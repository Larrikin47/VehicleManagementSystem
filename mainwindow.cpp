#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addvehicledialog.h"
#include "addcustomerdialog.h"        // ✅ New
#include "rentalmanager.h"
#include "customermanager.h"          // ✅ New

#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Initialize database connection
    db = QSqlDatabase::addDatabase("QSQLITE");

    // Set database path to application directory
    QString dbPath = QCoreApplication::applicationDirPath() + "/rental.db";
    db.setDatabaseName(dbPath);

    // Log the path for debugging
    qDebug() << "Database path:" << dbPath;

    // Open the database and check for success
    if (!db.open()) {
        QMessageBox::critical(this, "Database Error",
                              "Failed to open the database:\n" + db.lastError().text());
        return;
    }

    qDebug() << "Database opened successfully.";

    // Setup tables and display data
    setupDatabase();
    refreshView();
}

MainWindow::~MainWindow() {
    db.close();
    delete ui;
}

void MainWindow::setupDatabase() {
    RentalManager mgr;
    mgr.setDatabase(db);
    mgr.createTable();

    CustomerManager cmgr;
    cmgr.setDatabase(db);
    cmgr.createTable();
}

void MainWindow::refreshView() {
    RentalManager mgr;
    mgr.setDatabase(db);
    ui->tableView->setModel(mgr.getAllVehiclesModel());
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
    int id = ui->tableView->model()->data(
                                       ui->tableView->model()->index(ui->tableView->currentIndex().row(), 0)).toInt();

    RentalManager mgr;
    mgr.setDatabase(db);
    mgr.updateVehicleStatus(id, "Rented");
    refreshView();
}

void MainWindow::on_returnButton_clicked() {
    int id = ui->tableView->model()->data(
                                       ui->tableView->model()->index(ui->tableView->currentIndex().row(), 0)).toInt();

    RentalManager mgr;
    mgr.setDatabase(db);
    mgr.updateVehicleStatus(id, "Available");
    refreshView();
}

void MainWindow::on_refreshButton_clicked() {
    refreshView();
}

// ✅ Add Customer Button logic
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
