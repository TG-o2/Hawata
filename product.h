#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>
#include <QDateTime>
#include <QList>

struct ProductRecord {
    int id;
    QString type;
    QString location;
    QString status;
    int quantity;
    double price;
    QString fishCaught;
    QString dateOfPurchase;
};

class Product
{
public:
    enum class ProductStatus {
        InStock,
        Reserved,
        Available,
        Unavailable,
        Sold
    };

    Product();
    Product(const QString &type,
            const QString &location,
            const QDateTime &fishCaught,
            const QDateTime &dateOfPurchase,
            int quantity,
            ProductStatus status,
            double price);

    bool createProduct(const QString &type,
                       const QString &location,
                       const QString &status,
                       int quantity,
                       double price,
                       const QDateTime &fishCaught,
                       const QDateTime &dateOfPurchase);

    QList<ProductRecord> getAllProducts();

    bool updateProduct(int id,
                       const QString &type,
                       const QString &location,
                       const QString &status,
                       int quantity,
                       double price,
                       const QDateTime &fishCaught,
                       const QDateTime &dateOfPurchase);

    bool deleteProduct(int id);

    QString statusToString(ProductStatus status);
    ProductStatus stringToStatus(const QString &str);

private:
    QString getLastError();
    QString m_type;
    QString m_location;
    QDateTime m_fishCaught;
    QDateTime m_dateOfPurchase;
    int m_quantity;
    ProductStatus m_status;
    double m_price;
};

#endif // PRODUCT_H
