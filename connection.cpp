#include "connection.h"

Connection::Connection()
{
    // Use the member db, not a local variable
    db = QSqlDatabase::addDatabase("QODBC");  // or "QOCI" for Oracle client

    db.setDatabaseName("Driver={Oracle in XE};Dbq=localhost:1521/XE;Uid=SYSTEM;Pwd=root;");


    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
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
            qDebug() << "Database connection failed:" << db.lastError().text();
            return false;
        }
    }

    qDebug() << "Database connected successfully!";
    return true;
}
