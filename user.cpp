<<<<<<< HEAD
#include "user.h"
#include <QCryptographicHash>



// ---- Constructors ----

//create acc
User::User(const QString &firstName,
           const QString &lastName,
           Role role,
           const QString &email,
           const QString &passwordPlain)
    : m_userid(0),                       //--def
    m_firstName(firstName),
    m_lastName(lastName),
    m_role(role),
    m_email(email),
    m_salary(0.0),                     //--def
    m_status(UserStatus::Active),      //--def
    m_createdAt(QDateTime::currentDateTime())
{
    setPassword(passwordPlain);
}

//def user constructor
User::User(int userid,
           const QString &firstName,
           const QString &lastName,
           Role role,
           const QString &email,
           const QString &passwordPlain,
           double salary,
           UserStatus status,
           const QDateTime &createdAt)
    : m_userid(userid),
    m_firstName(firstName),
    m_lastName(lastName),
    m_role(role),
    m_email(email),
    m_salary(salary),
    m_status(status),
    m_createdAt(createdAt)
{
    setPassword(passwordPlain);
}


// ---- Hash Function ----

QString User::hashPassword(const QString &plain) const
{
    QByteArray hash =
        QCryptographicHash::hash(
            plain.toUtf8(),
            QCryptographicHash::Sha256);

    return hash.toHex();
}


//retrieve user data from file (-->will be changed to Qt database maybe?)
QString User::toFileString() const
{
    return m_firstName + ";" +
           m_lastName  + ";" +
           QString::number(static_cast<int>(m_role)) + ";" +
           m_email     + ";" +
           m_passwordHash;
}


// ---- Password Methods ----

void User::setPassword(const QString &plainPassword)
{
    m_passwordHash = hashPassword(plainPassword);
}

bool User::verifyPassword(const QString &plainPassword) const
{
    return hashPassword(plainPassword) == m_passwordHash;
}


// ---- Getters ----

int User::getuserId() const { return m_userid; }
QString User::getFirstName() const { return m_firstName; }
QString User::getLastName() const { return m_lastName; }
User::Role User::getRole() const { return m_role; }
QString User::getEmail() const { return m_email; }
QString User::getPasswordHash() const { return m_passwordHash; }
double User::getSalary() const { return m_salary; }
User::UserStatus User::getStatus() const { return m_status; }
QDateTime User::getCreatedAt() const { return m_createdAt; }


// ---- Setters ----

void User::setFirstName(const QString &value) { m_firstName = value; }
void User::setLastName(const QString &value) { m_lastName = value; }
void User::setRole(Role &value) { m_role = value; }
void User::setEmail(const QString &value) { m_email = value; }
void User::setSalary(double value) { m_salary = value; }
void User::setStatus(UserStatus value) { m_status = value; }
=======
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
        records.append(UserRecord(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toString(),
            QString(),
            query.value(4).toString(),
            query.value(5).toString(),
            query.value(6).toDouble(),
            query.value(7).toString(),
            query.value(8).toString()
            ));
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
>>>>>>> 71f93a09f10e0ea93fabf2f98f463c8f24f647a1
