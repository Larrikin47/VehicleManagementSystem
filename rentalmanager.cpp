#include "rentalmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

void RentalManager::setDatabase(const QSqlDatabase &db) {
    m_db = db;
}

void RentalManager::createTables() {
    QSqlQuery query(m_db);

    // Vehicles table
    query.exec("CREATE TABLE IF NOT EXISTS vehicles ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT NOT NULL, "
               "rate REAL NOT NULL, "
               "status TEXT NOT NULL)");

    // Rentals table with rental_date and date_returned
    query.exec("CREATE TABLE IF NOT EXISTS rentals ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "customer_id INTEGER NOT NULL, "
               "vehicle_id INTEGER NOT NULL, "
               "rental_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP, "
               "date_returned TIMESTAMP)");
}

QSqlQueryModel* RentalManager::getAllVehiclesModel() {
    auto *model = new QSqlQueryModel;
    model->setQuery("SELECT id, name, rate, status FROM vehicles", m_db);
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Name");
    model->setHeaderData(2, Qt::Horizontal, "Rate");
    model->setHeaderData(3, Qt::Horizontal, "Status");
    return model;
}

QSqlQueryModel* RentalManager::getAllRentalsModel() {
    auto *model = new QSqlQueryModel;
    model->setQuery(R"(
        SELECT rentals.id, customers.name AS customer, vehicles.name AS vehicle,
               rentals.rental_date, rentals.date_returned
        FROM rentals
        JOIN customers ON rentals.customer_id = customers.id
        JOIN vehicles ON rentals.vehicle_id = vehicles.id
        ORDER BY rentals.rental_date DESC
    )", m_db);
    model->setHeaderData(0, Qt::Horizontal, "Rental ID");
    model->setHeaderData(1, Qt::Horizontal, "Customer");
    model->setHeaderData(2, Qt::Horizontal, "Vehicle");
    model->setHeaderData(3, Qt::Horizontal, "Date Rented");
    model->setHeaderData(4, Qt::Horizontal, "Date Returned");
    return model;
}

bool RentalManager::addVehicle(const QString &name, double rate) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO vehicles (name, rate, status) VALUES (?, ?, 'Available')");
    query.addBindValue(name);
    query.addBindValue(rate);
    return query.exec();
}

bool RentalManager::updateVehicleStatus(int id, const QString &status) {
    QSqlQuery query(m_db);
    query.prepare("UPDATE vehicles SET status = ? WHERE id = ?");
    query.addBindValue(status);
    query.addBindValue(id);
    return query.exec();
}

bool RentalManager::registerRental(int customerId, int vehicleId) {
    QSqlQuery query(m_db);

    // First: update the vehicle's status
    query.prepare("UPDATE vehicles SET status = 'Rented' WHERE id = ?");
    query.addBindValue(vehicleId);
    if (!query.exec()) {
        qWarning() << "Failed to update vehicle status:" << query.lastError().text();
        return false;
    }

    // Then: insert into rentals table
    query.prepare("INSERT INTO rentals (customer_id, vehicle_id) VALUES (?, ?)");
    query.addBindValue(customerId);
    query.addBindValue(vehicleId);
    if (!query.exec()) {
        qWarning() << "Failed to register rental:" << query.lastError().text();
        return false;
    }

    return true;
}
