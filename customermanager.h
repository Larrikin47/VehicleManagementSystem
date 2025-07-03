#pragma once
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QString>

class CustomerManager {
public:
    void setDatabase(const QSqlDatabase &db);
    void createTable();
    bool addCustomer(const QString &name, const QString &phone, const QString &email);
    QSqlQueryModel* getAllCustomersModel();

private:
    QSqlDatabase m_db;
};
