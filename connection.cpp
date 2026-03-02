#include "connection.h"

Connection::Connection()
{
}

bool Connection::createconnect()
{
    m_lastError.clear();

    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("projet_2A");
    db.setUserName("SMARTFISH");
    db.setPassword("root");

    if (db.open()) {
        test = true;
    } else {
        m_lastError = db.lastError().text();
    }

    return test;
}

QString Connection::lastError() const
{
    return m_lastError;
}
