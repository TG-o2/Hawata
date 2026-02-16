#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QDebug>

class Connection
{
public:
    Connection();
    ~Connection();

    bool openConnection();

    QSqlDatabase db;

};

#endif // CONNECTION_H
