#include "Docking.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>

namespace {
QString normalizeDockingDate(const QVariant &value)
{
    const QDate date = value.toDate();
    if (date.isValid()) {
        return date.toString("dd/MM/yy");
    }

    const QDateTime dateTime = value.toDateTime();
    if (dateTime.isValid()) {
        return dateTime.date().toString("dd/MM/yy");
    }

    return value.toString().trimmed();
}
}

Docking::Docking() {}

bool Docking::createDocking(const QString &location, const QString &length,
                           const QString &height, const QString &status,
                           const QString &capacity, const QString &startDate,
                           const QString &endDate, int *createdDockId)
{
    QSqlDatabase db = QSqlDatabase::database();
    
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }
    
    QSqlQuery query(db);
    query.prepare("INSERT INTO DOCKING (LOCATION, LENGTH, HEIGHT, STATUS, CAPACITY, STARTDATE, ENDDATE) "
                  "VALUES (:location, :length, :height, :status, :capacity, :startDate, :endDate)");

    query.bindValue(":location", location);
    query.bindValue(":length", length);
    query.bindValue(":height", height);
    query.bindValue(":status", status);
    query.bindValue(":capacity", capacity);
    query.bindValue(":startDate", startDate);
    query.bindValue(":endDate", endDate);
    
    if (!query.exec()) {
        qDebug() << "Error inserting docking:" << query.lastError().text();
        return false;
    }

    int newDockId = -1;

    // QODBC + Oracle does not support query.lastInsertId(); resolve the inserted DOCKID with a SELECT.
    QSqlQuery idQuery(db);
    idQuery.prepare(
        "SELECT DOCKID FROM ("
        "  SELECT DOCKID FROM DOCKING "
        "  WHERE LOCATION = :location "
        "    AND LENGTH = :length "
        "    AND HEIGHT = :height "
        "    AND STATUS = :status "
        "    AND CAPACITY = :capacity "
        "    AND STARTDATE = :startDate "
        "    AND ENDDATE = :endDate "
        "  ORDER BY DOCKID DESC"
        ") WHERE ROWNUM = 1");
    idQuery.bindValue(":location", location);
    idQuery.bindValue(":length", length);
    idQuery.bindValue(":height", height);
    idQuery.bindValue(":status", status);
    idQuery.bindValue(":capacity", capacity);
    idQuery.bindValue(":startDate", startDate);
    idQuery.bindValue(":endDate", endDate);

    if (idQuery.exec() && idQuery.next()) {
        newDockId = idQuery.value(0).toInt();
    }

    if (newDockId <= 0) {
        QSqlQuery fallbackQuery(db);
        fallbackQuery.prepare("SELECT DOCKID FROM (SELECT DOCKID FROM DOCKING ORDER BY DOCKID DESC) WHERE ROWNUM = 1");
        if (fallbackQuery.exec() && fallbackQuery.next()) {
            newDockId = fallbackQuery.value(0).toInt();
        }
    }

    if (createdDockId != nullptr) {
        *createdDockId = newDockId;
    }
    
    qDebug() << "Docking created successfully!";
    return true;
}

QList<DockingRecord> Docking::getAllDockings()
{
    QList<DockingRecord> records;
    QSqlDatabase db = QSqlDatabase::database();
    
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return records;
    }
    
    QSqlQuery query(db);
    query.prepare("SELECT DOCKID, LOCATION, LENGTH, HEIGHT, STATUS, CAPACITY, STARTDATE, ENDDATE FROM DOCKING ORDER BY DOCKID ASC");
    
    if (!query.exec()) {
        qDebug() << "Error fetching dockings:" << query.lastError().text();
        return records;
    }
    
    while (query.next()) {
        DockingRecord record;
        record.id = query.value(0).toInt();
        record.location = query.value(1).toString();
        record.length = query.value(2).toString();
        record.height = query.value(3).toString();
        record.status = query.value(4).toString();
        record.capacity = query.value(5).toString();
        record.startDate = normalizeDockingDate(query.value(6));
        record.endDate = normalizeDockingDate(query.value(7));
        records.append(record);
    }
    
    qDebug() << "Fetched" << records.size() << "docking records";
    return records;
}

bool Docking::updateDocking(int id, const QString &location, const QString &length,
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
    query.prepare("UPDATE DOCKING SET LOCATION = :location, LENGTH = :length, HEIGHT = :height, "
                  "STATUS = :status, CAPACITY = :capacity, STARTDATE = :startDate, "
                  "ENDDATE = :endDate WHERE DOCKID = :id");

    query.bindValue(":location", location);
    query.bindValue(":length", length);
    query.bindValue(":height", height);
    query.bindValue(":status", status);
    query.bindValue(":capacity", capacity);
    query.bindValue(":startDate", startDate);
    query.bindValue(":endDate", endDate);
    query.bindValue(":id", id);
    
    if (!query.exec()) {
        qDebug() << "Error updating docking:" << query.lastError().text();
        return false;
    }
    
    qDebug() << "Docking updated successfully!";
    return true;
}

bool Docking::deleteDocking(int id)
{
    QSqlDatabase db = QSqlDatabase::database();
    
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }
    
    if (!db.transaction()) {
        qDebug() << "Error starting transaction for docking delete:" << db.lastError().text();
        return false;
    }

    QSqlQuery query(db);

    // Remove child rows first to satisfy FK_MANAGE_DOCK constraint.
    query.prepare("DELETE FROM MANAGE WHERE DOCKID = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Error deleting related manage rows:" << query.lastError().text();
        db.rollback();
        return false;
    }

    query.prepare("DELETE FROM DOCKING WHERE DOCKID = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Error deleting docking:" << query.lastError().text();
        db.rollback();
        return false;
    }

    if (!db.commit()) {
        qDebug() << "Error committing docking delete transaction:" << db.lastError().text();
        db.rollback();
        return false;
    }
    
    qDebug() << "Docking deleted successfully!";
    return true;
}

QString Docking::getLastError()
{
    QSqlDatabase db = QSqlDatabase::database();
    return db.lastError().text();
}
