#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QDialog>
#include <QStandardItemModel>
#include "product.h"
#include <QList>

namespace Ui {
class appwindow;
}

class appwindow : public QDialog
{
    Q_OBJECT

public:
    explicit appwindow(QWidget *parent = nullptr);
    ~appwindow();

private slots:
    // Product CRUD operations
    void on_checkProductButton_2_clicked();  // Add Product button
    void on_checkProductButton_clicked();    // Check/Display Products button
    void on_pushButton_24_clicked();         // Update Product button
    void on_pushButton_25_clicked();         // Delete Product button (if exists)
    
private:
    Ui::appwindow *ui;
    QList<Product> m_products;
    QStandardItemModel *m_productModel;
    
    // Product helper methods
    void loadProducts();
    void saveProducts();
    void displayProducts();
    void clearProductForm();
    int getNextProductId();
};

#endif // APPWINDOW_H
