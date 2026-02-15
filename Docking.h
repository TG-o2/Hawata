#ifndef DOCKING_H
#define DOCKING_H

#include <QString>

class Docking
{
public:
    Docking();

    // Create docking in database
    bool createDocking(const QString &location, const QString &length,
                      const QString &height, const QString &status,
                      const QString &capacity, const QString &startDate,
                      const QString &endDate);

private:
    QString getLastError();
};

#endif // DOCKING_H
