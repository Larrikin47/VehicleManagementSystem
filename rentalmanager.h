/* #pragma once
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QString>

class RentalManager {
public:
    void setDatabase(const QSqlDatabase &db);
    void createTable();
    QSqlQueryModel* getAllVehiclesModel();
    bool addVehicle(const QString &name, double rate);
    bool updateVehicleStatus(int id, const QString &status);

private:
    QSqlDatabase m_db;
};

*/

#pragma once
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QString>

class RentalManager {
public:
    void setDatabase(const QSqlDatabase &db);
    void createTable();
    QSqlQueryModel* getAllVehiclesModel();
    bool addVehicle(const QString &name, double rate);
    bool updateVehicleStatus(int id, const QString &status);

private:
    QSqlDatabase m_db;
};
