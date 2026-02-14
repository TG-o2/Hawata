#ifndef USER_H
#define USER_H

#include <QString>
#include <QDateTime>

class User
{
/// constructor + functions
public:
    enum class UserStatus {
        Active,
        Suspended,
        OnLeave,
        Terminated
    };
    enum class Role {
        Admin,
        Manager,
        Employee
    };

    //constructor
    // For signup (UI)
    User(const QString &firstName,
         const QString &lastName,
         Role role,
         const QString &email,
         const QString &passwordPlain);

    // Full constructor (DB / admin / loading)
    User(int userid,
         const QString &firstName,
         const QString &lastName,
         Role role,
         const QString &email,
         const QString &passwordPlain,
         double salary,
         UserStatus status,
         const QDateTime &createdAt);

    // getters
    int getuserId() const;
    QString getFirstName() const;
    QString getLastName() const;
    Role getRole() const;
    QString getEmail() const;
    QString getPasswordHash() const;
    double getSalary() const;
    UserStatus getStatus() const;
    QDateTime getCreatedAt() const;

    // setters
    void setFirstName(const QString &value);
    void setLastName(const QString &value);
    void setRole(Role &value);
    void setEmail(const QString &value);
    void setSalary(double value);
    void setStatus(UserStatus value);

    // password
    void setPassword(const QString &plainPassword);
    bool verifyPassword(const QString &plainPassword) const;

    //retrieving data from user file
    QString toFileString() const;

    ///main attributes
private:
    int m_userid;
    QString m_firstName;
    QString m_lastName;
    Role m_role;
    QString m_email;
    QString m_passwordHash;
    double m_salary;
    UserStatus m_status;
    QDateTime m_createdAt;

    QString hashPassword(const QString &plain) const;
};

#endif
