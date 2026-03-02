#ifndef USER_H
#define USER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QList>

class User
{
public:
    User();
    User(int userId,
         const QString &email,
         const QString &firstName,
         const QString &lastName,
         const QString &password,
         const QString &role,
         const QString &gender,
         double salary,
         const QString &shiftStart,
         const QString &shiftEnd,
         int supervisorId = 0);

    int getUserId() const;
    QString getEmail() const;
    QString getFirstName() const;
    QString getLastName() const;
    QString getPassword() const;
    QString getRole() const;
    QString getGender() const;
    double getSalary() const;
    QString getShiftStart() const;
    QString getShiftEnd() const;
    int getSupervisorId() const;

    void setUserId(int value);
    void setEmail(const QString &value);
    void setFirstName(const QString &value);
    void setLastName(const QString &value);
    void setPassword(const QString &value);
    void setRole(const QString &value);
    void setGender(const QString &value);
    void setSalary(double value);
    void setShiftStart(const QString &value);
    void setShiftEnd(const QString &value);
    void setSupervisorId(int value);

    bool ajouter_user();
    QSqlQueryModel* afficher();
    bool supprimer(int userId);
    bool modifier_user();
    QList<User> afficher_liste();
    QString getLastError();

private:
    int m_userId;
    QString m_email;
    QString m_firstName;
    QString m_lastName;
    QString m_password;
    QString m_role;
    QString m_gender;
    double m_salary;
    QString m_shiftStart;
    QString m_shiftEnd;
    int m_supervisorId;
};

#endif // USER_H
