#include "company.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Company::Company() {
    companiesModel = new QSqlQueryModel();
}

QList<CompanyRecord> Company::getAllCompanies()
{
    QList<CompanyRecord> records;
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return records;
    }

    QSqlQuery query(db);
    query.prepare("SELECT COMPANY_ID, NAME, LOCATION, EMAIL, PHONE, PREFERRED_FISH, STATUS FROM COMPANIES");

    if (!query.exec()) {
        qDebug() << "Error fetching companies:" << query.lastError().text();
        return records;
    }

    while (query.next()) {
        records.append(CompanyRecord(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toString(),
            query.value(5).toString(),
            query.value(6).toString()
            ));
    }

    qDebug() << "Fetched" << records.size() << "company records";
    return records;
}

///CREATE
bool Company::createCompany(const QString &name,
                            const QString &location,
                            const QString &email,
                            const QString &phone,
                            const QString &preferredFish,
                            const QString &status)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO COMPANIES (NAME, LOCATION, EMAIL, PHONE, PREFERRED_FISH, STATUS) "
                  "VALUES (:name, :location, :email, :phone, :preferredFish, :status)");

    query.bindValue(":name", name);
    query.bindValue(":location", location);
    query.bindValue(":email", email);
    query.bindValue(":phone", phone);
    query.bindValue(":preferredFish", preferredFish);
    query.bindValue(":status", status);

    if (!query.exec()) {
        qDebug() << "=== INSERT FAILED ===";
        qDebug() << "Database error:" << query.lastError().databaseText();
        qDebug() << "Driver error:"   << query.lastError().driverText();
        return false;
    }

    qDebug() << "Company created successfully!";
    return true;
}

///DISPLAY / READ
QSqlQueryModel* Company::getCompaniesModel()
{
    companiesModel->setQuery(
        "SELECT COMPANY_ID, NAME, LOCATION, EMAIL, PHONE, PREFERRED_FISH, STATUS FROM COMPANIES"
        );

    return companiesModel;
}

///DELETE
bool Company::deleteCompany(int COMPANY_ID)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("DELETE FROM COMPANIES WHERE COMPANY_ID = :id");
    query.bindValue(":id", COMPANY_ID);

    if (!query.exec()) {
        qDebug() << "Delete error:" << query.lastError().text();
        return false;
    }

    companiesModel->setQuery(
        "SELECT COMPANY_ID, NAME, LOCATION, EMAIL, PHONE, PREFERRED_FISH, STATUS FROM COMPANIES"
        );

    return true;
}

///UPDATE
bool Company::updateCompany(int COMPANY_ID,
                            const QString &name,
                            const QString &location,
                            const QString &email,
                            const QString &phone,
                            const QString &preferredFish,
                            const QString &status)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE COMPANIES SET NAME = :name, LOCATION = :location, EMAIL = :email, "
                  "PHONE = :phone, PREFERRED_FISH = :preferredFish, STATUS = :status "
                  "WHERE COMPANY_ID = :id");

    query.bindValue(":name", name);
    query.bindValue(":location", location);
    query.bindValue(":email", email);
    query.bindValue(":phone", phone);
    query.bindValue(":preferredFish", preferredFish);
    query.bindValue(":status", status);
    query.bindValue(":id", COMPANY_ID);

    if (!query.exec()) {
        qDebug() << "Update failed:" << query.lastError().text();
        return false;
    }

    qDebug() << "Company updated successfully!";
    return true;
}

QString Company::getLastError()
{
    QSqlDatabase db = QSqlDatabase::database();
    return db.lastError().text();
}
