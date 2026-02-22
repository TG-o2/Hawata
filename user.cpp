#include "User.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

User::User() {
    usersModel = new QSqlQueryModel();


}

QList<UserRecord> User::getAllUsers()
{
    QList<UserRecord> records;
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return records;
    }

    QSqlQuery query(db);
    query.prepare("SELECT USERID, EMAIL, FIRST_NAME, LAST_NAME, ROLE, GENDER, SALARY, SHIFT_START, SHIFT_END FROM USERS");

    if (!query.exec()) {
        qDebug() << "Error fetching users:" << query.lastError().text();
        return records;
    }

    while (query.next()) {
        UserRecord record;
        record.id = query.value(0).toInt();
        record.email = query.value(1).toString();
        record.firstName = query.value(2).toString();
        record.lastName = query.value(3).toString();
        record.role = query.value(4).toString();
        record.gender = query.value(5).toString();
        record.salary = query.value(6).toDouble();
        record.shiftStart = query.value(7).toString();
        record.shiftEnd = query.value(8).toString();
        records.append(record);
    }

    qDebug() << "Fetched" << records.size() << "user records";
    return records;
}

///CREATE
bool User::createUser(const QString &email,
                      const QString &firstName,
                      const QString &lastName,
                      const QString &password,
                      const QString &role,
                      const QString &gender,
                      double salary,
                      const QString &shiftStart,
                      const QString &shiftEnd)
{
    QSqlDatabase db = QSqlDatabase::database(); // uses default connection

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);

    // Use named placeholders
    query.prepare("INSERT INTO USERS (EMAIL, FIRST_NAME, LAST_NAME, PASSWORD, ROLE, GENDER, SALARY, SHIFT_START, SHIFT_END) "
                  "VALUES (:email, :firstName, :lastName, :password, :role, :gender, :salary, "
                  "TO_DATE(:shiftStart, 'YYYY-MM-DD HH24:MI:SS'), TO_DATE(:shiftEnd, 'YYYY-MM-DD HH24:MI:SS'))");

    // Bind values by name
    query.bindValue(":email", email);
    query.bindValue(":firstName", firstName);
    query.bindValue(":lastName", lastName);
    query.bindValue(":password", password);
    query.bindValue(":role", role);
    query.bindValue(":gender", gender);
    query.bindValue(":salary", salary);
    query.bindValue(":shiftStart", shiftStart);
    query.bindValue(":shiftEnd", shiftEnd);

    if (!query.exec()) {
        qDebug() << "Error inserting user:" << query.lastError().text();
        return false;
    }

    qDebug() << "User created successfully!";
    return true;
}

///DISPLAY/ READ

QSqlQueryModel* User::getUsersModel()
{
    usersModel->setQuery(
        "SELECT USERID, EMAIL, FIRST_NAME, LAST_NAME, ROLE, GENDER, SALARY, SHIFT_START, SHIFT_END FROM USERS"
        );

    return usersModel;
}
///DELETE
bool User::deleteUser(int userId)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("DELETE FROM USERS WHERE USERID = :id");
    query.bindValue(":id", userId);

    if (!query.exec()) {
        qDebug() << "Delete error:" << query.lastError().text();
        return false;
    }

    usersModel->setQuery(
        "SELECT USERID, EMAIL, FIRST_NAME, LAST_NAME, ROLE, GENDER, SALARY, SHIFT_START, SHIFT_END FROM USERS"
        );

    return true;
}

///UPDATE
bool User::updateUser(int userId,
                      const QString &email,
                      const QString &firstName,
                      const QString &lastName,
                      const QString &password,
                      const QString &role,
                      const QString &gender,
                      double salary,
                      const QString &shiftStart,
                      const QString &shiftEnd)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE USERS SET EMAIL = :email, FIRST_NAME = :firstName, LAST_NAME = :lastName, "
                  "PASSWORD = :password, ROLE = :role, GENDER = :gender, SALARY = :salary, "
                  "SHIFT_START = TO_DATE(:shiftStart, 'YYYY-MM-DD HH24:MI:SS'), "
                  "SHIFT_END = TO_DATE(:shiftEnd, 'YYYY-MM-DD HH24:MI:SS') "
                  "WHERE USERID = :id");

    query.bindValue(":email", email);
    query.bindValue(":firstName", firstName);
    query.bindValue(":lastName", lastName);
    query.bindValue(":password", password);
    query.bindValue(":role", role);
    query.bindValue(":gender", gender);
    query.bindValue(":salary", salary);
    query.bindValue(":shiftStart", shiftStart);
    query.bindValue(":shiftEnd", shiftEnd);
    query.bindValue(":id", userId);

    if (!query.exec()) {
        qDebug() << "Update failed:" << query.lastError().text();
        return false;
    }

    qDebug() << "User updated successfully!";
    return true;
}


QString User::getLastError()
{
    QSqlDatabase db = QSqlDatabase::database();
    return db.lastError().text();
}
