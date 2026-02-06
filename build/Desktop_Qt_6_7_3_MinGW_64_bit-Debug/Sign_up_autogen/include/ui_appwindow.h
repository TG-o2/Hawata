/********************************************************************************
** Form generated from reading UI file 'appwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPWINDOW_H
#define UI_APPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_appwindow
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page;
    QTabWidget *WebBrowsing;
    QWidget *tab;
    QToolBox *ToolBox_pages;
    QWidget *page_3;
    QPushButton *pushButton;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *passwordEdit;
    QComboBox *role_option;
    QLabel *logo;
    QLineEdit *firstNameEdit;
    QLabel *label_6;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *emailEdit;
    QLabel *label_7;
    QLineEdit *lastNameEdit;
    QLabel *label_8;
    QLineEdit *lastNameEdit_2;
    QComboBox *role_option_2;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *lastNameEdit_3;
    QPushButton *pushButton_2;
    QCalendarWidget *calendarWidget_2;
    QDateTimeEdit *dateTimeEdit;
    QDateTimeEdit *dateTimeEdit_2;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *icon;
    QWidget *page_4;
    QWidget *tab_3;
    QWidget *tab_4;
    QWidget *tab_5;
    QWidget *tab_2;
    QWidget *page_2;
    QTabWidget *WebBrowsing_2;
    QWidget *tab_6;
    QToolBox *page1;
    QWidget *page_5;
    QPushButton *pushButton_3;
    QLabel *label_14;
    QLabel *label_15;
    QComboBox *role_option_3;
    QLineEdit *firstNameEdit_2;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLineEdit *emailEdit_2;
    QLineEdit *lastNameEdit_4;
    QPushButton *pushButton_4;
    QDateTimeEdit *dateTimeEdit_3;
    QDateTimeEdit *dateTimeEdit_4;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_28;
    QLineEdit *emailEdit_4;
    QWidget *page_6;
    QWidget *tab_8;
    QTableView *tableView;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_29;
    QComboBox *comboBox;
    QPushButton *pushButton_7;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QWidget *tab_10;
    QGraphicsView *graphicsView;
    QLabel *label_42;
    QWidget *tab_11;
    QCalendarWidget *calendarWidget;
    QLabel *label_41;
    QWidget *tab_12;

    void setupUi(QDialog *appwindow)
    {
        if (appwindow->objectName().isEmpty())
            appwindow->setObjectName("appwindow");
        appwindow->resize(1434, 789);
        stackedWidget = new QStackedWidget(appwindow);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(259, 9, 1171, 781));
        page = new QWidget();
        page->setObjectName("page");
        WebBrowsing = new QTabWidget(page);
        WebBrowsing->setObjectName("WebBrowsing");
        WebBrowsing->setGeometry(QRect(-10, 0, 1251, 831));
        tab = new QWidget();
        tab->setObjectName("tab");
        ToolBox_pages = new QToolBox(tab);
        ToolBox_pages->setObjectName("ToolBox_pages");
        ToolBox_pages->setGeometry(QRect(20, 10, 1211, 731));
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        page_3->setGeometry(QRect(0, 0, 1211, 661));
        pushButton = new QPushButton(page_3);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(860, 420, 141, 51));
        label_2 = new QLabel(page_3);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 20, 441, 41));
        label_2->setStyleSheet(QString::fromUtf8("font-family: \"Arteks\";\n"
"font-size: 35px;\n"
"    font-weight: bold;\n"
"    color: #0a4c73;"));
        label_3 = new QLabel(page_3);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(490, 50, 111, 20));
        passwordEdit = new QLineEdit(page_3);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setGeometry(QRect(490, 300, 251, 31));
        role_option = new QComboBox(page_3);
        role_option->addItem(QString());
        role_option->addItem(QString());
        role_option->addItem(QString());
        role_option->setObjectName("role_option");
        role_option->setGeometry(QRect(820, 70, 151, 41));
        logo = new QLabel(page_3);
        logo->setObjectName("logo");
        logo->setGeometry(QRect(60, 70, 361, 241));
        logo->setStyleSheet(QString::fromUtf8(""));
        firstNameEdit = new QLineEdit(page_3);
        firstNameEdit->setObjectName("firstNameEdit");
        firstNameEdit->setGeometry(QRect(490, 80, 251, 31));
        label_6 = new QLabel(page_3);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(820, 40, 111, 20));
        label_4 = new QLabel(page_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(490, 120, 111, 20));
        label_5 = new QLabel(page_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(490, 200, 111, 20));
        emailEdit = new QLineEdit(page_3);
        emailEdit->setObjectName("emailEdit");
        emailEdit->setGeometry(QRect(490, 230, 251, 31));
        label_7 = new QLabel(page_3);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(490, 270, 111, 20));
        lastNameEdit = new QLineEdit(page_3);
        lastNameEdit->setObjectName("lastNameEdit");
        lastNameEdit->setGeometry(QRect(490, 150, 251, 31));
        label_8 = new QLabel(page_3);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(820, 120, 111, 20));
        lastNameEdit_2 = new QLineEdit(page_3);
        lastNameEdit_2->setObjectName("lastNameEdit_2");
        lastNameEdit_2->setGeometry(QRect(820, 150, 251, 31));
        role_option_2 = new QComboBox(page_3);
        role_option_2->addItem(QString());
        role_option_2->addItem(QString());
        role_option_2->setObjectName("role_option_2");
        role_option_2->setGeometry(QRect(820, 220, 151, 41));
        label_9 = new QLabel(page_3);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(820, 190, 111, 20));
        label_10 = new QLabel(page_3);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(820, 270, 111, 20));
        lastNameEdit_3 = new QLineEdit(page_3);
        lastNameEdit_3->setObjectName("lastNameEdit_3");
        lastNameEdit_3->setGeometry(QRect(820, 300, 251, 31));
        pushButton_2 = new QPushButton(page_3);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(860, 500, 141, 51));
        calendarWidget_2 = new QCalendarWidget(page_3);
        calendarWidget_2->setObjectName("calendarWidget_2");
        calendarWidget_2->setGeometry(QRect(220, 380, 320, 236));
        dateTimeEdit = new QDateTimeEdit(page_3);
        dateTimeEdit->setObjectName("dateTimeEdit");
        dateTimeEdit->setGeometry(QRect(570, 430, 221, 41));
        dateTimeEdit_2 = new QDateTimeEdit(page_3);
        dateTimeEdit_2->setObjectName("dateTimeEdit_2");
        dateTimeEdit_2->setGeometry(QRect(570, 510, 221, 41));
        label_11 = new QLabel(page_3);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(220, 350, 111, 20));
        label_12 = new QLabel(page_3);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(570, 400, 111, 20));
        label_13 = new QLabel(page_3);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(570, 480, 111, 20));
        icon = new QLabel(page_3);
        icon->setObjectName("icon");
        icon->setGeometry(QRect(1040, 40, 81, 71));
        icon->setStyleSheet(QString::fromUtf8(""));
        ToolBox_pages->addItem(page_3, QString::fromUtf8("Page 1"));
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        page_4->setGeometry(QRect(0, 0, 1211, 661));
        ToolBox_pages->addItem(page_4, QString::fromUtf8("Page 2"));
        WebBrowsing->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        WebBrowsing->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        WebBrowsing->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        WebBrowsing->addTab(tab_5, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        WebBrowsing->addTab(tab_2, QString());
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        WebBrowsing_2 = new QTabWidget(page_2);
        WebBrowsing_2->setObjectName("WebBrowsing_2");
        WebBrowsing_2->setGeometry(QRect(0, 0, 1251, 831));
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        page1 = new QToolBox(tab_6);
        page1->setObjectName("page1");
        page1->setGeometry(QRect(20, 10, 1211, 731));
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        page_5->setGeometry(QRect(0, 0, 98, 28));
        pushButton_3 = new QPushButton(page_5);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(860, 420, 181, 51));
        label_14 = new QLabel(page_5);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(30, 20, 441, 41));
        label_14->setStyleSheet(QString::fromUtf8("font-family: \"Arteks\";\n"
"font-size: 35px;\n"
"    font-weight: bold;\n"
"    color: #0a4c73;"));
        label_15 = new QLabel(page_5);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(490, 50, 111, 20));
        role_option_3 = new QComboBox(page_5);
        role_option_3->addItem(QString());
        role_option_3->addItem(QString());
        role_option_3->setObjectName("role_option_3");
        role_option_3->setGeometry(QRect(490, 300, 151, 41));
        firstNameEdit_2 = new QLineEdit(page_5);
        firstNameEdit_2->setObjectName("firstNameEdit_2");
        firstNameEdit_2->setGeometry(QRect(490, 80, 251, 31));
        label_16 = new QLabel(page_5);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(490, 270, 111, 20));
        label_17 = new QLabel(page_5);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(490, 120, 111, 20));
        label_18 = new QLabel(page_5);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(490, 200, 111, 20));
        emailEdit_2 = new QLineEdit(page_5);
        emailEdit_2->setObjectName("emailEdit_2");
        emailEdit_2->setGeometry(QRect(490, 230, 251, 31));
        lastNameEdit_4 = new QLineEdit(page_5);
        lastNameEdit_4->setObjectName("lastNameEdit_4");
        lastNameEdit_4->setGeometry(QRect(490, 150, 251, 31));
        pushButton_4 = new QPushButton(page_5);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(860, 500, 181, 51));
        dateTimeEdit_3 = new QDateTimeEdit(page_5);
        dateTimeEdit_3->setObjectName("dateTimeEdit_3");
        dateTimeEdit_3->setGeometry(QRect(840, 100, 221, 41));
        dateTimeEdit_4 = new QDateTimeEdit(page_5);
        dateTimeEdit_4->setObjectName("dateTimeEdit_4");
        dateTimeEdit_4->setGeometry(QRect(840, 180, 221, 41));
        label_24 = new QLabel(page_5);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(840, 70, 111, 20));
        label_25 = new QLabel(page_5);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(840, 150, 111, 20));
        label_28 = new QLabel(page_5);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(490, 370, 111, 20));
        emailEdit_4 = new QLineEdit(page_5);
        emailEdit_4->setObjectName("emailEdit_4");
        emailEdit_4->setGeometry(QRect(490, 400, 251, 31));
        page1->addItem(page_5, QString::fromUtf8("Page 1"));
        page_6 = new QWidget();
        page_6->setObjectName("page_6");
        page_6->setGeometry(QRect(0, 0, 98, 28));
        page1->addItem(page_6, QString::fromUtf8("Page 2"));
        WebBrowsing_2->addTab(tab_6, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName("tab_8");
        tableView = new QTableView(tab_8);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(410, 190, 691, 321));
        label = new QLabel(tab_8);
        label->setObjectName("label");
        label->setGeometry(QRect(422, 129, 71, 31));
        label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: Black;\n"
"    font-size: 18px;\n"
"    font-weight: bold;\n"
"    font-family: Arial;\n"
"}\n"
""));
        lineEdit = new QLineEdit(tab_8);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(510, 125, 251, 41));
        label_29 = new QLabel(tab_8);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(820, 120, 111, 51));
        label_29->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: Black;\n"
"    font-size: 18px;\n"
"    font-weight: bold;\n"
"    font-family: Arial;\n"
"}\n"
""));
        comboBox = new QComboBox(tab_8);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(920, 120, 161, 51));
        pushButton_7 = new QPushButton(tab_8);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(530, 540, 141, 51));
        pushButton_7->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #FF0000;\n"
"    color: white;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 8px 16px;\n"
"}\n"
""));
        pushButton_11 = new QPushButton(tab_8);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(710, 540, 141, 51));
        pushButton_11->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 8px 16px;\n"
"}\n"
""));
        pushButton_12 = new QPushButton(tab_8);
        pushButton_12->setObjectName("pushButton_12");
        pushButton_12->setGeometry(QRect(870, 540, 141, 51));
        pushButton_12->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 8px 16px;\n"
"}\n"
""));
        WebBrowsing_2->addTab(tab_8, QString());
        tab_10 = new QWidget();
        tab_10->setObjectName("tab_10");
        graphicsView = new QGraphicsView(tab_10);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(330, 200, 581, 361));
        label_42 = new QLabel(tab_10);
        label_42->setObjectName("label_42");
        label_42->setGeometry(QRect(140, 70, 131, 41));
        label_42->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: Black;\n"
"    font-size: 25px;\n"
"    font-weight: bold;\n"
"    font-family: Arial;\n"
"}\n"
""));
        WebBrowsing_2->addTab(tab_10, QString());
        tab_11 = new QWidget();
        tab_11->setObjectName("tab_11");
        calendarWidget = new QCalendarWidget(tab_11);
        calendarWidget->setObjectName("calendarWidget");
        calendarWidget->setGeometry(QRect(260, 160, 601, 451));
        label_41 = new QLabel(tab_11);
        label_41->setObjectName("label_41");
        label_41->setGeometry(QRect(100, 60, 171, 51));
        label_41->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: Black;\n"
"    font-size: 25px;\n"
"    font-weight: bold;\n"
"    font-family: Arial;\n"
"}\n"
""));
        WebBrowsing_2->addTab(tab_11, QString());
        tab_12 = new QWidget();
        tab_12->setObjectName("tab_12");
        WebBrowsing_2->addTab(tab_12, QString());
        stackedWidget->addWidget(page_2);

        retranslateUi(appwindow);

        stackedWidget->setCurrentIndex(0);
        WebBrowsing->setCurrentIndex(0);
        ToolBox_pages->setCurrentIndex(0);
        WebBrowsing_2->setCurrentIndex(1);
        page1->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(appwindow);
    } // setupUi

    void retranslateUi(QDialog *appwindow)
    {
        appwindow->setWindowTitle(QCoreApplication::translate("appwindow", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("appwindow", "Create User", nullptr));
        label_2->setText(QCoreApplication::translate("appwindow", "Create New User:", nullptr));
        label_3->setText(QCoreApplication::translate("appwindow", "First Name:", nullptr));
        role_option->setItemText(0, QCoreApplication::translate("appwindow", "Admin", nullptr));
        role_option->setItemText(1, QCoreApplication::translate("appwindow", "Manager", nullptr));
        role_option->setItemText(2, QCoreApplication::translate("appwindow", "Employee", nullptr));

        logo->setText(QCoreApplication::translate("appwindow", "Picture", nullptr));
        label_6->setText(QCoreApplication::translate("appwindow", "Choose Role", nullptr));
        label_4->setText(QCoreApplication::translate("appwindow", "Last Name:", nullptr));
        label_5->setText(QCoreApplication::translate("appwindow", "Email", nullptr));
        label_7->setText(QCoreApplication::translate("appwindow", "Password", nullptr));
        label_8->setText(QCoreApplication::translate("appwindow", "Salary", nullptr));
        role_option_2->setItemText(0, QCoreApplication::translate("appwindow", "Female", nullptr));
        role_option_2->setItemText(1, QCoreApplication::translate("appwindow", "Male", nullptr));

        label_9->setText(QCoreApplication::translate("appwindow", "Gender", nullptr));
        label_10->setText(QCoreApplication::translate("appwindow", "Salary", nullptr));
        pushButton_2->setText(QCoreApplication::translate("appwindow", "Check For User", nullptr));
        label_11->setText(QCoreApplication::translate("appwindow", "Shifts:", nullptr));
        label_12->setText(QCoreApplication::translate("appwindow", "Start of Shift", nullptr));
        label_13->setText(QCoreApplication::translate("appwindow", "End of Shift", nullptr));
        icon->setText(QCoreApplication::translate("appwindow", "user icon", nullptr));
        ToolBox_pages->setItemText(ToolBox_pages->indexOf(page_3), QCoreApplication::translate("appwindow", "Page 1", nullptr));
        ToolBox_pages->setItemText(ToolBox_pages->indexOf(page_4), QCoreApplication::translate("appwindow", "Page 2", nullptr));
        WebBrowsing->setTabText(WebBrowsing->indexOf(tab), QCoreApplication::translate("appwindow", "Tab 1", nullptr));
        WebBrowsing->setTabText(WebBrowsing->indexOf(tab_3), QCoreApplication::translate("appwindow", "Page", nullptr));
        WebBrowsing->setTabText(WebBrowsing->indexOf(tab_4), QCoreApplication::translate("appwindow", "Page", nullptr));
        WebBrowsing->setTabText(WebBrowsing->indexOf(tab_5), QCoreApplication::translate("appwindow", "Page", nullptr));
        WebBrowsing->setTabText(WebBrowsing->indexOf(tab_2), QCoreApplication::translate("appwindow", "Tab 2", nullptr));
        pushButton_3->setText(QCoreApplication::translate("appwindow", "Create Docking", nullptr));
        label_14->setText(QCoreApplication::translate("appwindow", "Create Docking:", nullptr));
        label_15->setText(QCoreApplication::translate("appwindow", "Location:", nullptr));
        role_option_3->setItemText(0, QCoreApplication::translate("appwindow", "Available", nullptr));
        role_option_3->setItemText(1, QCoreApplication::translate("appwindow", "Occupied", nullptr));

        label_16->setText(QCoreApplication::translate("appwindow", "Status:", nullptr));
        label_17->setText(QCoreApplication::translate("appwindow", "Length:", nullptr));
        label_18->setText(QCoreApplication::translate("appwindow", "Height:", nullptr));
        pushButton_4->setText(QCoreApplication::translate("appwindow", "Check For Docking", nullptr));
        label_24->setText(QCoreApplication::translate("appwindow", "Start Date", nullptr));
        label_25->setText(QCoreApplication::translate("appwindow", "End Date", nullptr));
        label_28->setText(QCoreApplication::translate("appwindow", "Capacity:", nullptr));
        page1->setItemText(page1->indexOf(page_5), QCoreApplication::translate("appwindow", "Page 1", nullptr));
        page1->setItemText(page1->indexOf(page_6), QCoreApplication::translate("appwindow", "Page 2", nullptr));
        WebBrowsing_2->setTabText(WebBrowsing_2->indexOf(tab_6), QCoreApplication::translate("appwindow", "Create", nullptr));
        label->setText(QCoreApplication::translate("appwindow", "Search", nullptr));
        label_29->setText(QCoreApplication::translate("appwindow", "Sorted By", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("appwindow", "Status", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("appwindow", "Capacity", nullptr));

        pushButton_7->setText(QCoreApplication::translate("appwindow", "Delete", nullptr));
        pushButton_11->setText(QCoreApplication::translate("appwindow", "Update", nullptr));
        pushButton_12->setText(QCoreApplication::translate("appwindow", "Export PDF", nullptr));
        WebBrowsing_2->setTabText(WebBrowsing_2->indexOf(tab_8), QCoreApplication::translate("appwindow", "Display", nullptr));
        label_42->setText(QCoreApplication::translate("appwindow", "Chart :", nullptr));
        WebBrowsing_2->setTabText(WebBrowsing_2->indexOf(tab_10), QCoreApplication::translate("appwindow", "Statistics", nullptr));
        label_41->setText(QCoreApplication::translate("appwindow", "Calender :", nullptr));
        WebBrowsing_2->setTabText(WebBrowsing_2->indexOf(tab_11), QCoreApplication::translate("appwindow", "Calender", nullptr));
        WebBrowsing_2->setTabText(WebBrowsing_2->indexOf(tab_12), QCoreApplication::translate("appwindow", "History", nullptr));
    } // retranslateUi

};

namespace Ui {
    class appwindow: public Ui_appwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPWINDOW_H
