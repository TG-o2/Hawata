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

    // If relation already exists, treat it as success (idempotent behavior).
    QSqlQuery existsQuery(db);
    existsQuery.prepare("SELECT 1 FROM MANAGE WHERE USERID = :userId AND DOCKID = :dockId");
    existsQuery.bindValue(":userId", userId);
    existsQuery.bindValue(":dockId", dockId);
    if (existsQuery.exec() && existsQuery.next()) {
        return true;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO MANAGE (USERID, DOCKID) VALUES (:userId, :dockId)");
    query.bindValue(":userId", userId);
    query.bindValue(":dockId", dockId);

    if (!query.exec()) {
        const QString errText = query.lastError().text();

        // ORA-00001: if USERID is unique in MANAGE, update existing row instead of failing.
        if (errText.contains("ORA-00001", Qt::CaseInsensitive)) {
            QSqlQuery updateQuery(db);
            updateQuery.prepare("UPDATE MANAGE SET DOCKID = :dockId WHERE USERID = :userId");
            updateQuery.bindValue(":dockId", dockId);
            updateQuery.bindValue(":userId", userId);
            if (updateQuery.exec() && updateQuery.numRowsAffected() > 0) {
                return true;
            }
        }

        qDebug() << "Error inserting manage relation:" << errText;
        return false;
    }

    return true;
}

QString Manage::getLastError()
{
    QSqlDatabase db = QSqlDatabase::database();
    return db.lastError().text();
}
