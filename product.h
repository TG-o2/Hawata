#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

#include <QDateTime>


class Product
{
public:

    Product();

    // Create a new product in the database
    bool createProduct(const QString &id,
                       const QString &type,
                       const QString &status,
                       const QString &quantity,
                       const QString &price,
                       const QString &fishCaughtTime,
                       const QString &dateOfPurchase,
                       const QString &location);

private:
    QString getLastError();

    enum class ProductStatus {
        InStock,
        Reserved,
        Available,
        Unavailable,
        Sold
    };

    // Constructor for adding new product (UI)
    Product(const QString &productCode,
            const QString &fishType,
            const QDateTime &catchDate,
            const QDateTime &catchTime,
            int quantity,
            ProductStatus status,
            double price);

    // Full constructor (for loading from file/database)
    Product(int productId,
            const QString &productCode,
            const QString &fishType,
            const QDateTime &catchDate,
            const QDateTime &catchTime,
            int quantity,
            ProductStatus status,
            double price,
            const QDateTime &createdAt);

    // Getters
    int getProductId() const;
    QString getProductCode() const;
    QString getFishType() const;
    QDateTime getCatchDate() const;
    QDateTime getCatchTime() const;
    int getQuantity() const;
    ProductStatus getStatus() const;
    double getPrice() const;
    QDateTime getCreatedAt() const;

    // Setters
    void setProductCode(const QString &value);
    void setFishType(const QString &value);
    void setCatchDate(const QDateTime &value);
    void setCatchTime(const QDateTime &value);
    void setQuantity(int value);
    void setStatus(ProductStatus value);
    void setPrice(double value);

    // Data persistence
    QString toFileString() const;

    // Helper to convert status enum to QString
    static QString statusToString(ProductStatus status);
    static ProductStatus stringToStatus(const QString &str);

private:
    int m_productId;
    QString m_productCode;
    QString m_fishType;
    QDateTime m_catchDate;
    QDateTime m_catchTime;
    int m_quantity;
    ProductStatus m_status;
    double m_price;
    QDateTime m_createdAt;

};

#endif // PRODUCT_H
