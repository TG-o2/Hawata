#ifndef USER_H
#define USER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QList>

struct UserRecord {
    int id;
    QString email;
    QString firstName;
    QString lastName;
    QString password;
    QString role;
    QString gender;
    double salary;
    QString shiftStart;
    QString shiftEnd;
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
