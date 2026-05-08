#include "connection.h"
#include <QDebug>
#include <QStringList>
#include <QtGlobal>


Connection::Connection() = default;

bool Connection::createconnect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    db.setHostName("localhost");
    db.setPort(1521);
    db.setDatabaseName("HWT");
    db.setUserName("qtuser");
    db.setPassword("mypassword123");

    if (db.open()) {
        qDebug() << "Connected to MySQL!";
        return true;
    } else {
        m_lastError = db.lastError().text();
        qDebug() << "Error:" << m_lastError;
        return false;
    }
}

QString Connection::lastError() const
{
    return m_lastError;
}
