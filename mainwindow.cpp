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

// ✅ Setup both Vehicle and Customer tables
void MainWindow::setupDatabase() {
    RentalManager rentalMgr;
    rentalMgr.setDatabase(db);
    rentalMgr.createTables(); // creates vehicles and rentals

    CustomerManager custMgr;
    custMgr.setDatabase(db);
    custMgr.createTable(); // creates customers
}

// ✅ Refresh the vehicle view + optional rental view
void MainWindow::refreshView() {
    RentalManager mgr;
    mgr.setDatabase(db);
    ui->tableView->setModel(mgr.getAllVehiclesModel());

    if (ui->rentalTableView) {
        ui->rentalTableView->setModel(mgr.getAllRentalsModel());
    }
}

// ✅ Add a new vehicle
void MainWindow::on_addVehicleButton_clicked() {
    AddVehicleDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        RentalManager mgr;
        mgr.setDatabase(db);
        mgr.addVehicle(dlg.getName(), dlg.getRate());
        refreshView();
    }
}

// ✅ Rent a vehicle to a customer
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

// ✅ Return a vehicle (mark as available)
void MainWindow::on_returnButton_clicked() {
    int id = ui->tableView->model()->data(
                                       ui->tableView->model()->index(ui->tableView->currentIndex().row(), 0)).toInt();

    RentalManager mgr;
    mgr.setDatabase(db);
    mgr.updateVehicleStatus(id, "Available");
    refreshView();
}

// ✅ Manual refresh
void MainWindow::on_refreshButton_clicked() {
    refreshView();
}

// ✅ Add a new customer
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

// ✅ Delete a vehicle
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
