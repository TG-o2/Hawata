#include "product.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QList>
Product::Product(const QString &type,
                 const QString &location,
                 const QDateTime &fishCaught,
                 const QDateTime &dateOfPurchase,
                 int quantity,
                 ProductStatus status,
                 double price)
    : m_type(type),
    m_location(location),
    m_fishCaught(fishCaught),
    m_dateOfPurchase(dateOfPurchase),
    m_quantity(quantity),
    m_status(status),
    m_price(price)
{
}
Product::Product() {}

/*
  Correct version:
  - No ID (Oracle identity handles it)
  - Correct column names
  - Correct data types
  - No TO_DATE (Qt handles QDateTime automatically)
*/
bool Product::createProduct(const QString &type,
                            const QString &location,
                            const QString &status,
                            int quantity,
                            double price,
                            const QDateTime &fishCaught,
                            const QDateTime &dateOfPurchase)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);

    query.prepare("INSERT INTO products "
                  "(type, status, location, quantity, price, fish_caught, dateofpurchase) "
                  "VALUES (:type, :status, :location, :quantity, :price, :fishCaught, :dateOfPurchase)");

    query.bindValue(":type", type);
    query.bindValue(":status", status);
    query.bindValue(":location", location);
    query.bindValue(":quantity", quantity);
    query.bindValue(":price", price);
    query.bindValue(":fishCaught", fishCaught);
    query.bindValue(":dateOfPurchase", dateOfPurchase);

    if (!query.exec()) {
        qDebug() << "Error inserting product:" << query.lastError().text();
        return false;
    }

    qDebug() << "Product created successfully!";
    return true;
}

QList<ProductRecord> Product::getAllProducts()
{
    QList<ProductRecord> records;
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return records;
    }

    QSqlQuery query(db);
    query.prepare("SELECT productid, type, location, status, quantity, price, fish_caught, dateofpurchase FROM products");

    if (!query.exec()) {
        qDebug() << "Error fetching products:" << query.lastError().text();
        return records;
    }

    while (query.next()) {
        ProductRecord record;
        record.id = query.value(0).toInt();
        record.type = query.value(1).toString();
        record.location = query.value(2).toString();
        record.status = query.value(3).toString();
        record.quantity = query.value(4).toInt();
        record.price = query.value(5).toDouble();
        record.fishCaught = query.value(6).toString();
        record.dateOfPurchase = query.value(7).toString();
        records.append(record);
    }

    qDebug() << "Fetched" << records.size() << "product records";
    return records;
}

bool Product::updateProduct(int id,
                            const QString &type,
                            const QString &location,
                            const QString &status,
                            int quantity,
                            double price,
                            const QDateTime &fishCaught,
                            const QDateTime &dateOfPurchase)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE products SET type = :type, location = :location, status = :status, "
                  "quantity = :quantity, price = :price, fish_caught = :fishCaught, "
                  "dateofpurchase = :dateOfPurchase WHERE productid = :id");

    query.addBindValue(type);
    query.addBindValue(location);
    query.addBindValue(status);
    query.addBindValue(quantity);
    query.addBindValue(price);
    query.addBindValue(fishCaught);
    query.addBindValue(dateOfPurchase);
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << "Error updating product:" << query.lastError().text();
        return false;
    }

    qDebug() << "Product updated successfully!";
    return true;
}

bool Product::deleteProduct(int id)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("DELETE FROM products WHERE productid = :id");
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << "Error deleting product:" << query.lastError().text();
        return false;
    }

    qDebug() << "Product deleted successfully!";
    return true;
}

QString Product::getLastError()
{
    QSqlDatabase db = QSqlDatabase::database();
    return db.lastError().text();
}

QString Product::statusToString(ProductStatus status)
{
    switch(status) {
    case ProductStatus::InStock: return "InStock";
    case ProductStatus::Reserved: return "Reserved";
    case ProductStatus::Available: return "Available";
    case ProductStatus::Unavailable: return "Unavailable";
    case ProductStatus::Sold: return "Sold";
    }
    return "Available";
}

Product::ProductStatus Product::stringToStatus(const QString &str)
{
    if (str == "InStock") return ProductStatus::InStock;
    if (str == "Reserved") return ProductStatus::Reserved;
    if (str == "Available") return ProductStatus::Available;
    if (str == "Unavailable") return ProductStatus::Unavailable;
    if (str == "Sold") return ProductStatus::Sold;

    return ProductStatus::Available;
}
