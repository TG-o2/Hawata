/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *Sign_in;
    QLabel *create_acc;
    QLineEdit *password_input;
    QLineEdit *firstName_input;
    QCheckBox *Remember_me;
    QLabel *logo;
    QLabel *label_7;
    QPushButton *Exit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(240, 20, 281, 41));
        label->setStyleSheet(QString::fromUtf8("font-family: \"Behove\";\n"
"font-size: 35px;\n"
"    font-weight: bold;\n"
"    color: #0a4c73;"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(470, 210, 161, 21));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(470, 320, 161, 21));
        Sign_in = new QPushButton(centralwidget);
        Sign_in->setObjectName("Sign_in");
        Sign_in->setGeometry(QRect(470, 370, 121, 41));
        create_acc = new QLabel(centralwidget);
        create_acc->setObjectName("create_acc");
        create_acc->setGeometry(QRect(470, 440, 291, 21));
        create_acc->setTextFormat(Qt::TextFormat::RichText);
        create_acc->setOpenExternalLinks(false);
        password_input = new QLineEdit(centralwidget);
        password_input->setObjectName("password_input");
        password_input->setGeometry(QRect(470, 250, 271, 41));
        firstName_input = new QLineEdit(centralwidget);
        firstName_input->setObjectName("firstName_input");
        firstName_input->setGeometry(QRect(470, 160, 271, 41));
        Remember_me = new QCheckBox(centralwidget);
        Remember_me->setObjectName("Remember_me");
        Remember_me->setGeometry(QRect(470, 310, 161, 24));
        logo = new QLabel(centralwidget);
        logo->setObjectName("logo");
        logo->setGeometry(QRect(30, 140, 411, 291));
        logo->setStyleSheet(QString::fromUtf8(""));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(470, 120, 161, 21));
        Exit = new QPushButton(centralwidget);
        Exit->setObjectName("Exit");
        Exit->setGeometry(QRect(610, 370, 121, 41));
        Exit->setStyleSheet(QString::fromUtf8(""));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "User Sign up", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        label_5->setText(QString());
        Sign_in->setText(QCoreApplication::translate("MainWindow", "Sign In", nullptr));
        Sign_in->setProperty("style", QVariant(QString()));
        create_acc->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" text-decoration: underline;\">forgot password?</span></p></body></html>", nullptr));
        Remember_me->setText(QCoreApplication::translate("MainWindow", "Remember Me", nullptr));
        logo->setText(QCoreApplication::translate("MainWindow", "Picture", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        Exit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        Exit->setProperty("style", QVariant(QCoreApplication::translate("MainWindow", "danger", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
