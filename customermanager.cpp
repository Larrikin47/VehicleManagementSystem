#include "customermanager.h"
#include <QSqlQuery>

void CustomerManager::setDatabase(const QSqlDatabase &db) {
    m_db = db;
}

void CustomerManager::createTable() {
    QSqlQuery query(m_db);
    query.exec("CREATE TABLE IF NOT EXISTS customers ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT NOT NULL, "
               "phone TEXT, "
               "email TEXT)");
}

bool CustomerManager::addCustomer(const QString &name, const QString &phone, const QString &email) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO customers (name, phone, email) VALUES (?, ?, ?)");
    query.addBindValue(name);
    query.addBindValue(phone);
    query.addBindValue(email);
    return query.exec();
}

QSqlQueryModel* CustomerManager::getAllCustomersModel() {
    auto model = new QSqlQueryModel;
    model->setQuery("SELECT id, name, phone, email FROM customers", m_db);
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Name");
    model->setHeaderData(2, Qt::Horizontal, "Phone");
    model->setHeaderData(3, Qt::Horizontal, "Email");
    return model;
}
