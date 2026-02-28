#ifndef CONNECTION_H
#define CONNECTION_H
<<<<<<< HEAD
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
=======

#include <QSqlDatabase>
#include <QDebug>
>>>>>>> 71f93a09f10e0ea93fabf2f98f463c8f24f647a1

class Connection
{
public:
    Connection();
<<<<<<< HEAD
    bool createconnect();
=======
    ~Connection();

    bool openConnection();

    QSqlDatabase db;

>>>>>>> 71f93a09f10e0ea93fabf2f98f463c8f24f647a1
};

#endif // CONNECTION_H
