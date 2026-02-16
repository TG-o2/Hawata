#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>
#include <QDateTime>

class Product
{
public:
    // Enums
    enum class ProductStatus {
        InStock,
        Reserved,
        Available,
        Unavailable,
        Sold
    };

    // Constructors
    Product();
    Product(const QString &productCode,
            const QString &fishType,
            const QDateTime &catchDate,
            const QDateTime &catchTime,
            int quantity,
            ProductStatus status,
            double price);

    // Database functions
    bool createProduct(const QString &id,
                       const QString &type,
                       const QString &status,
                       const QString &quantity,
                       const QString &price,
                       const QString &fishCaughtTime,
                       const QString &dateOfPurchase,
                       const QString &location);

    // Utility functions
    static QString statusToString(ProductStatus status);
    static ProductStatus stringToStatus(const QString &str);

private:
    QString getLastError();

    // Add member variables if needed
    QString m_productCode;
    QString m_fishType;
    QDateTime m_catchDate;
    QDateTime m_catchTime;
    int m_quantity;
    ProductStatus m_status;
    double m_price;

};

#endif // PRODUCT_H
