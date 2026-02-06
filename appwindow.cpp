#include "appwindow.h"
#include "ui_appwindow.h"
#include <QPixmap>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
appwindow::appwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::appwindow)
{
    ui->setupUi(this);

    //photo logo set up
    QPixmap pix("logoQt.png");
    QPixmap user_icon("user.png");
    ui->logo->setPixmap(pix);
    ui->logo->setScaledContents(true);
    ui->icon->setPixmap(user_icon);
    ui->icon->setScaledContents(true);
    //web / pages titles
    ui->WebBrowsing->setTabText(0, "Users Admission");
    ui->WebBrowsing->setTabText(1, "Test1");
    ui->WebBrowsing->setTabText(2, "Test2");

    //diferent bodies titles
    ui->ToolBox_pages->setItemText(0, "User Creation");
    ui->ToolBox_pages->setItemText(1, "Display");
}

appwindow::~appwindow()
{
    delete ui;
}
