/* #include "rentalmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

void RentalManager::setDatabase(const QSqlDatabase &db) {
    m_db = db;
}

void RentalManager::createTable() {
    QSqlQuery query(m_db);
    query.exec("CREATE TABLE IF NOT EXISTS vehicles ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT NOT NULL, "
               "rate REAL NOT NULL, "
               "status TEXT NOT NULL)");
}

QSqlQueryModel* RentalManager::getAllVehiclesModel() {
    auto model = new QSqlQueryModel;
    model->setQuery("SELECT id, name, rate, status FROM vehicles", m_db);
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Name");
    model->setHeaderData(2, Qt::Horizontal, "Rate");
    model->setHeaderData(3, Qt::Horizontal, "Status");
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
*/

#include "rentalmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

void RentalManager::setDatabase(const QSqlDatabase &db) {
    m_db = db;
}

void RentalManager::createTable() {
    QSqlQuery query(m_db);
    query.exec("CREATE TABLE IF NOT EXISTS vehicles ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT NOT NULL, "
               "rate REAL NOT NULL, "
               "status TEXT NOT NULL)");
}

QSqlQueryModel* RentalManager::getAllVehiclesModel() {
    auto model = new QSqlQueryModel;
    model->setQuery("SELECT id, name, rate, status FROM vehicles", m_db);
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Name");
    model->setHeaderData(2, Qt::Horizontal, "Rate");
    model->setHeaderData(3, Qt::Horizontal, "Status");
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
