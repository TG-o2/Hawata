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
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_appwindow
{
public:
    QTabWidget *WebBrowsing;
    QWidget *tab;
    QToolBox *ToolBox_pages;
    QWidget *page;
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
    QWidget *page_2;
    QWidget *tab_3;
    QToolBox *toolBox;
    QWidget *page_3;
    QTableWidget *tableWidget;
    QPushButton *Filterbutton;
    QLineEdit *lineEdit;
    QPushButton *pushButton_4;
    QScrollBar *verticalScrollBar;
    QToolBox *toolBox_2;
    QWidget *page_6;
    QLabel *label_22;
    QLabel *label_23;
    QLineEdit *lineEdit_8;
    QLabel *label_24;
    QLineEdit *lineEdit_9;
    QLabel *label_25;
    QLineEdit *lineEdit_10;
    QLabel *label_26;
    QLineEdit *lineEdit_12;
    QPushButton *pushButton_6;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *label_29;
    QLabel *label_31;
    QLabel *label_30;
    QLabel *label_32;
    QLabel *label_33;
    QWidget *page_8;
    QGraphicsView *graphicsView_3;
    QWidget *page_7;
    QLabel *label_34;
    QPushButton *pushButton_7;
    QPushButton *Filterbutton_2;
    QWidget *page_5;
    QLineEdit *lineEdit_2;
    QLabel *label;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QPushButton *pushButton_5;
    QLabel *label_18;
    QLineEdit *lineEdit_6;
    QWidget *page_4;
    QLabel *label_20;
    QLabel *label_21;
    QGraphicsView *graphicsView;
    QGraphicsView *graphicsView_2;
    QWidget *tab_4;
    QWidget *tab_5;
    QWidget *tab_2;
    QLabel *label_19;

    void setupUi(QDialog *appwindow)
    {
        if (appwindow->objectName().isEmpty())
            appwindow->setObjectName("appwindow");
        appwindow->resize(1256, 846);
        WebBrowsing = new QTabWidget(appwindow);
        WebBrowsing->setObjectName("WebBrowsing");
        WebBrowsing->setGeometry(QRect(0, 0, 1251, 571));
        tab = new QWidget();
        tab->setObjectName("tab");
        ToolBox_pages = new QToolBox(tab);
        ToolBox_pages->setObjectName("ToolBox_pages");
        ToolBox_pages->setGeometry(QRect(20, 10, 1211, 731));
        page = new QWidget();
        page->setObjectName("page");
        page->setGeometry(QRect(0, 0, 1211, 683));
        pushButton = new QPushButton(page);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(860, 420, 141, 51));
        label_2 = new QLabel(page);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 20, 441, 41));
        label_2->setStyleSheet(QString::fromUtf8("font-family: \"Arteks\";\n"
"font-size: 35px;\n"
"    font-weight: bold;\n"
"    color: #0a4c73;"));
        label_3 = new QLabel(page);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(490, 50, 111, 20));
        passwordEdit = new QLineEdit(page);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setGeometry(QRect(490, 300, 251, 31));
        role_option = new QComboBox(page);
        role_option->addItem(QString());
        role_option->addItem(QString());
        role_option->addItem(QString());
        role_option->setObjectName("role_option");
        role_option->setGeometry(QRect(820, 70, 151, 41));
        logo = new QLabel(page);
        logo->setObjectName("logo");
        logo->setGeometry(QRect(60, 70, 361, 241));
        logo->setStyleSheet(QString::fromUtf8(""));
        firstNameEdit = new QLineEdit(page);
        firstNameEdit->setObjectName("firstNameEdit");
        firstNameEdit->setGeometry(QRect(490, 80, 251, 31));
        label_6 = new QLabel(page);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(820, 40, 111, 20));
        label_4 = new QLabel(page);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(490, 120, 111, 20));
        label_5 = new QLabel(page);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(490, 200, 111, 20));
        emailEdit = new QLineEdit(page);
        emailEdit->setObjectName("emailEdit");
        emailEdit->setGeometry(QRect(490, 230, 251, 31));
        label_7 = new QLabel(page);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(490, 270, 111, 20));
        lastNameEdit = new QLineEdit(page);
        lastNameEdit->setObjectName("lastNameEdit");
        lastNameEdit->setGeometry(QRect(490, 150, 251, 31));
        label_8 = new QLabel(page);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(820, 120, 111, 20));
        lastNameEdit_2 = new QLineEdit(page);
        lastNameEdit_2->setObjectName("lastNameEdit_2");
        lastNameEdit_2->setGeometry(QRect(820, 150, 251, 31));
        role_option_2 = new QComboBox(page);
        role_option_2->addItem(QString());
        role_option_2->addItem(QString());
        role_option_2->setObjectName("role_option_2");
        role_option_2->setGeometry(QRect(820, 220, 151, 41));
        label_9 = new QLabel(page);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(820, 190, 111, 20));
        label_10 = new QLabel(page);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(820, 270, 111, 20));
        lastNameEdit_3 = new QLineEdit(page);
        lastNameEdit_3->setObjectName("lastNameEdit_3");
        lastNameEdit_3->setGeometry(QRect(820, 300, 251, 31));
        pushButton_2 = new QPushButton(page);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(860, 500, 141, 51));
        calendarWidget_2 = new QCalendarWidget(page);
        calendarWidget_2->setObjectName("calendarWidget_2");
        calendarWidget_2->setGeometry(QRect(220, 380, 320, 236));
        dateTimeEdit = new QDateTimeEdit(page);
        dateTimeEdit->setObjectName("dateTimeEdit");
        dateTimeEdit->setGeometry(QRect(570, 430, 221, 41));
        dateTimeEdit_2 = new QDateTimeEdit(page);
        dateTimeEdit_2->setObjectName("dateTimeEdit_2");
        dateTimeEdit_2->setGeometry(QRect(570, 510, 221, 41));
        label_11 = new QLabel(page);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(220, 350, 111, 20));
        label_12 = new QLabel(page);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(570, 400, 111, 20));
        label_13 = new QLabel(page);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(570, 480, 111, 20));
        icon = new QLabel(page);
        icon->setObjectName("icon");
        icon->setGeometry(QRect(1040, 40, 81, 71));
        icon->setStyleSheet(QString::fromUtf8(""));
        ToolBox_pages->addItem(page, QString::fromUtf8("Page 1"));
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        page_2->setGeometry(QRect(0, 0, 100, 30));
        ToolBox_pages->addItem(page_2, QString::fromUtf8("Page 2"));
        WebBrowsing->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        toolBox = new QToolBox(tab_3);
        toolBox->setObjectName("toolBox");
        toolBox->setGeometry(QRect(0, 10, 1231, 501));
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        page_3->setGeometry(QRect(0, 0, 1231, 429));
        tableWidget = new QTableWidget(page_3);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 60, 611, 421));
        Filterbutton = new QPushButton(page_3);
        Filterbutton->setObjectName("Filterbutton");
        Filterbutton->setGeometry(QRect(490, 10, 91, 21));
        lineEdit = new QLineEdit(page_3);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(30, 10, 151, 31));
        pushButton_4 = new QPushButton(page_3);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(200, 10, 91, 21));
        verticalScrollBar = new QScrollBar(page_3);
        verticalScrollBar->setObjectName("verticalScrollBar");
        verticalScrollBar->setGeometry(QRect(600, 150, 16, 160));
        verticalScrollBar->setOrientation(Qt::Orientation::Vertical);
        toolBox_2 = new QToolBox(page_3);
        toolBox_2->setObjectName("toolBox_2");
        toolBox_2->setGeometry(QRect(660, 40, 571, 341));
        page_6 = new QWidget();
        page_6->setObjectName("page_6");
        page_6->setGeometry(QRect(0, 0, 571, 269));
        label_22 = new QLabel(page_6);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(40, 120, 101, 21));
        label_23 = new QLabel(page_6);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(40, 30, 101, 21));
        lineEdit_8 = new QLineEdit(page_6);
        lineEdit_8->setObjectName("lineEdit_8");
        lineEdit_8->setGeometry(QRect(210, 60, 113, 20));
        label_24 = new QLabel(page_6);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(40, 90, 91, 21));
        lineEdit_9 = new QLineEdit(page_6);
        lineEdit_9->setObjectName("lineEdit_9");
        lineEdit_9->setGeometry(QRect(210, 90, 113, 20));
        label_25 = new QLabel(page_6);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(40, 60, 91, 31));
        lineEdit_10 = new QLineEdit(page_6);
        lineEdit_10->setObjectName("lineEdit_10");
        lineEdit_10->setGeometry(QRect(210, 30, 113, 20));
        label_26 = new QLabel(page_6);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(40, 150, 111, 21));
        lineEdit_12 = new QLineEdit(page_6);
        lineEdit_12->setObjectName("lineEdit_12");
        lineEdit_12->setGeometry(QRect(210, 120, 113, 20));
        pushButton_6 = new QPushButton(page_6);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(370, 147, 101, 41));
        label_27 = new QLabel(page_6);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(40, 180, 111, 21));
        label_28 = new QLabel(page_6);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(40, 210, 111, 21));
        label_29 = new QLabel(page_6);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(210, 150, 111, 21));
        label_31 = new QLabel(page_6);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(40, 0, 111, 21));
        label_30 = new QLabel(page_6);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(210, 180, 111, 21));
        label_32 = new QLabel(page_6);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(210, 210, 111, 21));
        label_33 = new QLabel(page_6);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(210, 0, 111, 21));
        toolBox_2->addItem(page_6, QString::fromUtf8("View Details"));
        page_8 = new QWidget();
        page_8->setObjectName("page_8");
        page_8->setGeometry(QRect(0, 0, 100, 30));
        graphicsView_3 = new QGraphicsView(page_8);
        graphicsView_3->setObjectName("graphicsView_3");
        graphicsView_3->setGeometry(QRect(80, 30, 401, 201));
        toolBox_2->addItem(page_8, QString::fromUtf8("live location"));
        page_7 = new QWidget();
        page_7->setObjectName("page_7");
        page_7->setGeometry(QRect(0, 0, 571, 289));
        label_34 = new QLabel(page_7);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(50, 30, 331, 41));
        QFont font;
        font.setPointSize(13);
        label_34->setFont(font);
        pushButton_7 = new QPushButton(page_7);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(255, 80, 91, 31));
        toolBox_2->addItem(page_7, QString::fromUtf8("Delete"));
        Filterbutton_2 = new QPushButton(page_3);
        Filterbutton_2->setObjectName("Filterbutton_2");
        Filterbutton_2->setGeometry(QRect(370, 10, 91, 21));
        toolBox->addItem(page_3, QString::fromUtf8("View"));
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        page_5->setGeometry(QRect(0, 0, 1231, 429));
        lineEdit_2 = new QLineEdit(page_5);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(210, 50, 113, 20));
        label = new QLabel(page_5);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 50, 101, 31));
        label_14 = new QLabel(page_5);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(40, 5, 131, 31));
        QFont font1;
        font1.setPointSize(15);
        label_14->setFont(font1);
        label_15 = new QLabel(page_5);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(40, 80, 91, 31));
        label_16 = new QLabel(page_5);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(40, 110, 91, 21));
        label_17 = new QLabel(page_5);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(40, 140, 101, 21));
        lineEdit_3 = new QLineEdit(page_5);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(210, 80, 113, 20));
        lineEdit_4 = new QLineEdit(page_5);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(210, 110, 113, 20));
        lineEdit_5 = new QLineEdit(page_5);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(210, 140, 113, 20));
        pushButton_5 = new QPushButton(page_5);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(220, 220, 91, 21));
        label_18 = new QLabel(page_5);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(40, 170, 111, 21));
        lineEdit_6 = new QLineEdit(page_5);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setGeometry(QRect(210, 170, 113, 20));
        toolBox->addItem(page_5, QString::fromUtf8("Add"));
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        page_4->setGeometry(QRect(0, 0, 1231, 429));
        label_20 = new QLabel(page_4);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(80, 20, 131, 16));
        label_21 = new QLabel(page_4);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(350, 15, 111, 21));
        graphicsView = new QGraphicsView(page_4);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(30, 50, 256, 192));
        graphicsView_2 = new QGraphicsView(page_4);
        graphicsView_2->setObjectName("graphicsView_2");
        graphicsView_2->setGeometry(QRect(330, 50, 256, 192));
        toolBox->addItem(page_4, QString::fromUtf8("Statistics"));
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
        label_19 = new QLabel(appwindow);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(750, 820, 37, 12));

        retranslateUi(appwindow);

        WebBrowsing->setCurrentIndex(1);
        ToolBox_pages->setCurrentIndex(0);
        toolBox->setCurrentIndex(0);
        toolBox_2->setCurrentIndex(0);


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
        ToolBox_pages->setItemText(ToolBox_pages->indexOf(page), QCoreApplication::translate("appwindow", "Page 1", nullptr));
        ToolBox_pages->setItemText(ToolBox_pages->indexOf(page_2), QCoreApplication::translate("appwindow", "Page 2", nullptr));
        WebBrowsing->setTabText(WebBrowsing->indexOf(tab), QCoreApplication::translate("appwindow", "Tab 1", nullptr));
