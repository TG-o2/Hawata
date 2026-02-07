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
    QPixmap pix("logoQt.png");
    ui->logo->setPixmap(pix);
    ui->logo->setScaledContents(true);


    //create account link
    ui->create_acc->setTextFormat(Qt::RichText);

    ui->create_acc->setText(
        "<a href=\"signup\">forgot password?</a>"
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

void MainWindow::openSignupPage()
{
    // Tu peux ouvrir la fenêtre signup ici plus tard
    qDebug() << "openSignupPage called";
}

void MainWindow::on_Create_clicked()
{
    qDebug() << "Create button clicked";

    CreateAcc create_account(this);
    create_account.exec();
}


void MainWindow::on_create_acc_linkActivated(const QString &link)
{
    qDebug() << "LINK CLICKED:" << link;

    CreateAcc create_account(this);
    create_account.exec();
}

void MainWindow::on_Sign_in_clicked()
{
    QString firstName = ui->firstName_input->text();
    QString password = ui->password_input->text();

    if (firstName.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter username and password.");
        return;
    }

    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Cannot open users file!");
        return;
    }

    bool found = false;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(";");
        if (parts.size() == 5) {
            QString fileUser = parts[3].trimmed();
            QString filePass = parts[4].trimmed();
            if (fileUser == firstName && filePass == password) {
                found = true;
                break;
            }
        }
    }

    file.close();

    if (found) {
        appwindow *app = new appwindow();
        app->show();

        // Close login window
        this->close();
    } else {
        QMessageBox::warning(this, "Error", "Username or password is incorrect.");
    }
}

