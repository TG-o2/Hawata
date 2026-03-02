#ifndef APPWINDOW_H
#define APPWINDOW_H

#include "user.h"
#include "connection.h"
#include "product.h"
#include "boats.h"
#include "company.h"
#include "Docking.h"
#include "manage.h"
#include <QDialog>

class QModelIndex;
class QSqlQueryModel;
class QTableWidgetItem;

namespace Ui {
class appwindow;
}

class appwindow : public QDialog
{
    Q_OBJECT

public:
    explicit appwindow(QWidget *parent = nullptr, int currentUserId = -1, const QString &currentUserRole = "");
    ~appwindow();

private slots:
    // ============================ START USER MODULE .h ============================
    // User CRUD slots 
    void fillUserForm(const QModelIndex &index);
    void on_UPDUser_clicked();
    void on_deleteUSERBtn_clicked();
    void on_editUSERBtn_clicked();
    void on_usersTable_cellClicked(int row, int column);
    void on_usersTable_cellDoubleClicked(int row, int column);
    void on_clear_3_clicked();
    // ============================ END USER MODULE .h ============================

    // docking CRUD
    void on_CreateDocking_clicked();
    void on_edit_Docking_clicked();
    void on_delete_docking_clicked();
    void on_tabdocking_cellDoubleClicked(int row, int column);
    void on_tabdocking_cellClicked(int row, int column);
    void on_clear_docking_clicked();
    void on_searchbar_docking_textChanged(const QString &text);
    void on_docking_sort_currentIndexChanged(int index);
    void on_export_docking_clicked();

    // product CRUD
    void on_checkProductButton_2_clicked();
    void on_checkProductButton_clicked();
    void on_Manage_24_clicked();
    void on_tableWidget_10_cellClicked(int row, int column);
    void on_tableWidget_10_cellDoubleClicked(int row, int column);
    void on_edit_company_6_clicked();
    void on_delete_company_6_clicked();
    void on_clear_6_clicked();
    void on_searchbar_6_textChanged(const QString &text);
    void on_comboBox_18_currentIndexChanged(int index);
    void on_export_pdf_6_clicked();
    void on_pushButton_12_clicked();

    // boats CRUD
    void on_addBoatButton_clicked();
    void on_deleteBoatButton_clicked();
    void on_updateBoatButton_clicked();
    void on_searchBoatButton_3_clicked();
    void on_Boatwidget_2_clicked(QTableWidgetItem *item);

    // companies CRUD
    void on_tableWidget_11_cellClicked(int row, int column);
    void on_tableWidget_11_cellDoubleClicked(int row, int column);
    void on_CreateUser_3_clicked();
    void on_edit_company_7_clicked();
    void on_delete_company_7_clicked();
    void on_clear_7_clicked();

private:
    Ui::appwindow *ui;

    // docks
    Docking dockingManager;
    Manage manageManager;
    int selectedDockingId = -1;
    void loadDockingTable();
    void populateDockingTable(const QList<DockingRecord> &records);
    QList<DockingRecord> allDockingRecords;

    // ============================ USER MODULE ============================
    // User state + managers used by User module integration
    User userManager;
    QSqlQueryModel *usersModel;
    int selectedUserId = -1;
    int connectedUserId = -1;
    QString connectedUserRole;
    void loadUsersTable();
    Connection conn;

    // products
    Product productManager;
    int selectedProductId = -1;
    void loadProductTable();
    QList<ProductRecord> allProductRecords;

    // boats
    void displayBoats();
    void clearBoatInputs();
    int currentlySelectedId;
    Boats boatsTmp;

    // companies
    void loadCompaniesTable();
    void fillCompanyForm(int row);
    Company companyManager;
    int selectedCompanyId = -1;
    
    // product statistics
    void generateProductStatisticsByStatus(const QList<ProductRecord> &products);
};

#endif // APPWINDOW_H
