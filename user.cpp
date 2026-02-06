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
