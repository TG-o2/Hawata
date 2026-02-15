#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

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
};

#endif // PRODUCT_H
