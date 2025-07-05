#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "addvehicledialog.h"
#include "addcustomerdialog.h"
#include "addrentaldialog.h"

#include "rentalmanager.h"
#include "customermanager.h"

#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSqlQuery>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Setup database
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = QCoreApplication::applicationDirPath() + "/rental.db";
    db.setDatabaseName(dbPath);

    qDebug() << "Database path:" << dbPath;

    if (!db.open()) {
        QMessageBox::critical(this, "Database Error", db.lastError().text());
        return;
    }

    qDebug() << "Database opened successfully.";

    setupDatabase();
    refreshView();
}

MainWindow::~MainWindow() {
    db.close();
    delete ui;
}

void MainWindow::setupDatabase() {
    RentalManager rentalMgr;
    rentalMgr.setDatabase(db);
    rentalMgr.createTables();

    CustomerManager custMgr;
    custMgr.setDatabase(db);
    custMgr.createTable();
}

void MainWindow::refreshView() {
    RentalManager mgr;
    mgr.setDatabase(db);
    ui->tableView->setModel(mgr.getAllVehiclesModel());

    if (ui->rentalTableView) {
        ui->rentalTableView->setModel(mgr.getAllRentalsModel());
    }
}

void MainWindow::on_addVehicleButton_clicked() {
    AddVehicleDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        RentalManager mgr;
        mgr.setDatabase(db);
        mgr.addVehicle(dlg.getName(), dlg.getRate());
        refreshView();
    }
}

void MainWindow::on_rentButton_clicked() {
    AddRentalDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        RentalManager mgr;
        mgr.setDatabase(db);

        int customerId = dlg.getSelectedCustomerId();
        int vehicleId = dlg.getSelectedVehicleId();

        if (mgr.registerRental(customerId, vehicleId)) {
            QMessageBox::information(this, "Rental Success", "Rental recorded successfully.");
            refreshView();
        } else {
            QMessageBox::warning(this, "Rental Failed", "Rental failed. Please check data.");
        }
    }
}

void MainWindow::on_returnButton_clicked() {
    int id = ui->tableView->model()->data(
                                       ui->tableView->model()->index(ui->tableView->currentIndex().row(), 0)).toInt();

    RentalManager mgr;
    mgr.setDatabase(db);

    // Update vehicle status
    mgr.updateVehicleStatus(id, "Available");

    // Also update rentals.date_returned with current timestamp
    QSqlQuery query(db);
    query.prepare("UPDATE rentals SET date_returned = :now WHERE vehicle_id = :vid AND date_returned IS NULL");
    query.bindValue(":vid", id);
    query.bindValue(":now", QDateTime::currentDateTime().toString(Qt::ISODate));
    if (!query.exec()) {
        QMessageBox::warning(this, "Return Error", query.lastError().text());
    }

    refreshView();
}

void MainWindow::on_refreshButton_clicked() {
    refreshView();
}

void MainWindow::on_addCustomerButton_clicked() {
    AddCustomerDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        CustomerManager cmgr;
        cmgr.setDatabase(db);
        bool success = cmgr.addCustomer(dlg.getName(), dlg.getPhone(), dlg.getEmail());
        if (success) {
            QMessageBox::information(this, "Customer Added", "New customer added successfully.");
        } else {
            QMessageBox::warning(this, "Error", "Failed to add customer.");
        }
    }
}

void MainWindow::on_deleteVehicleButton_clicked() {
    QModelIndex currentIndex = ui->tableView->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "No Selection", "Please select a vehicle to delete.");
        return;
    }

    int row = currentIndex.row();
    int vehicleId = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toInt();

    QMessageBox::StandardButton confirm = QMessageBox::question(this, "Confirm Delete",
                                                                "Are you sure you want to delete this vehicle?",
                                                                QMessageBox::Yes | QMessageBox::No);

    if (confirm == QMessageBox::Yes) {
        QSqlQuery query(db);
        query.prepare("DELETE FROM vehicles WHERE id = :id");
        query.bindValue(":id", vehicleId);

        if (!query.exec()) {
            QMessageBox::critical(this, "Delete Failed", query.lastError().text());
        } else {
            QMessageBox::information(this, "Deleted", "Vehicle deleted successfully.");
            refreshView();
        }
    }
}

// ✅ New: Generate Rental Report and Export to CSV
void MainWindow::on_generateReportButton_clicked() {
    QString filePath = QCoreApplication::applicationDirPath() + "/rental_report.csv";
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "File Error", "Unable to create report file.");
        return;
    }

    QTextStream out(&file);
    out << "RentalID,Customer,Vehicle,DateRented,DateReturned,ReturnStatus\n";

    QSqlQuery query(db);
    QString sql = R"(
        SELECT rentals.id, customers.name, vehicles.name, rentals.rental_date,
               rentals.date_returned,
               CASE WHEN rentals.date_returned IS NOT NULL THEN 'Returned' ELSE 'Not Returned' END AS return_status
        FROM rentals
        JOIN customers ON rentals.customer_id = customers.id
        JOIN vehicles ON rentals.vehicle_id = vehicles.id
    )";

    if (!query.exec(sql)) {
        QMessageBox::critical(this, "Query Error", query.lastError().text());
        return;
    }

    while (query.next()) {
        QString rentalId = query.value(0).toString();
        QString customerName = query.value(1).toString();
        QString vehicleName = query.value(2).toString();
        QString dateRented = query.value(3).toString();
        QString dateReturned = query.value(4).toString();
        QString returnStatus = query.value(5).toString();

        out << QString("%1,%2,%3,%4,%5,%6\n")
                   .arg(rentalId, customerName, vehicleName, dateRented, dateReturned, returnStatus);
    }

    file.close();

    QMessageBox::information(this, "Report Generated", "CSV report saved to:\n" + filePath);

    // Auto-open CSV file
#if defined(Q_OS_WIN)
    QProcess::startDetached("notepad.exe", {filePath});
#elif defined(Q_OS_MAC)
    QProcess::startDetached("open", {filePath});
#else
    QProcess::startDetached("xdg-open", {filePath});
#endif
}
