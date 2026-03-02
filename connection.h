#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>

class Connection
{
public:
    Connection();
    bool createconnect();
    QString lastError() const;

private:
    QString m_lastError;
};

#endif // CONNECTION_H
