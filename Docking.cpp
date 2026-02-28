#include "Docking.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Docking::Docking() {}

bool Docking::createDocking(const QString &location, const QString &length,
<<<<<<< HEAD
                           const QString &height, const QString &status,
                           const QString &capacity, const QString &startDate,
                           const QString &endDate)
{
    QSqlDatabase db = QSqlDatabase::database();
    
=======
                            const QString &height, const QString &status,
                            const QString &capacity, const QString &startDate,
                            const QString &endDate)
{
    QSqlDatabase db = QSqlDatabase::database();

>>>>>>> 71f93a09f10e0ea93fabf2f98f463c8f24f647a1
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }
<<<<<<< HEAD
    
    QSqlQuery query(db);
    query.prepare("INSERT INTO DOCKING (LOCATION, LENGTH, HEIGHT, STATUS, CAPACITY, STARTDATE, ENDDATE) "
                  "VALUES (:location, :length, :height, :status, :capacity, :startDate, :endDate)");
    
=======

    QSqlQuery query(db);
    query.prepare("INSERT INTO DOCKING (LOCATION, LENGTH, HEIGHT, STATUS, CAPACITY, STARTDATE, ENDDATE) "
                  "VALUES (:location, :length, :height, :status, :capacity, :startDate, :endDate)");

>>>>>>> 71f93a09f10e0ea93fabf2f98f463c8f24f647a1
    query.addBindValue(location);
    query.addBindValue(length);
    query.addBindValue(height);
    query.addBindValue(status);
    query.addBindValue(capacity);
    query.addBindValue(startDate);
    query.addBindValue(endDate);
<<<<<<< HEAD
    
=======

>>>>>>> 71f93a09f10e0ea93fabf2f98f463c8f24f647a1
    if (!query.exec()) {
        qDebug() << "Error inserting docking:" << query.lastError().text();
        return false;
    }
<<<<<<< HEAD
    
=======

>>>>>>> 71f93a09f10e0ea93fabf2f98f463c8f24f647a1
    qDebug() << "Docking created successfully!";
    return true;
}

QList<DockingRecord> Docking::getAllDockings()
{
    QList<DockingRecord> records;
    QSqlDatabase db = QSqlDatabase::database();
<<<<<<< HEAD
    
=======

>>>>>>> 71f93a09f10e0ea93fabf2f98f463c8f24f647a1
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return records;
    }
<<<<<<< HEAD
    
    QSqlQuery query(db);
    query.prepare("SELECT DOCKID, LOCATION, LENGTH, HEIGHT, STATUS, CAPACITY, STARTDATE, ENDDATE FROM DOCKING ORDER BY DOCKID ASC");
    
=======

    QSqlQuery query(db);
    query.prepare("SELECT DOCKID, LOCATION, LENGTH, HEIGHT, STATUS, CAPACITY, STARTDATE, ENDDATE FROM DOCKING");

>>>>>>> 71f93a09f10e0ea93fabf2f98f463c8f24f647a1
    if (!query.exec()) {
        qDebug() << "Error fetching dockings:" << query.lastError().text();
        return records;
    }
<<<<<<< HEAD
    
=======

>>>>>>> 71f93a09f10e0ea93fabf2f98f463c8f24f647a1
    while (query.next()) {
        DockingRecord record;
        record.id = query.value(0).toInt();
        record.location = query.value(1).toString();
        record.length = query.value(2).toString();
        record.height = query.value(3).toString();
        record.status = query.value(4).toString();
        record.capacity = query.value(5).toString();
        record.startDate = query.value(6).toString();
        record.endDate = query.value(7).toString();
        records.append(record);
    }
<<<<<<< HEAD
    
=======

>>>>>>> 71f93a09f10e0ea93fabf2f98f463c8f24f647a1
    qDebug() << "Fetched" << records.size() << "docking records";
    return records;
}

bool Docking::updateDocking(int id, const QString &location, const QString &length,
<<<<<<< HEAD
                           const QString &height, const QString &status,
                           const QString &capacity, const QString &startDate,
                           const QString &endDate)
{
    QSqlDatabase db = QSqlDatabase::database();
    
=======
                            const QString &height, const QString &status,
                            const QString &capacity, const QString &startDate,
                            const QString &endDate)
{
    QSqlDatabase db = QSqlDatabase::database();

>>>>>>> 71f93a09f10e0ea93fabf2f98f463c8f24f647a1
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }
<<<<<<< HEAD
    
=======

>>>>>>> 71f93a09f10e0ea93fabf2f98f463c8f24f647a1
    QSqlQuery query(db);
    query.prepare("UPDATE DOCKING SET LOCATION = :location, LENGTH = :length, HEIGHT = :height, "
                  "STATUS = :status, CAPACITY = :capacity, STARTDATE = :startDate, "
                  "ENDDATE = :endDate WHERE DOCKID = :id");
<<<<<<< HEAD
    
=======

>>>>>>> 71f93a09f10e0ea93fabf2f98f463c8f24f647a1
    query.addBindValue(location);
    query.addBindValue(length);
    query.addBindValue(height);
    query.addBindValue(status);
    query.addBindValue(capacity);
    query.addBindValue(startDate);
    query.addBindValue(endDate);
    query.addBindValue(id);
<<<<<<< HEAD
    
=======

>>>>>>> 71f93a09f10e0ea93fabf2f98f463c8f24f647a1
    if (!query.exec()) {
        qDebug() << "Error updating docking:" << query.lastError().text();
        return false;
    }
<<<<<<< HEAD
    
=======

>>>>>>> 71f93a09f10e0ea93fabf2f98f463c8f24f647a1
    qDebug() << "Docking updated successfully!";
    return true;
}

bool Docking::deleteDocking(int id)
{
    QSqlDatabase db = QSqlDatabase::database();
<<<<<<< HEAD
    
=======

>>>>>>> 71f93a09f10e0ea93fabf2f98f463c8f24f647a1
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }
<<<<<<< HEAD
    
    QSqlQuery query(db);
    query.prepare("DELETE FROM DOCKING WHERE DOCKID = :id");
    query.addBindValue(id);
    
=======

    QSqlQuery query(db);
    query.prepare("DELETE FROM DOCKING WHERE DOCKID = :id");
    query.addBindValue(id);

>>>>>>> 71f93a09f10e0ea93fabf2f98f463c8f24f647a1
    if (!query.exec()) {
        qDebug() << "Error deleting docking:" << query.lastError().text();
        return false;
    }
<<<<<<< HEAD
    
=======

>>>>>>> 71f93a09f10e0ea93fabf2f98f463c8f24f647a1
    qDebug() << "Docking deleted successfully!";
    return true;
}

QString Docking::getLastError()
{
    QSqlDatabase db = QSqlDatabase::database();
    return db.lastError().text();
}
