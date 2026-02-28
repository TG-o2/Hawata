#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createacc.h"
#include "appwindow.h"


//libraries
#include <QPixmap>
#include <QFontDatabase>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //logo
    QPixmap pix("icons/try2.png");
    ui->logo->setPixmap(pix);
    ui->logo->setScaledContents(true);


    //create account link
    ui->create_acc->setTextFormat(Qt::RichText);

    ui->create_acc->setText(
        "<a href=\"signup\">forgot password?</a>"
        );
    ui->BackFrame->lower();
    ui->BackFrame->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #0369a1;"
        "border-radius: 16px;"
        );

    ui->create_acc->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->create_acc->setOpenExternalLinks(false);
    ui->create_acc->setCursor(Qt::PointingHandCursor);




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_logo_linkActivated(const QString &link)
{

}


void MainWindow::on_Exit_clicked()
{
    QApplication::quit();
}




void MainWindow::on_create_acc_linkActivated(const QString &link)
{
    qDebug() << "LINK CLICKED:" << link;

    CreateAcc create_account(this);
    create_account.exec();
}

void MainWindow::on_Sign_in_clicked()
{

    QSqlQuery query;
    query.prepare("SELECT USERID, EMAIL, ROLE FROM USERS WHERE EMAIL = :email AND PASSWORD = :password");

    query.bindValue(":email", ui->firstName_input->text());
    query.bindValue(":password", ui->password_input->text());

    if(query.exec())
    {
        if(query.next())
        {
            int connectedUserId = query.value(0).toInt();
            QString connectedEmail = query.value(1).toString();
            QString connectedUserRole = query.value(2).toString();
            qDebug() << "Connected user:" << connectedEmail << "ID:" << connectedUserId << "Role:" << connectedUserRole;
            appwindow *app = new appwindow(this, connectedUserId, connectedUserRole);
            app->show();
            this->hide();
        }
        else
        {
            QMessageBox::warning(this, "Login", "Invalid Login or Password");
        }
    }
    else
    {
        qDebug() << query.lastError();
    }

}
