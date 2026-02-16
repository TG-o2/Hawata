#include "User.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

User::User() {
    usersModel = new QSqlQueryModel();


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
bool User::updateUser(int userId, const QString &email, const QString &firstName,
                             const QString &lastName, const QString &role,
                             const QString &gender, double salary)
{
    QSqlQuery query;
    query.prepare("UPDATE USERS SET email = :email, first_name = :fname, last_name = :lname, "
                  "role = :role, gender = :gender, salary = :salary WHERE user_id = :uid");

    query.bindValue(":email", email);
    query.bindValue(":fname", firstName);
    query.bindValue(":lname", lastName);
    query.bindValue(":role", role);
    query.bindValue(":gender", gender);
    query.bindValue(":salary", salary);
    query.bindValue(":uid", userId);

    if(!query.exec()) {
        qDebug() << "Update failed:" << query.lastError().text();
        return false;
    }
    return true;
}

QString User::getLastError()
{
    QSqlDatabase db = QSqlDatabase::database();
    return db.lastError().text();
}
