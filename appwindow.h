#ifndef APPWINDOW_H
#define APPWINDOW_H

#include "Docking.h"
#include "user.h"
#include "connection.h"
#include "product.h"

#include <QDialog>
#include <QFile>
#include <QFontDatabase>
#include <QDebug>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPixmap>
#include <QTextStream>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include <QStandardItem>

#include <QPixmap>
#include <QTextStream>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include <QStandardItem>

namespace Ui {
class appwindow;
}

class appwindow : public QDialog
{
    Q_OBJECT

public:
    explicit appwindow(QWidget *parent = nullptr);
    ~appwindow();
    void fillUserForm(const QModelIndex &index);
private slots:
    ///user CRUD
    void on_UPDUser_clicked();
    void on_deleteUSERBtn_clicked();
    void on_editUSERBtn_clicked();
    void on_usersTable_cellClicked(int row, int column);
    void on_usersTable_cellDoubleClicked(int row, int column);
    void on_clear_3_clicked();
    ///docking crud
    void on_CreateDocking_clicked();
    void on_delete_docking_clicked();
    void on_tabdocking_cellDoubleClicked(int row, int column);
    void on_tabdocking_cellClicked(int row, int column);
    void on_clear_docking_clicked();
    void on_edit_Docking_clicked();
    ///product CRUD
    void on_checkProductButton_2_clicked();
    void on_checkProductButton_clicked();
    void on_Manage_24_clicked();
    void on_tableWidget_10_cellClicked(int row, int column);
    void on_tableWidget_10_cellDoubleClicked(int row, int column);
    void on_edit_company_6_clicked();
    void on_delete_company_6_clicked();
    void on_clear_6_clicked();



private:
    Ui::appwindow *ui;
    //docks
    Docking dockingManager;
    int selectedDockingId = -1;
    void loadDockingTable();
    //users
    User userManager;
    QSqlQueryModel *usersModel;
    int selectedUserId = -1;
    void loadUsersTable();
    Connection conn;

    Product productManager;
    int selectedProductId = -1;
    void loadProductTable();
};

#endif // APPWINDOW_H
