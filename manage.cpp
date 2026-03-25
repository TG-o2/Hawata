#include "manage.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Manage::Manage() {}

bool Manage::ajouter_manage(int userId, int dockId)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO MANAGE (USERID, DOCKID) VALUES (:userId, :dockId)");
    query.bindValue(":userId", userId);
    query.bindValue(":dockId", dockId);

    if (!query.exec()) {
        qDebug() << "Error inserting manage relation:" << query.lastError().text();
        return false;
    }

    return true;
}

QString Manage::getLastError()
{
    QSqlDatabase db = QSqlDatabase::database();
    return db.lastError().text();
}
