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


// ---- Constructors ----

// Constructor for adding new product
Product::Product(const QString &productCode,
                 const QString &fishType,
                 const QDateTime &catchDate,
                 const QDateTime &catchTime,
                 int quantity,
                 ProductStatus status,
                 double price)
    : m_productId(0),                       // Default, will be set when saving
      m_productCode(productCode),
      m_fishType(fishType),
      m_catchDate(catchDate),
      m_catchTime(catchTime),
      m_quantity(quantity),
      m_status(status),
      m_price(price),
      m_createdAt(QDateTime::currentDateTime())
{
}

// Full constructor for loading from file/database
Product::Product(int productId,
                 const QString &productCode,
                 const QString &fishType,
                 const QDateTime &catchDate,
                 const QDateTime &catchTime,
                 int quantity,
                 ProductStatus status,
                 double price,
                 const QDateTime &createdAt)
    : m_productId(productId),
      m_productCode(productCode),
      m_fishType(fishType),
      m_catchDate(catchDate),
      m_catchTime(catchTime),
      m_quantity(quantity),
      m_status(status),
      m_price(price),
      m_createdAt(createdAt)
{
}

// ---- Getters ----

int Product::getProductId() const { return m_productId; }
QString Product::getProductCode() const { return m_productCode; }
QString Product::getFishType() const { return m_fishType; }
QDateTime Product::getCatchDate() const { return m_catchDate; }
QDateTime Product::getCatchTime() const { return m_catchTime; }
int Product::getQuantity() const { return m_quantity; }
Product::ProductStatus Product::getStatus() const { return m_status; }
double Product::getPrice() const { return m_price; }
QDateTime Product::getCreatedAt() const { return m_createdAt; }

// ---- Setters ----

void Product::setProductCode(const QString &value) { m_productCode = value; }
void Product::setFishType(const QString &value) { m_fishType = value; }
void Product::setCatchDate(const QDateTime &value) { m_catchDate = value; }
void Product::setCatchTime(const QDateTime &value) { m_catchTime = value; }
void Product::setQuantity(int value) { m_quantity = value; }
void Product::setStatus(ProductStatus value) { m_status = value; }
void Product::setPrice(double value) { m_price = value; }

// ---- Data Persistence ----

QString Product::toFileString() const
{
    return QString::number(m_productId) + ";" +
           m_productCode + ";" +
           m_fishType + ";" +
           m_catchDate.toString(Qt::ISODate) + ";" +
           m_catchTime.toString(Qt::ISODate) + ";" +
           QString::number(m_quantity) + ";" +
           QString::number(static_cast<int>(m_status)) + ";" +
           QString::number(m_price, 'f', 2) + ";" +
           m_createdAt.toString(Qt::ISODate);
}

// ---- Helper Methods ----

QString Product::statusToString(ProductStatus status)
{
    switch (status) {
    case ProductStatus::InStock:    return "In Stock";
    case ProductStatus::Reserved:   return "Reserved";
    case ProductStatus::Available:  return "Available";
    case ProductStatus::Unavailable:return "Unavailable";
    case ProductStatus::Sold:       return "Sold";
    default:                        return "Unknown";
    }
}

Product::ProductStatus Product::stringToStatus(const QString &str)
{
    if (str == "In Stock")      return ProductStatus::InStock;
    if (str == "Reserved")      return ProductStatus::Reserved;
    if (str == "Available")     return ProductStatus::Available;
    if (str == "Unavailable")   return ProductStatus::Unavailable;
    if (str == "Sold")          return ProductStatus::Sold;
    return ProductStatus::Available; // Default

}
