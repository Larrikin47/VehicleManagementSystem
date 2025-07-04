#include "addrentaldialog.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

AddRentalDialog::AddRentalDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AddRentalDialog) {
    ui->setupUi(this);
    loadCustomers();
    loadVehicles();
}

AddRentalDialog::~AddRentalDialog() {
    delete ui;
}

void AddRentalDialog::loadCustomers() {
    QSqlQuery query("SELECT id, name FROM customers");
    if (!query.exec()) {
        qDebug() << "Failed to load customers:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();
        ui->customerComboBox->addItem(name, id);
    }
}

void AddRentalDialog::loadVehicles() {
    QSqlQuery query("SELECT id, name FROM vehicles WHERE status = 'Available'");
    if (!query.exec()) {
        qDebug() << "Failed to load vehicles:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();
        ui->vehicleComboBox->addItem(name, id);
    }
}

int AddRentalDialog::getSelectedCustomerId() const {
    return ui->customerComboBox->currentData().toInt();
}

int AddRentalDialog::getSelectedVehicleId() const {
    return ui->vehicleComboBox->currentData().toInt();
}
