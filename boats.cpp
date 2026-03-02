#include "boats.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>

Boats::Boats() : id(0), status(1), totalTrips(0), totalFish(0)
{
}

Boats::Boats(int id, const QString &size, const QString &location,
             const QString &ownerName, const QString &ownerEmail, int status,
             const QString &type, const QString &lastMaintenanceDate,
             int totalTrips, int totalFish)
    : id(id), size(size), location(location), ownerName(ownerName),
    ownerEmail(ownerEmail), status(status), type(type),
    lastMaintenanceDate(lastMaintenanceDate), totalTrips(totalTrips),
    totalFish(totalFish)
{
}

bool Boats::create()
{
    lastError.clear();
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        lastError = "Database is not open!";
        qDebug() << lastError;
        return false;
    }

    QSqlQuery query(db);

    // If ID is 0, we need to get the next value
    if (id == 0) {
        // Get the max ID and add 1
        QSqlQuery maxQuery(db);
        maxQuery.exec("SELECT NVL(MAX(BOATID), 0) + 1 FROM BOAT");
        if (maxQuery.next()) {
            id = maxQuery.value(0).toInt();
        } else {
            lastError = "Failed to generate ID";
            return false;
        }
    }

    // Now include BOATID in the INSERT
    query.prepare("INSERT INTO BOAT (BOATID, SIZEBOAT, LOCATION, OWNERNAME, "
                  "OWNERMAIL, STATUS, TYPE, LASTMAINTENANCEDATE, TOTALTRIPS, TOTALFISH) "
                  "VALUES (:id, :size, :location, :ownerName, :ownerEmail, "
                  ":status, :type, TO_DATE(:lastMaintenanceDate, 'YYYY-MM-DD'), :totalTrips, :totalFish)");

    // Bind values including ID
    query.bindValue(":id", id);
    query.bindValue(":size", size);
    query.bindValue(":location", location);
    query.bindValue(":ownerName", ownerName);
    query.bindValue(":ownerEmail", ownerEmail);
    query.bindValue(":status", status);
    query.bindValue(":type", type);
    query.bindValue(":lastMaintenanceDate", lastMaintenanceDate);
    query.bindValue(":totalTrips", totalTrips);
    query.bindValue(":totalFish", totalFish);

    if (!query.exec()) {
        lastError = query.lastError().text();
        qDebug() << "Error inserting boat:" << lastError;
        return false;
    }

    qDebug() << "Boat created successfully with ID:" << id;
    return true;
}
bool Boats::update()
{
    lastError.clear();
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        lastError = "Database is not open!";
        qDebug() << lastError;
        return false;
    }

    QSqlQuery query(db);

    query.prepare("UPDATE BOAT SET "
                  "SIZEBOAT = :size, "
                  "LOCATION = :location, "
                  "OWNERNAME = :ownerName, "
                  "OWNERMAIL = :ownerEmail, "
                  "STATUS = :status, "
                  "TYPE = :type, "
                  "LASTMAINTENANCEDATE = TO_DATE(:lastMaintenanceDate, 'YYYY-MM-DD'), "
                  "TOTALTRIPS = :totalTrips, "
                  "TOTALFISH = :totalFish "
                  "WHERE BOATID = :id");

    query.bindValue(":size", size);
    query.bindValue(":location", location);
    query.bindValue(":ownerName", ownerName);
    query.bindValue(":ownerEmail", ownerEmail);
    query.bindValue(":status", status);
    query.bindValue(":type", type);
    query.bindValue(":lastMaintenanceDate", lastMaintenanceDate);
    query.bindValue(":totalTrips", totalTrips);
    query.bindValue(":totalFish", totalFish);
    query.bindValue(":id", id);

    if (!query.exec()) {
        lastError = query.lastError().text();
        qDebug() << "Error updating boat:" << lastError;
        return false;
    }

    // Check if any row was actually updated
    int rowsAffected = query.numRowsAffected();
    qDebug() << "Rows affected by update:" << rowsAffected;

    if (rowsAffected == 0) {
        lastError = "No boat found with ID: " + QString::number(id);
        qDebug() << lastError;
        return false;
    }

    qDebug() << "Boat updated successfully!";
    return true;
}

bool Boats::deleteBoat()
{
    lastError.clear();
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        lastError = "Database is not open!";
        qDebug() << lastError;
        return false;
    }

    QSqlQuery query(db);

    query.prepare("DELETE FROM BOAT WHERE BOATID = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        lastError = query.lastError().text();
        qDebug() << "Error deleting boat:" << lastError;
        return false;
    }

    // Check if any row was actually deleted
    if (query.numRowsAffected() == 0) {
        lastError = "No boat found with ID: " + QString::number(id);
        qDebug() << lastError;
        return false;
    }

    qDebug() << "Boat deleted successfully!";
    return true;
}

void Boats::read()
{
    lastError.clear();
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        lastError = "Database is not open!";
        qDebug() << lastError;
        return;
    }

    QSqlQuery query(db);

    query.prepare("SELECT SIZEBOAT, LOCATION, OWNERNAME, OWNERMAIL, "
                  "STATUS, TYPE, LASTMAINTENANCEDATE, TOTALTRIPS, TOTALFISH "
                  "FROM BOAT WHERE BOATID = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        lastError = query.lastError().text();
        qDebug() << "Error reading boat:" << lastError;
        return;
    }

    if (query.next()) {
        size = query.value(0).toString();
        location = query.value(1).toString();
        ownerName = query.value(2).toString();
        ownerEmail = query.value(3).toString();
        status = query.value(4).toInt();
        type = query.value(5).toString();
        lastMaintenanceDate = query.value(6).toString();
        totalTrips = query.value(7).toInt();
        totalFish = query.value(8).toInt();

        qDebug() << "Boat read successfully!";
    } else {
        lastError = "No boat found with ID: " + QString::number(id);
        qDebug() << lastError;
    }
}

QSqlQuery Boats::getAll()
{
    QSqlQuery query;

    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return query;
    }

    query = QSqlQuery(db);

    query.prepare("SELECT BOATID, SIZEBOAT, LOCATION, OWNERNAME, OWNERMAIL, "
                  "STATUS, TYPE, LASTMAINTENANCEDATE, TOTALTRIPS, TOTALFISH "
                  "FROM BOAT ORDER BY BOATID");

    if (!query.exec()) {
        qDebug() << "Error retrieving boats:" << query.lastError().text();
    }

    return query;
}

