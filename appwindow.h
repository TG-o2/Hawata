#ifndef APPWINDOW_H
#define APPWINDOW_H
#include "Docking.h"
#include "user.h"
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

private:
    Ui::appwindow *ui;
    Docking dockingManager;
    User userManager;

};

#endif // APPWINDOW_H
