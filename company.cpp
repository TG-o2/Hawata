#include "company.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Company::Company()
    : m_companyId(0)
{
}

Company::Company(int companyId,
                 const QString &name,
                 const QString &location,
                 const QString &email,
                 const QString &phone,
                 const QString &preferredFish,
                 const QString &status)
    : m_companyId(companyId),
    m_name(name),
    m_location(location),
    m_email(email),
    m_phone(phone),
    m_preferredFish(preferredFish),
    m_status(status)
{
}

int Company::getCompanyId() const { return m_companyId; }
QString Company::getName() const { return m_name; }
QString Company::getLocation() const { return m_location; }
QString Company::getEmail() const { return m_email; }
QString Company::getPhone() const { return m_phone; }
QString Company::getPreferredFish() const { return m_preferredFish; }
QString Company::getStatus() const { return m_status; }

void Company::setCompanyId(int value) { m_companyId = value; }
void Company::setName(const QString &value) { m_name = value; }
void Company::setLocation(const QString &value) { m_location = value; }
void Company::setEmail(const QString &value) { m_email = value; }
void Company::setPhone(const QString &value) { m_phone = value; }
void Company::setPreferredFish(const QString &value) { m_preferredFish = value; }
void Company::setStatus(const QString &value) { m_status = value; }

QList<Company> Company::afficher_liste()
{
    QList<Company> records;
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
        records.append(Company(
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

bool Company::ajouter_company()
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO COMPANIES (NAME, LOCATION, EMAIL, PHONE, PREFERRED_FISH, STATUS) "
                  "VALUES (:name, :location, :email, :phone, :preferredFish, :status)");

    query.bindValue(":name", m_name);
    query.bindValue(":location", m_location);
    query.bindValue(":email", m_email);
    query.bindValue(":phone", m_phone);
    query.bindValue(":preferredFish", m_preferredFish);
    query.bindValue(":status", m_status);

    if (!query.exec()) {
        qDebug() << "Error inserting company:" << query.lastError().text();
        return false;
    }

    qDebug() << "Company created successfully!";
    return true;
}

QSqlQueryModel* Company::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT COMPANY_ID, NAME, LOCATION, EMAIL, PHONE, PREFERRED_FISH, STATUS FROM COMPANIES");
    return model;
}

bool Company::supprimer(int companyId)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("DELETE FROM COMPANIES WHERE COMPANY_ID = :id");
    query.bindValue(":id", companyId);

    if (!query.exec()) {
        qDebug() << "Delete error:" << query.lastError().text();
        return false;
    }

    return true;
}

bool Company::modifier_company()
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE COMPANIES SET "
                  "NAME = :name, "
                  "LOCATION = :location, "
                  "EMAIL = :email, "
                  "PHONE = :phone, "
                  "PREFERRED_FISH = :preferredFish, "
                  "STATUS = :status "
                  "WHERE COMPANY_ID = :id");

    query.bindValue(":name", m_name);
    query.bindValue(":location", m_location);
    query.bindValue(":email", m_email);
    query.bindValue(":phone", m_phone);
    query.bindValue(":preferredFish", m_preferredFish);
    query.bindValue(":status", m_status);
    query.bindValue(":id", m_companyId);

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
