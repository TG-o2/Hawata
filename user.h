#ifndef USER_H
#define USER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlError>

class User
{
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

};

#endif // USER_H
