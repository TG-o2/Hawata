#ifndef DOCKING_H
#define DOCKING_H

#include <QString>
#include <QList>
#include <QStringList>

struct DockingRecord {
    int id;
    QString location;
    QString length;
    QString height;
    QString status;
    QString capacity;
    QString startDate;
    QString endDate;
};

class Docking
{
public:
    Docking();

    bool createDocking(const QString &location, const QString &length,
                       const QString &height, const QString &status,
                       const QString &capacity, const QString &startDate,
                       const QString &endDate);

    QList<DockingRecord> getAllDockings();

    bool updateDocking(int id, const QString &location, const QString &length,
                       const QString &height, const QString &status,
                       const QString &capacity, const QString &startDate,
                       const QString &endDate);

    bool deleteDocking(int id);

private:
    QString getLastError();
};

#endif // DOCKING_H
