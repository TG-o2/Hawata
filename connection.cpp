#include "connection.h"
#include <QDebug>
#include <QStringList>
#include <QtGlobal>

Connection::Connection()
{
<<<<<<< HEAD
    db = QSqlDatabase::addDatabase("QODBC");  // or "QOCI" for Oracle client
    db.setDatabaseName("Driver={Oracle in XE};Dbq=localhost:1521/XE;Uid=qtuserc;Pwd=mypassword123;");
=======
>>>>>>> 1b1cd5493122bb876131594df48c28eb8d37e3bc

}

bool Connection::createconnect()
{
    m_lastError.clear();

    const QString connectionName = "qt_sql_default_connection";

    {
        QSqlDatabase oldDb = QSqlDatabase::database(connectionName, false);
        if (oldDb.isValid() && oldDb.isOpen()) {
            oldDb.close();
        }
    }
    QSqlDatabase::removeDatabase(connectionName);

    const QString dbUser = qEnvironmentVariable("HWT_DB_USER", "qtuser");
    const QString dbPassword = qEnvironmentVariable("HWT_DB_PASSWORD", "mypassword123");
    const QString dbHost = qEnvironmentVariable("HWT_DB_HOST", "localhost");
    const QString dbPort = qEnvironmentVariable("HWT_DB_PORT", "1521");
    const QString dbService = qEnvironmentVariable("HWT_DB_SERVICE", "XE");
    const QString dbConnect = qEnvironmentVariable(
        "HWT_DB_CONNECT",
        QString("%1:%2/%3").arg(dbHost, dbPort, dbService)
        );
    const QString dbDsn = qEnvironmentVariable("HWT_DB_DSN", "HWT");
    const QString dbOdbcDriver = qEnvironmentVariable("HWT_DB_ODBC_DRIVER", "Oracle in XE");
    const QString dbOdbcConn = qEnvironmentVariable(
        "HWT_DB_ODBC_CONN",
        QString("Driver={%1};Dbq=//%2:%3/%4;Uid=%5;Pwd=%6;")
            .arg(dbOdbcDriver, dbHost, dbPort, dbService, dbUser, dbPassword)
        );

    const QStringList availableDrivers = QSqlDatabase::drivers();

    auto tryDriver = [&](const QString &driver, const QStringList &databaseCandidates) -> bool {
        if (!availableDrivers.contains(driver)) {
            return false;
        }

        QString localLastError;
        {
            QSqlDatabase db = QSqlDatabase::addDatabase(driver, connectionName);
            db.setUserName(dbUser);
            db.setPassword(dbPassword);

            for (const QString &databaseName : databaseCandidates) {
                db.setDatabaseName(databaseName);
                if (db.open()) {
                    qDebug() << "Database connected. driver=" << driver << "databaseName=" << databaseName;
                    return true;
                }

                localLastError = db.lastError().text();
                qDebug() << "Database open failed. driver=" << driver
                         << "databaseName=" << databaseName
                         << "error=" << localLastError;
            }

            db.close();
        }

        QSqlDatabase::removeDatabase(connectionName);
        m_lastError = localLastError;
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
        QString("DSN=%1;UID=%2;PWD=%3;").arg(dbDsn, dbUser, dbPassword),
        QString("DSN=%1;").arg(dbDsn),
        dbDsn
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
