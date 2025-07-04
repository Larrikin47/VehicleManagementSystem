#pragma once
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QString>

class RentalManager {
public:
    void setDatabase(const QSqlDatabase &db);
    void createTables();  // ← updated name (plural)

    QSqlQueryModel* getAllVehiclesModel();
    QSqlQueryModel* getAllRentalsModel();  // ← NEW: View all rentals

    bool addVehicle(const QString &name, double rate);
    bool updateVehicleStatus(int id, const QString &status);

    bool registerRental(int customerId, int vehicleId);  // ← NEW: Assign vehicle to customer

private:
    QSqlDatabase m_db;
};
