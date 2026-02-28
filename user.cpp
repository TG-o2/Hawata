#include "user.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

User::User()
    : m_userId(0),
    m_salary(0.0),
    m_supervisorId(0)
{
}

User::User(int userId,
           const QString &email,
           const QString &firstName,
           const QString &lastName,
           const QString &password,
           const QString &role,
           const QString &gender,
           double salary,
           const QString &shiftStart,
           const QString &shiftEnd,
           int supervisorId)
    : m_userId(userId),
    m_email(email),
    m_firstName(firstName),
    m_lastName(lastName),
    m_password(password),
    m_role(role),
    m_gender(gender),
    m_salary(salary),
    m_shiftStart(shiftStart),
    m_shiftEnd(shiftEnd),
    m_supervisorId(supervisorId)
{
}

int User::getUserId() const { return m_userId; }
QString User::getEmail() const { return m_email; }
QString User::getFirstName() const { return m_firstName; }
QString User::getLastName() const { return m_lastName; }
QString User::getPassword() const { return m_password; }
QString User::getRole() const { return m_role; }
QString User::getGender() const { return m_gender; }
double User::getSalary() const { return m_salary; }
QString User::getShiftStart() const { return m_shiftStart; }
QString User::getShiftEnd() const { return m_shiftEnd; }
int User::getSupervisorId() const { return m_supervisorId; }

void User::setUserId(int value) { m_userId = value; }
void User::setEmail(const QString &value) { m_email = value; }
void User::setFirstName(const QString &value) { m_firstName = value; }
void User::setLastName(const QString &value) { m_lastName = value; }
void User::setPassword(const QString &value) { m_password = value; }
void User::setRole(const QString &value) { m_role = value; }
void User::setGender(const QString &value) { m_gender = value; }
void User::setSalary(double value) { m_salary = value; }
void User::setShiftStart(const QString &value) { m_shiftStart = value; }
void User::setShiftEnd(const QString &value) { m_shiftEnd = value; }
void User::setSupervisorId(int value) { m_supervisorId = value; }

QList<User> User::afficher_liste()
{
    QList<User> records;
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return records;
    }

    QSqlQuery query(db);
    query.prepare("SELECT USERID, EMAIL, FIRST_NAME, LAST_NAME, PASSWORD, ROLE, GENDER, SALARY, SHIFT_START, SHIFT_END, SUPERVISORID FROM USERS");

    if (!query.exec()) {
        qDebug() << "Error fetching users:" << query.lastError().text();
        return records;
    }

    while (query.next()) {
        records.append(User(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toString(),
            query.value(5).toString(),
            query.value(6).toString(),
            query.value(7).toDouble(),
            query.value(8).toString(),
            query.value(9).toString(),
            query.value(10).toInt()
        ));
    }

    qDebug() << "Fetched" << records.size() << "user records";
    return records;
}

bool User::ajouter_user()
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO USERS (EMAIL, FIRST_NAME, LAST_NAME, PASSWORD, ROLE, GENDER, SALARY, SHIFT_START, SHIFT_END, SUPERVISORID) "
                  "VALUES (:email, :firstName, :lastName, :password, :role, :gender, :salary, "
                  "TO_DATE(:shiftStart, 'YYYY-MM-DD HH24:MI:SS'), TO_DATE(:shiftEnd, 'YYYY-MM-DD HH24:MI:SS'), :supervisorId)");

    query.bindValue(":email", m_email);
    query.bindValue(":firstName", m_firstName);
    query.bindValue(":lastName", m_lastName);
    query.bindValue(":password", m_password);
    query.bindValue(":role", m_role);
    query.bindValue(":gender", m_gender);
    query.bindValue(":salary", m_salary);
    query.bindValue(":shiftStart", m_shiftStart);
    query.bindValue(":shiftEnd", m_shiftEnd);
    query.bindValue(":supervisorId", m_supervisorId);

    if (!query.exec()) {
        qDebug() << "Error inserting user:" << query.lastError().text();
        return false;
    }

    qDebug() << "User created successfully!";
    return true;
}

QSqlQueryModel* User::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT USERID, EMAIL, FIRST_NAME, LAST_NAME, ROLE, GENDER, SALARY, SHIFT_START, SHIFT_END, SUPERVISORID FROM USERS");
    return model;
}

bool User::supprimer(int userId)
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

    return true;
}

bool User::modifier_user()
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
                  "SHIFT_END = TO_DATE(:shiftEnd, 'YYYY-MM-DD HH24:MI:SS'), "
                  "SUPERVISORID = :supervisorId "
                  "WHERE USERID = :id");

    query.bindValue(":email", m_email);
    query.bindValue(":firstName", m_firstName);
    query.bindValue(":lastName", m_lastName);
    query.bindValue(":password", m_password);
    query.bindValue(":role", m_role);
    query.bindValue(":gender", m_gender);
    query.bindValue(":salary", m_salary);
    query.bindValue(":shiftStart", m_shiftStart);
    query.bindValue(":shiftEnd", m_shiftEnd);
    query.bindValue(":supervisorId", m_supervisorId);
    query.bindValue(":id", m_userId);

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
