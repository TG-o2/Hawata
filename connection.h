// connection.h
#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtSql>
#include <QDebug>

class Connection
{
public:
    Connection();
    ~Connection();
    bool openConnection();
private:
    QSqlDatabase db;
};

#endif // CONNECTION_H
