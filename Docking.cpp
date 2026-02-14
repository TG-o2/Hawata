#include "Docking.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Docking::Docking() {}

bool Docking::createDocking(const QString &location, const QString &length,
                           const QString &height, const QString &status,
                           const QString &capacity, const QString &startDate,
                           const QString &endDate)
{
    QSqlDatabase db = QSqlDatabase::database();
    
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }
    
    QSqlQuery query(db);
    // Use uppercase column names without quotes
    query.prepare("INSERT INTO DOCKING (LOCATION, LENGTH, HEIGHT, STATUS, CAPACITY, STARTDATE, ENDDATE) "
                  "VALUES (:location, :length, :height, :status, :capacity, TO_DATE(:startDate, 'YYYY-MM-DD HH24:MI:SS'), TO_DATE(:endDate, 'YYYY-MM-DD HH24:MI:SS'))");
    
    query.addBindValue(location);
    query.addBindValue(length);
    query.addBindValue(height);
    query.addBindValue(status);
    query.addBindValue(capacity);
    query.addBindValue(startDate);
    query.addBindValue(endDate);
    
    if (!query.exec()) {
        qDebug() << "Error inserting docking:" << query.lastError().text();
        return false;
    }
    
    qDebug() << "Docking created successfully!";
    return true;
}

QString Docking::getLastError()
{
    QSqlDatabase db = QSqlDatabase::database();
    return db.lastError().text();
}
