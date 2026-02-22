#include "connection.h"

Connection::Connection()
{
    db = QSqlDatabase::addDatabase("QODBC");  // or "QOCI" for Oracle client
    db.setDatabaseName("Driver={Oracle in XE};Dbq=localhost:1521/XE;Uid=qtuser;Pwd=mypassword123;");

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
}
