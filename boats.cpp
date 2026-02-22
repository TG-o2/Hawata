#include "Boats.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Boats::Boats() {}

bool Boats::createBoat(const QString &boatId, const QString &size,
                       const QString &location, const QString &ownerName,
                       const QString &ownerEmail, int status,
                       const QString &type, const QString &lastMaintenanceDate,
                       int totalTrips, int totalFish)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    // Use uppercase column names without quotes
    query.prepare("INSERT INTO BOATS (BOATID, SIZE, LOCATION, OWNERNAME, OWNEREMAIL, STATUS, TYPE, LASTMAINTENANCEDATE, TOTALTRIPS, TOTALFISH) "
                  "VALUES (:boatId, :size, :location, :ownerName, :ownerEmail, :status, :type, TO_DATE(:lastMaintenanceDate, 'YYYY-MM-DD HH24:MI:SS'), :totalTrips, :totalFish)");

    query.addBindValue(boatId);
    query.addBindValue(size);
    query.addBindValue(location);
    query.addBindValue(ownerName);
    query.addBindValue(ownerEmail);
    query.addBindValue(status);
    query.addBindValue(type);
    query.addBindValue(lastMaintenanceDate);
    query.addBindValue(totalTrips);
    query.addBindValue(totalFish);

    if (!query.exec()) {
        qDebug() << "Error inserting boat:" << query.lastError().text();
        return false;
    }

    qDebug() << "Boat created successfully!";
    return true;
}

bool Boats::updateBoat(const QString &boatId, const QString &size,
                       const QString &location, const QString &ownerName,
                       const QString &ownerEmail, int status,
                       const QString &type, const QString &lastMaintenanceDate,
                       int totalTrips, int totalFish)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE BOATS SET SIZE = :size, LOCATION = :location, "
                  "OWNERNAME = :ownerName, OWNEREMAIL = :ownerEmail, "
                  "STATUS = :status, TYPE = :type, "
                  "LASTMAINTENANCEDATE = TO_DATE(:lastMaintenanceDate, 'YYYY-MM-DD HH24:MI:SS'), "
                  "TOTALTRIPS = :totalTrips, TOTALFISH = :totalFish "
                  "WHERE BOATID = :boatId");

    query.addBindValue(size);
    query.addBindValue(location);
    query.addBindValue(ownerName);
    query.addBindValue(ownerEmail);
    query.addBindValue(status);
    query.addBindValue(type);
    query.addBindValue(lastMaintenanceDate);
    query.addBindValue(totalTrips);
    query.addBindValue(totalFish);
    query.addBindValue(boatId);

    if (!query.exec()) {
        qDebug() << "Error updating boat:" << query.lastError().text();
        return false;
    }

    qDebug() << "Boat updated successfully!";
    return true;
}

bool Boats::deleteBoat(const QString &boatId)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("DELETE FROM BOATS WHERE BOATID = :boatId");
    query.addBindValue(boatId);

    if (!query.exec()) {
        qDebug() << "Error deleting boat:" << query.lastError().text();
        return false;
    }

    qDebug() << "Boat deleted successfully!";
    return true;
}

QSqlQuery Boats::getBoat(const QString &boatId)
{
    QSqlQuery query;

    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database is not open!";
        return query;
    }

    query.prepare("SELECT * FROM BOATS WHERE BOATID = :boatId");
    query.addBindValue(boatId);

    if (!query.exec()) {
        qDebug() << "Error retrieving boat:" << query.lastError().text();
    }

    return query;
}

QSqlQuery Boats::getAllBoats()
{
    QSqlQuery query;

    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database is not open!";
        return query;
    }

    query.prepare("SELECT * FROM BOATS ORDER BY BOATID");

    if (!query.exec()) {
        qDebug() << "Error retrieving boats:" << query.lastError().text();
    }

    return query;
}

QString Boats::getLastError()
{
    QSqlDatabase db = QSqlDatabase::database();
    return db.lastError().text();
}
