#include "product.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Product::Product() {}

bool Product::createProduct(const QString &id,
                            const QString &type,
                            const QString &status,
                            const QString &quantity,
                            const QString &price,
                            const QString &fishCaughtTime,
                            const QString &dateOfPurchase,
                            const QString &location)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO PRODUCT (ID_D, TYPE, STATUS, QUANTITY, PRICE, FISH_CAUGHT_TIME, DATE_OF_PURCHASE, LOCATION) "
                  "VALUES (:id, :type, :status, :quantity, :price, "
                  "TO_DATE(:fishCaughtTime, 'YYYY-MM-DD HH24:MI:SS'), "
                  "TO_DATE(:dateOfPurchase, 'YYYY-MM-DD HH24:MI:SS'), "
                  ":location)");

    query.bindValue(":id", id);
    query.bindValue(":type", type);
    query.bindValue(":status", status);
    query.bindValue(":quantity", quantity);
    query.bindValue(":price", price);
    query.bindValue(":fishCaughtTime", fishCaughtTime);
    query.bindValue(":dateOfPurchase", dateOfPurchase);
    query.bindValue(":location", location);

    if (!query.exec()) {
        qDebug() << "Error inserting product:" << query.lastError().text();
        return false;
    }

    qDebug() << "Product created successfully!";
    return true;
}

QString Product::getLastError()
{
    QSqlDatabase db = QSqlDatabase::database();
    return db.lastError().text();
}
