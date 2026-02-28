#include "connection.h"

Connection::Connection()
{
<<<<<<< HEAD

}

bool Connection::createconnect()
{bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("projet_2A");//inserer le nom de la source de données
    db.setUserName("jihene");//inserer nom de l'utilisateur
    db.setPassword("jihene");//inserer mot de passe de cet utilisateur

    if (db.open())
        test=true;





    return  test;
=======
    db = QSqlDatabase::addDatabase("QODBC");  // or "QOCI" for Oracle client
    db.setDatabaseName("Driver={Oracle in XE};Dbq=localhost:1521/XE;Uid=ahmed;Pwd=root;");

    if (!db.open()) {
        qDebug() << "Database connection failed:";
    } else {
        qDebug() << "Database connected successfully!";
    }
}

Connection::~Connection()
{
    if (db.isOpen())
        db.close();
}

bool Connection::openConnection()
{
    if (!db.isOpen()) {
        if (!db.open()) {
            qDebug() << "Database connection failed:";
            return false;
        }
    }

    qDebug() << "Database connected successfully!";
    return true;
>>>>>>> 71f93a09f10e0ea93fabf2f98f463c8f24f647a1
}
