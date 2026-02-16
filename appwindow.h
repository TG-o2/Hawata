#ifndef APPWINDOW_H
#define APPWINDOW_H
#include "Docking.h"
#include "user.h"
#include "company.h"
#include <QDialog>
#include <QFile>
#include <QFontDatabase>
#include <QDebug>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

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

    void on_CreateCompany_clicked();

    // Company CRUD operations
    void loadCompaniesTable();
    void on_edit_company_7_clicked();
    void on_delete_company_7_clicked();
    void on_searchbar_7_textChanged(const QString &text);
    void on_clear_7_clicked();

private:
    Ui::appwindow *ui;
    Docking dockingManager;
    User userManager;
    Company companyManager;

};

#endif // APPWINDOW_H
