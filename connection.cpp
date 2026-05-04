#include "connection.h"
#include <QDebug>
#include <QStringList>
#include <QtGlobal>
#include <QStringList>
#include <QtGlobal>

Connection::Connection()
{
    //db = QSqlDatabase::addDatabase("QODBC");  // or "QOCI" for Oracle client
    //db.setDatabaseName("Driver={Oracle in XE};Dbq=localhost:1521/XE;Uid=qtuserc;Pwd=mypassword123;");

}

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
    };

    const QStringList qociCandidates = {
        dbConnect,
        QString("//%1:%2/%3").arg(dbHost, dbPort, dbService),
        dbService
    };

    if (tryDriver("QOCI", qociCandidates)) {
        return true;
    }

    const QStringList qodbcCandidates = {
                                         dbOdbcConn,
                                         QString("Driver={%1};Dbq=%2;Uid=%3;Pwd=%4;").arg(dbOdbcDriver, dbConnect, dbUser, dbPassword),

                                         };

    if (tryDriver("QODBC", qodbcCandidates)) {
        return true;
    }

    m_lastError = QString("Database connection failed. Available Qt SQL drivers: %1. Last error: %2")
                      .arg(availableDrivers.join(", "), m_lastError);
    qDebug() << m_lastError;
    return false;
}

QString Connection::lastError() const
{
    return m_lastError;
}
