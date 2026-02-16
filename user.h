#ifndef USER_H
#define USER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQueryModel>

class User
{
private:
    QSqlQueryModel* usersModel;


public:
    User();

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

    // Get last database error
    QString getLastError();
    QSqlQueryModel* getUsersModel();
    bool deleteUser(int userId);
    bool updateUser(int userId, const QString &email, const QString &firstName,const QString &lastName, const QString &role, const QString &gender, double salary);


};

#endif // USER_H