#if QT_CONFIG(tooltip)
        toolBox->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        toolBox->setWhatsThis(QCoreApplication::translate("appwindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("appwindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("appwindow", "Owner name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("appwindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("appwindow", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("appwindow", "Details", nullptr));
        Filterbutton->setText(QCoreApplication::translate("appwindow", "By Status", nullptr));
        lineEdit->setText(QString());
        lineEdit->setPlaceholderText(QString());
        pushButton_4->setText(QCoreApplication::translate("appwindow", "Search", nullptr));
        label_22->setText(QCoreApplication::translate("appwindow", "Size", nullptr));
        label_23->setText(QCoreApplication::translate("appwindow", "Owner name", nullptr));
        label_24->setText(QCoreApplication::translate("appwindow", "Type", nullptr));
        label_25->setText(QCoreApplication::translate("appwindow", "Owner Email", nullptr));
        label_26->setText(QCoreApplication::translate("appwindow", "Status", nullptr));
        pushButton_6->setText(QCoreApplication::translate("appwindow", "Save", nullptr));
        label_27->setText(QCoreApplication::translate("appwindow", "Number of trips", nullptr));
        label_28->setText(QCoreApplication::translate("appwindow", "Total fish caught", nullptr));
        label_29->setText(QCoreApplication::translate("appwindow", "OUT", nullptr));
        label_31->setText(QCoreApplication::translate("appwindow", "Boat ID", nullptr));
        label_30->setText(QCoreApplication::translate("appwindow", "0", nullptr));
        label_32->setText(QCoreApplication::translate("appwindow", "0", nullptr));
        label_33->setText(QCoreApplication::translate("appwindow", "ID", nullptr));
        toolBox_2->setItemText(toolBox_2->indexOf(page_6), QCoreApplication::translate("appwindow", "View Details", nullptr));
        toolBox_2->setItemText(toolBox_2->indexOf(page_8), QCoreApplication::translate("appwindow", "live location", nullptr));
        label_34->setText(QCoreApplication::translate("appwindow", "Are you sure you want to delete this ship?", nullptr));
        pushButton_7->setText(QCoreApplication::translate("appwindow", "Delete", nullptr));
        toolBox_2->setItemText(toolBox_2->indexOf(page_7), QCoreApplication::translate("appwindow", "Delete", nullptr));
        Filterbutton_2->setText(QCoreApplication::translate("appwindow", "By Type", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_3), QCoreApplication::translate("appwindow", "View", nullptr));
        label->setText(QCoreApplication::translate("appwindow", "Owner name", nullptr));
        label_14->setText(QCoreApplication::translate("appwindow", "Add Boat", nullptr));
        label_15->setText(QCoreApplication::translate("appwindow", "Owner Email", nullptr));
        label_16->setText(QCoreApplication::translate("appwindow", "Type", nullptr));
        label_17->setText(QCoreApplication::translate("appwindow", "Size", nullptr));
        pushButton_5->setText(QCoreApplication::translate("appwindow", "Save", nullptr));
        label_18->setText(QCoreApplication::translate("appwindow", "Last maintenance date", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_5), QCoreApplication::translate("appwindow", "Add", nullptr));
        label_20->setText(QCoreApplication::translate("appwindow", "Boat trips", nullptr));
        label_21->setText(QCoreApplication::translate("appwindow", "Fish caught", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_4), QCoreApplication::translate("appwindow", "Statistics", nullptr));
        WebBrowsing->setTabText(WebBrowsing->indexOf(tab_3), QCoreApplication::translate("appwindow", "Boats", nullptr));
        WebBrowsing->setTabText(WebBrowsing->indexOf(tab_4), QCoreApplication::translate("appwindow", "Page", nullptr));
        WebBrowsing->setTabText(WebBrowsing->indexOf(tab_5), QCoreApplication::translate("appwindow", "Page", nullptr));
        WebBrowsing->setTabText(WebBrowsing->indexOf(tab_2), QCoreApplication::translate("appwindow", "Tab 2", nullptr));
        label_19->setText(QCoreApplication::translate("appwindow", "Type", nullptr));
    } // retranslateUi

};

namespace Ui {
    class appwindow: public Ui_appwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPWINDOW_H
