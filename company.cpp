#include "company.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QRegularExpression>

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

    // ===== INPUT VALIDATION =====
    if (name.trimmed().isEmpty()) {
        qDebug() << "Name is required!";
        return false;
    }

    if (preferredFish.trimmed().isEmpty()) {
        qDebug() << "Preferred fish is required!";
        return false;
    }

    QString normalizedStatus = status.trimmed().toUpper();
    if (normalizedStatus != "ACTIVE" && normalizedStatus != "INACTIVE") {
        qDebug() << "Invalid status value!";
        return false;
    }

    // Basic email validation
    QRegularExpression emailRegex("^[\\w\\.]+@[\\w\\.]+\\.[a-zA-Z]{2,}$");
    if (!email.isEmpty() && !emailRegex.match(email).hasMatch()) {
        qDebug() << "Invalid email format!";
        return false;
    }

    // Phone validation: exactly 8 digits
    QRegularExpression phoneRegex("^[0-9]{8}$");

    if (!phoneRegex.match(phone.trimmed()).hasMatch()) {
        qDebug() << "Phone must contain exactly 8 digits!";
        return false;
    }

    // Check duplicate email manually
    if (!email.isEmpty()) {
        QSqlQuery checkQuery(db);
        checkQuery.prepare("SELECT COUNT(*) FROM COMPANIES WHERE EMAIL = :email");
        checkQuery.bindValue(":email", email);
        checkQuery.exec();
        checkQuery.next();

        if (checkQuery.value(0).toInt() > 0) {
            qDebug() << "Email already exists!";
            return false;
        }
    }

    // ===== INSERT =====
    QSqlQuery query(db);
    query.prepare("INSERT INTO COMPANIES "
                  "(NAME, LOCATION, EMAIL, PHONE, PREFERRED_FISH, STATUS) "
                  "VALUES (:name, :location, :email, :phone, :preferredFish, :status)");

    query.bindValue(":name", name.trimmed());
    query.bindValue(":location", location.trimmed());
    query.bindValue(":email", email.trimmed());
    query.bindValue(":phone", phone.trimmed());
    query.bindValue(":preferredFish", preferredFish.trimmed());
    query.bindValue(":status", normalizedStatus);

    if (!query.exec()) {
        qDebug() << "Insert failed:" << query.lastError().text();
        return false;
    }

    return true;
}

///DISPLAY / READ
QSqlQueryModel* Company::getCompaniesModel()
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return nullptr;
    }

    companiesModel->setQuery(
        "SELECT COMPANY_ID, NAME, LOCATION, EMAIL, PHONE, "
        "PREFERRED_FISH, STATUS FROM COMPANIES"
        );

    if (companiesModel->lastError().isValid()) {
        qDebug() << "Model error:" << companiesModel->lastError().text();
    }

    return companiesModel;
}

///DELETE
bool Company::deleteCompany(int companyId)
{
    if (companyId <= 0) {
        qDebug() << "Invalid company ID!";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database();

    if (!db.transaction()) {
        qDebug() << "Transaction failed!";
        return false;
    }

    QSqlQuery query(db);

    // Check existence first
    query.prepare("SELECT COUNT(*) FROM COMPANIES WHERE COMPANY_ID = :id");
    query.bindValue(":id", companyId);
    query.exec();
    query.next();

    if (query.value(0).toInt() == 0) {
        db.rollback();
        qDebug() << "Company does not exist!";
        return false;
    }

    // Delete dependencies
    query.prepare("DELETE FROM BUY WHERE COMPANY_ID = :id");
    query.bindValue(":id", companyId);
    if (!query.exec()) { db.rollback(); return false; }

    query.prepare("DELETE FROM PRODUCTS WHERE COMPANYID = :id");
    query.bindValue(":id", companyId);
    if (!query.exec()) { db.rollback(); return false; }

    query.prepare("DELETE FROM COMPANIES WHERE COMPANY_ID = :id");
    query.bindValue(":id", companyId);
    if (!query.exec()) { db.rollback(); return false; }

    db.commit();
    return true;
}
///UPDATE
bool Company::updateCompany(int companyId,
                            const QString &name,
                            const QString &location,
                            const QString &email,
                            const QString &phone,
                            const QString &preferredFish,
                            const QString &status)
{
    if (companyId <= 0) {
        qDebug() << "Invalid company ID!";
        return false;
    }

    if (name.trimmed().isEmpty() || preferredFish.trimmed().isEmpty()) {
        qDebug() << "Required fields missing!";
        return false;
    }

    QString normalizedStatus = status.trimmed().toUpper();
    if (normalizedStatus != "ACTIVE" && normalizedStatus != "INACTIVE") {
        qDebug() << "Invalid status!";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return false;

    // Prevent duplicate email (excluding current record)
    QSqlQuery checkQuery(db);
    checkQuery.prepare("SELECT COUNT(*) FROM COMPANIES "
                       "WHERE EMAIL = :email AND COMPANY_ID != :id");
    checkQuery.bindValue(":email", email);
    checkQuery.bindValue(":id", companyId);
    checkQuery.exec();
    checkQuery.next();

    if (checkQuery.value(0).toInt() > 0) {
        qDebug() << "Email already used by another company!";
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

    query.bindValue(":name", name.trimmed());
    query.bindValue(":location", location.trimmed());
    query.bindValue(":email", email.trimmed());
    query.bindValue(":phone", phone.trimmed());
    query.bindValue(":preferredFish", preferredFish.trimmed());
    query.bindValue(":status", normalizedStatus);
    query.bindValue(":id", companyId);

    if (!query.exec()) {
        qDebug() << "Update failed:" << query.lastError().text();
        return false;
    }

    return true;
}
QList<CompanyRecord> Company::searchCompanies(const QString &keyword)
{
    QList<CompanyRecord> records;
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return records;

    QSqlQuery query(db);
    query.prepare(
        "SELECT COMPANY_ID, NAME, LOCATION, EMAIL, PHONE, "
        "PREFERRED_FISH, STATUS "
        "FROM COMPANIES "
        "WHERE LOWER(NAME) LIKE LOWER(:kw) "
        "OR LOWER(LOCATION) LIKE LOWER(:kw) "
        "OR LOWER(EMAIL) LIKE LOWER(:kw) "
        "OR LOWER(PREFERRED_FISH) LIKE LOWER(:kw) "
        "OR LOWER(STATUS) LIKE LOWER(:kw)"
        );

    query.bindValue(":kw", "%" + keyword + "%");

    if (!query.exec()) {
        qDebug() << "Search error:" << query.lastError().text();
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

    return records;
}
QList<CompanyRecord> Company::sortCompaniesBy(const QString &column)
{
    QList<CompanyRecord> records;
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return records;

    QString safeColumn;

    // 🔐 Allow only these two columns
    if (column == "NAME")
        safeColumn = "NAME";
    else if (column == "PREFERRED_FISH")
        safeColumn = "PREFERRED_FISH";
    else
        safeColumn = "COMPANY_ID";

    QString queryStr =
        "SELECT COMPANY_ID, NAME, LOCATION, EMAIL, PHONE, "
        "PREFERRED_FISH, STATUS "
        "FROM COMPANIES ORDER BY " + safeColumn + " ASC";

    QSqlQuery query(db);

    if (!query.exec(queryStr)) {
        qDebug() << "Sort error:" << query.lastError().text();
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

    return records;
}

QString Company::getLastError()
{
    QSqlDatabase db = QSqlDatabase::database();
    return db.lastError().text();
}
