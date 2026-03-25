#ifndef MANAGE_H
#define MANAGE_H

#include <QString>

class Manage
{
public:
    Manage();

    bool ajouter_manage(int userId, int dockId);
    QString getLastError();
};

#endif // MANAGE_H
