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

// Add these missing constructor implementations
Product::Product(const QString &productCode,
                 const QString &fishType,
                 const QDateTime &catchDate,
                 const QDateTime &catchTime,
                 int quantity,
                 ProductStatus status,
                 double price)
{
    // Initialize member variables here
    // You need to add member variables to the class first
}

// Add these missing functions
QString Product::statusToString(ProductStatus status)
{
    switch(status) {
    case ProductStatus::InStock:
        return "In Stock";
    case ProductStatus::Reserved:
        return "Reserved";
    case ProductStatus::Available:
        return "Available";
    case ProductStatus::Unavailable:
        return "Unavailable";
    case ProductStatus::Sold:
        return "Sold";
    default:
        return "Unknown";
    }
}

Product::ProductStatus Product::stringToStatus(const QString &str)
{
    if (str == "In Stock") return ProductStatus::InStock;
    if (str == "Reserved") return ProductStatus::Reserved;
    if (str == "Available") return ProductStatus::Available;
    if (str == "Unavailable") return ProductStatus::Unavailable;
    if (str == "Sold") return ProductStatus::Sold;
    return ProductStatus::Available; // Default
}

QString Product::getLastError()
{
    QSqlDatabase db = QSqlDatabase::database();
    return db.lastError().text();
}
