#ifndef BOATS_H
#define BOATS_H

#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class Boats
{
public:
    Boats();
    Boats(int id, const QString &size, const QString &location,
          const QString &ownerName, const QString &ownerEmail, int status,
          const QString &type, const QString &lastMaintenanceDate,
          int totalTrips, int totalFish);

    // Getters
    int getId() const { return id; }
    QString getSize() const { return size; }
    QString getLocation() const { return location; }
    QString getOwnerName() const { return ownerName; }
    QString getOwnerEmail() const { return ownerEmail; }
    int getStatus() const { return status; }
    QString getType() const { return type; }
    QString getLastMaintenanceDate() const { return lastMaintenanceDate; }
    int getTotalTrips() const { return totalTrips; }
    int getTotalFish() const { return totalFish; }

    // Setters
    void setId(int newId) { id = newId; }
    void setSize(const QString &newSize) { size = newSize; }
    void setLocation(const QString &newLocation) { location = newLocation; }
    void setOwnerName(const QString &newOwnerName) { ownerName = newOwnerName; }
    void setOwnerEmail(const QString &newOwnerEmail) { ownerEmail = newOwnerEmail; }
    void setStatus(int newStatus) { status = newStatus; }
    void setType(const QString &newType) { type = newType; }
    void setLastMaintenanceDate(const QString &newDate) { lastMaintenanceDate = newDate; }
    void setTotalTrips(int newTotalTrips) { totalTrips = newTotalTrips; }
    void setTotalFish(int newTotalFish) { totalFish = newTotalFish; }

    // CRUD Operations
    bool create();  // Now doesn't require ID in parameters
    bool update();
    bool deleteBoat();
    void read(); // Populates the current object with data from DB for its ID
    static QSqlQuery getAll(); // Returns all boats


    // Helper methods
    QString getLastError() const { return lastError; }



private:
    int id;
    QString size;
    QString location;
    QString ownerName;
    QString ownerEmail;
    int status; // 1 = IN PORT, 0 = OUT
    QString type;
    QString lastMaintenanceDate;
    int totalTrips;
    int totalFish;
    QString lastError;
};

#endif // BOATS_H
