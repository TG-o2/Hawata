#ifndef USER_H
#define USER_H

#include <QString>
<<<<<<< HEAD
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
=======
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QList>

class UserRecord {
public:
    UserRecord() = default;
    UserRecord(int id,
               const QString &email,
               const QString &firstName,
               const QString &lastName,
               const QString &password,
               const QString &role,
               const QString &gender,
               double salary,
               const QString &shiftStart,
               const QString &shiftEnd)
        : m_id(id),
        m_email(email),
        m_firstName(firstName),
        m_lastName(lastName),
        m_password(password),
        m_role(role),
        m_gender(gender),
        m_salary(salary),
        m_shiftStart(shiftStart),
        m_shiftEnd(shiftEnd)
    {
    }

    int id() const { return m_id; }
    const QString& email() const { return m_email; }
    const QString& firstName() const { return m_firstName; }
    const QString& lastName() const { return m_lastName; }
    const QString& password() const { return m_password; }
    const QString& role() const { return m_role; }
    const QString& gender() const { return m_gender; }
    double salary() const { return m_salary; }
    const QString& shiftStart() const { return m_shiftStart; }
    const QString& shiftEnd() const { return m_shiftEnd; }

private:
    int m_id = 0;
    QString m_email;
    QString m_firstName;
    QString m_lastName;
    QString m_password;
    QString m_role;
    QString m_gender;
    double m_salary = 0.0;
    QString m_shiftStart;
    QString m_shiftEnd;
};

class User
{
private:
    QSqlQueryModel* usersModel;


public:
    User();
    ~User() {
        delete usersModel;
    }
    // Create a new user in the database
    bool createUser(const QString &email,
                    const QString &firstName,
                    const QString &lastName,
                    const QString &password,
                    const QString &role,
                    const QString &gender,
                    double salary,
                    const QString &shiftStart,
                    const QString &shiftEnd);

    QList<UserRecord> getAllUsers();

    QString getLastError();
    QSqlQueryModel* getUsersModel();

    bool deleteUser(int userId);

    bool updateUser(int userId,
                    const QString &email,
                    const QString &firstName,
                    const QString &lastName,
                    const QString &password,
                    const QString &role,
                    const QString &gender,
                    double salary,
                    const QString &shiftStart,
                    const QString &shiftEnd);


};

#endif // USER_H
>>>>>>> 71f93a09f10e0ea93fabf2f98f463c8f24f647a1
