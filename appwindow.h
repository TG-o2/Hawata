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
    void on_CreateDocking_clicked();
    void on_CreateUser_clicked();
    void on_checkProductButton_2_clicked();  // ONLY ONCE!

    void on_deleteUSERBtn_clicked();

    void on_editUSERBtn_clicked();

private:
    Ui::appwindow *ui;
    //docks
    Docking dockingManager;
    //users
    User userManager;
    QSqlQueryModel *usersModel;
    Connection conn;

    Product productManager;
};

#endif // APPWINDOW_H
