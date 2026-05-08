#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "appwindow.h"
#include "emailsender.h"
#include "arduino.h"


//libraries
#include <QApplication>
#include <QPixmap>
#include <QFontDatabase>
#include <QDebug>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTextStream>
#include <QMessageBox>
#include <QTimer>
QString normalizeUID(QString uid)
{
    return uid.toUpper()
    .remove(" ")
        .remove(":")
        .remove("-");
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //logo
    QPixmap pix("icons/try2.png");
    ui->logo->setPixmap(pix);
    ui->logo->setScaledContents(true);


    //forgot password for account link
    ui->forgot_password->setTextFormat(Qt::RichText);

    ui->forgot_password->setText(
        "<a href=\"signup\">forgot password?</a>"
        );
    ui->BackFrame->lower();
    ui->BackFrame->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #0369a1;"
        "border-radius: 16px;"
        );

    ui->forgot_password->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->forgot_password->setOpenExternalLinks(false);
    ui->forgot_password->setCursor(Qt::PointingHandCursor);


    //auto login part of user (special feature 1)

    QSettings settings("MyApp", "UserLogin");

    bool remember = settings.value("remember", false).toBool();

    if (remember) {
        int userId = settings.value("userId").toInt();
        QString role = settings.value("role").toString();

        qDebug() << "Auto login for user ID:" << userId;
        m_autoLoginTriggered = true;
        openAppWindow(userId, role);
    }


    /*

    //*************arduino with rfid***********

        arduino = new Arduino(this);
        const int arduinoStatus = arduino->connectArduino();
        qDebug() << "Arduino connect status:" << arduinoStatus;

        connect(arduino, &Arduino::cardScanned,
            this, [this](QString uid)
            {
                if (rfidBusy) return; 
                rfidBusy = true;

                uid = normalizeUID(uid);
                qDebug() << "RFID UID:" << uid;

                QSqlQuery debug("SELECT CardID FROM USERS");
                while (debug.next()) {
                    qDebug() << "DB UID:" << debug.value(0).toString();
                }
                qDebug() << "Checking UID in DB:" << uid;

                QSqlQuery query;
                query.prepare(
                    "SELECT USERID, ROLE FROM USERS "
                    "WHERE UPPER(REPLACE(REPLACE(REPLACE(CardID,' ',''),'-',''),':','')) = :uid"
                    );

                query.bindValue(":uid", uid);
                if (query.exec() && query.next()) {

                    int userId = query.value(0).toInt();
                    QString role = query.value(1).toString();

                    qDebug() << "Access GRANTED";
                    qDebug() << "Sending GRANTED to Arduino:" << arduino;
                    arduino->sendResponse("GRANTED");

                    QTimer::singleShot(300, this, [=]() {

                    arduino->close_arduino();   
                    qDebug() << "Arduino closed from MainWindow";

                    openAppWindow(userId, role);
                });

                } else {

                    qDebug() << "Access DENIED";
                    if (!query.lastError().text().isEmpty()) {
                        qDebug() << "RFID query error:" << query.lastError().text();
                    }

                    arduino->sendResponse("DENIED");

                    rfidBusy = false; // allow retry
                }
            });*/


}

bool MainWindow::isAutoLoginTriggered() const
{
    return m_autoLoginTriggered;
}

void MainWindow::openAppWindow(int userId, const QString &role)
{
    appwindow *app = new appwindow(nullptr, userId, role);
    app->setAttribute(Qt::WA_DeleteOnClose);
    app->show();
    this->close();
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
            QSettings settings("MyApp", "UserLogin");

            if (ui->Remember_me->isChecked()) {
                settings.setValue("userId", connectedUserId);
                settings.setValue("email", connectedEmail);
                settings.setValue("role", connectedUserRole);
                settings.setValue("remember", true);
            } else {
                settings.clear(); // remove saved login
            }
            qDebug() << "Connected user:" << connectedEmail << "ID:" << connectedUserId << "Role:" << connectedUserRole;
            openAppWindow(connectedUserId, connectedUserRole);
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

///forgot passwrd special feature user
void MainWindow::on_forgot_password_linkActivated(const QString &link)
{
    QString email = ui->firstName_input->text();

    if (email.isEmpty()) {
        QMessageBox::warning(this, "Error", "Enter your email");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT PASSWORD FROM USERS WHERE EMAIL = :email");
    query.bindValue(":email", email);

    if (!query.exec() || !query.next()) {
        QMessageBox::warning(this, "Error", "Email not found");
        return;
    }

    QString password = query.value(0).toString();

    EmailSender sender;

    QString subject = "Password Recovery";
    QString body = "Your password is: " + password;

    sender.sendEmail(email, subject, body);

    QMessageBox::information(this, "Success", "Password sent to your email");
}
