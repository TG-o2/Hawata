#ifndef APPWINDOW_H
#define APPWINDOW_H
#include "Docking.h"
#include "user.h"
#include "product.h"
#include <QDialog>

#include <QFile>
#include <QFontDatabase>
#include <QDebug>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
=======
#include <QStandardItemModel>
#include <QSqlDatabase>
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

    void on_CreateDocking_clicked();

    void on_CreateUser_clicked();
    void on_checkProductButton_2_clicked();

private:
    Ui::appwindow *ui;
    Docking dockingManager;
    User userManager;
     Product productManager;

=======
    // Product CRUD operations
    void on_checkProductButton_2_clicked();  // Add Product button
    void on_checkProductButton_clicked();    // Check/Display Products button
    void on_pushButton_24_clicked();         // Update Product button
    void on_pushButton_25_clicked();         // Delete Product button (if exists)
    
private:
    Ui::appwindow *ui;
    QList<Product> m_products;
    QStandardItemModel *m_productModel;
    QSqlDatabase m_database;
    
    // Database helper methods
    bool connectToDatabase();
    void createProductTable();
    
    // Product helper methods
    void loadProductsFromDB();
    void displayProducts();
    void clearProductForm();
    int getNextProductId();

};

#endif // APPWINDOW_H
