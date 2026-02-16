#ifndef BOATS_H
#define BOATS_H

#include <QString>
#include <QSqlQuery>

class Boats
{
public:
    Boats();

    // Create a new boat record
    bool createBoat(const QString &boatId, const QString &size,
                    const QString &location, const QString &ownerName,
                    const QString &ownerEmail, int status,
                    const QString &type, const QString &lastMaintenanceDate,
                    int totalTrips, int totalFish);

    // Update an existing boat record
    bool updateBoat(const QString &boatId, const QString &size,
                    const QString &location, const QString &ownerName,
                    const QString &ownerEmail, int status,
                    const QString &type, const QString &lastMaintenanceDate,
                    int totalTrips, int totalFish);

    // Delete a boat record
    bool deleteBoat(const QString &boatId);

    // Get a specific boat by ID
    QSqlQuery getBoat(const QString &boatId);

    // Get all boats
    QSqlQuery getAllBoats();

    // Get last error message
    QString getLastError();
};

#endif // BOATS_H
