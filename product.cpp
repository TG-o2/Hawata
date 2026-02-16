#include "product.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Product::Product()
{
    productsModel = new QSqlQueryModel();
}

Product::Product(const QString &productCode,
                 const QString &fishType,
                 const QDateTime &catchDate,
                 const QDateTime &catchTime,
                 int quantity,
                 ProductStatus status,
                 double price)
{
    m_productCode = productCode;
    m_fishType = fishType;
    m_catchDate = catchDate;
    m_catchTime = catchTime;
    m_quantity = quantity;
    m_status = status;
    m_price = price;
    productsModel = new QSqlQueryModel();
}

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

QSqlQueryModel* Product::getProductsModel()
{
    productsModel->setQuery("SELECT ID_D, TYPE, STATUS, QUANTITY, PRICE, "
                            "FISH_CAUGHT_TIME, DATE_OF_PURCHASE, LOCATION FROM PRODUCT");
    return productsModel;
}

bool Product::deleteProduct(const QString &id)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return false;
    QSqlQuery query;
    query.prepare("DELETE FROM PRODUCT WHERE ID_D = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Delete error:" << query.lastError().text();
        return false;
    }
    // refresh model
    productsModel->setQuery("SELECT ID_D, TYPE, STATUS, QUANTITY, PRICE, "
                            "FISH_CAUGHT_TIME, DATE_OF_PURCHASE, LOCATION FROM PRODUCT");
    return true;
}

bool Product::updateProduct(const QString &id,
                            const QString &type,
                            const QString &status,
                            int quantity,
                            double price,
                            const QString &location)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return false;
    QSqlQuery query;
    query.prepare("UPDATE PRODUCT SET TYPE = :type, STATUS = :status, "
                  "QUANTITY = :quantity, PRICE = :price, LOCATION = :location "
                  "WHERE ID_D = :id");
    query.bindValue(":type", type);
    query.bindValue(":status", status);
    query.bindValue(":quantity", quantity);
    query.bindValue(":price", price);
    query.bindValue(":location", location);
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Update error:" << query.lastError().text();
        return false;
    }
    // refresh model
    productsModel->setQuery("SELECT ID_D, TYPE, STATUS, QUANTITY, PRICE, "
                            "FISH_CAUGHT_TIME, DATE_OF_PURCHASE, LOCATION FROM PRODUCT");
    return true;
}

QString Product::statusToString(ProductStatus status)
{
    switch(status) {
    case ProductStatus::InStock: return "In Stock";
    case ProductStatus::Reserved: return "Reserved";
    case ProductStatus::Available: return "Available";
    case ProductStatus::Unavailable: return "Unavailable";
    case ProductStatus::Sold: return "Sold";
    default: return "Unknown";
    }
}

Product::ProductStatus Product::stringToStatus(const QString &str)
{
    if (str == "In Stock") return ProductStatus::InStock;
    if (str == "Reserved") return ProductStatus::Reserved;
    if (str == "Available") return ProductStatus::Available;
    if (str == "Unavailable") return ProductStatus::Unavailable;
    if (str == "Sold") return ProductStatus::Sold;
    return ProductStatus::Available;
}

QString Product::getLastError()
{
    QSqlDatabase db = QSqlDatabase::database();
    return db.lastError().text();
}
