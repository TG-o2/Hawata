#include "appwindow.h"
#include "ui_appwindow.h"
#include "mainwindow.h"


#include <QPixmap>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QTableWidgetItem>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>


appwindow::appwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::appwindow)
    , m_productModel(new QStandardItemModel(this))
{
    ui->setupUi(this);

    // Initialize product table model
    m_productModel->setHorizontalHeaderLabels(
        QStringList() << "ID" << "Code" << "Fish Type" << "Catch Date" 
                      << "Quantity" << "Status" << "Price" << "Created At"
    );
    ui->tableView_5->setModel(m_productModel);
    ui->tableView_5->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_5->setSelectionMode(QAbstractItemView::SingleSelection);

    // Connect to database and create table if needed
    if (connectToDatabase()) {
        createProductTable();
    } else {
        QMessageBox::warning(this, "Database Error", "Failed to connect to database. Product features may not work.");
    }

    //photo logo set up

    QPixmap logo("icons/try1.png");

    QPixmap Uicon("icons/add-user2.png");
    QPixmap Dock("icons/dock.png");
    QPixmap Boat("icons/boat.png");
    QPixmap Prod("icons/prod.png");
    QPixmap Email("icons/Email.png");
    QPixmap Comp("icons/companies.png");
    QPixmap Stats("icons/stats.png");

    QPixmap user_icon("icons/add-user1.png");
    QPixmap user_display("icons/dashboard.png");
    QPixmap user_delete("icons/trash.png");
    QPixmap Calendar("icons/display.png");
    QPixmap live("icons/live.png");

    //pictures for product--------
    QPixmap fish("icons/fishicon.png");
    QPixmap pic_2("icons/logoQT.png");
    QPixmap homepage("icons/Ports1.jpg");
    QPixmap waves("icons/wave.jpg");
    //product picture set up
    ui->pic->setPixmap(fish);
    ui->pic->setScaledContents(true);




    //end of product picture code--------------

    //chart for page 4 of window 1 (User management)


    ///----add manage display

    //user page
    //1
    ui->adduser->setPixmap(user_icon);
    ui->adduser->setScaledContents(true);

    ui->Usericon->setPixmap(Uicon);
    ui->Usericon->setScaledContents(true);


    ui->deluser->setPixmap(user_delete);
    ui->deluser->setScaledContents(true);

    ui->dispuser->setPixmap(user_display);
    ui->dispuser->setScaledContents(true);

    //2
    ui->adduser_2->setPixmap(user_icon);
    ui->adduser_2->setScaledContents(true);

    ui->deluser_2->setPixmap(user_delete);
    ui->deluser_2->setScaledContents(true);

    ui->dispuser_2->setPixmap(user_display);
    ui->dispuser_2->setScaledContents(true);

    //3
    ui->adduser_3->setPixmap(user_icon);
    ui->adduser_3->setScaledContents(true);

    ui->deluser_3->setPixmap(user_delete);
    ui->deluser_3->setScaledContents(true);

    ui->dispuser_3->setPixmap(user_display);
    ui->dispuser_3->setScaledContents(true);

    //dock page 1 2 3 4
    ui->Dock1->setPixmap(Dock);
    ui->Dock1->setScaledContents(true);

    ui->deluser_17->setPixmap(user_delete);
    ui->deluser_17->setScaledContents(true);

    ui->dispuser_17->setPixmap(user_display);
    ui->dispuser_17->setScaledContents(true);

    ui->Dock3->setPixmap(Dock);
    ui->Dock3->setScaledContents(true);

    ui->deluser_5->setPixmap(user_delete);
    ui->deluser_5->setScaledContents(true);

    ui->dispuser_5->setPixmap(user_display);
    ui->dispuser_5->setScaledContents(true);

    ui->Dock4->setPixmap(Dock);
    ui->Dock4->setScaledContents(true);

    ui->deluser_6->setPixmap(user_delete);
    ui->deluser_6->setScaledContents(true);
    ui->dispuser_5->setPixmap(user_display);
    ui->dispuser_5->setScaledContents(true);

    ui->Dock4->setPixmap(Dock);
    ui->Dock4->setScaledContents(true);

    ui->deluser_6->setPixmap(user_delete);
    ui->deluser_6->setScaledContents(true);

    ui->dispuser_6->setPixmap(user_display);
    ui->dispuser_6->setScaledContents(true);
    //boat page 7,8 & 9
    ui->Dock1->setPixmap(user_display);
    ui->Dock2->setScaledContents(true);

    ui->deluser_18->setPixmap(user_delete);
    ui->deluser_18->setScaledContents(true);

    ui->dispuser_18->setPixmap(Stats);
    ui->dispuser_18->setScaledContents(true);

    ui->Dock2->setPixmap(user_display);
    ui->Dock2->setScaledContents(true);

    ui->deluser_18->setPixmap(user_delete);
    ui->deluser_18->setScaledContents(true);

    ui->dispuser_18->setPixmap(Stats);
    ui->dispuser_18->setScaledContents(true);

    ui->Dock3->setPixmap(user_display);
    ui->Dock3->setScaledContents(true);

    ui->cal1->setPixmap(Calendar);
    ui->cal1->setScaledContents(true);

    ui->cal2->setPixmap(Calendar);
    ui->cal2->setScaledContents(true);

    ui->cal3->setPixmap(Calendar);
    ui->cal3->setScaledContents(true);

    ui->cal4->setPixmap(Calendar);
    ui->cal4->setScaledContents(true);
    //PRODUCT pages

    ui->Addboat1->setPixmap(Boat);
    ui->Addboat1->setScaledContents(true);
    ui->Addboat2->setPixmap(Boat);
    ui->Addboat2->setScaledContents(true);
    ui->Addboat3->setPixmap(Boat);
    ui->Addboat3->setScaledContents(true);
    ui->Addboat4->setPixmap(Boat);
    ui->Addboat4->setScaledContents(true);


    ui->ManBoat1->setPixmap(user_display);
    ui->ManBoat1->setScaledContents(true);
    ui->ManBoat2->setPixmap(user_display);
    ui->ManBoat2->setScaledContents(true);
    ui->ManBoat3->setPixmap(user_display);
    ui->ManBoat3->setScaledContents(true);
    ui->ManBoat4->setPixmap(user_display);
    ui->ManBoat4->setScaledContents(true);


    ui->dispboat3->setPixmap(Stats);
    ui->dispboat3->setScaledContents(true);
    ui->dispboat2->setPixmap(Stats);
    ui->dispboat2->setScaledContents(true);
    ui->dispboat1->setPixmap(Stats);
    ui->dispboat1->setScaledContents(true);
    ui->dispboat4->setPixmap(Stats);
    ui->dispboat4->setScaledContents(true);

    ui->Live1->setPixmap(live);
    ui->Live1->setScaledContents(true);
    ui->Live2->setPixmap(live);
    ui->Live2->setScaledContents(true);
    ui->Live3->setPixmap(live);
    ui->Live3->setScaledContents(true);
    ui->Live4->setPixmap(live);
    ui->Live4->setScaledContents(true);
    //COMPANIES
    ui->Prod1->setPixmap(Prod);
    ui->Prod1->setScaledContents(true);
    ui->Prod2->setPixmap(Prod);
    ui->Prod2->setScaledContents(true);
    ui->Prod3->setPixmap(Prod);
    ui->Prod3->setScaledContents(true);
    ui->Prod4->setPixmap(Prod);
    ui->Prod4->setScaledContents(true);

    ui->disProd1->setPixmap(Stats);
    ui->disProd1->setScaledContents(true);
    ui->disProd2->setPixmap(Stats);
    ui->disProd2->setScaledContents(true);
    ui->disProd3->setPixmap(Stats);
    ui->disProd3->setScaledContents(true);
    ui->disProd4->setPixmap(Stats);
    ui->disProd4->setScaledContents(true);

    ui->Manprod1->setPixmap(user_display);
    ui->Manprod1->setScaledContents(true);
    ui->Manprod2->setPixmap(user_display);
    ui->Manprod2->setScaledContents(true);
    ui->Manprod3->setPixmap(user_display);
    ui->Manprod3->setScaledContents(true);
    ui->Manprod4->setPixmap(user_display);
    ui->Manprod4->setScaledContents(true);

    ui->Discounts1->setPixmap(user_display);
    ui->Discounts1->setScaledContents(true);
    ui->Discounts2->setPixmap(user_display);
    ui->Discounts2->setScaledContents(true);
    ui->Discounts3->setPixmap(user_display);
    ui->Discounts3->setScaledContents(true);
    ui->Discounts4->setPixmap(user_display);
    ui->Discounts4->setScaledContents(true);

    //company page:

    ui->email1->setPixmap(Email);
    ui->email1->setScaledContents(true);
    ui->email2->setPixmap(Email);
    ui->email2->setScaledContents(true);
    ui->email3->setPixmap(Email);
    ui->email3->setScaledContents(true);
    ui->email4->setPixmap(Email);
    ui->email4->setScaledContents(true);

    ui->Comp1->setPixmap(Comp);
    ui->Comp1->setScaledContents(true);
    ui->Comp2->setPixmap(Comp);
    ui->Comp2->setScaledContents(true);
    ui->Comp3->setPixmap(Comp);
    ui->Comp3->setScaledContents(true);
    ui->Comp4->setPixmap(Comp);
    ui->Comp4->setScaledContents(true);

    ui->ManC1->setPixmap(user_display);
    ui->ManC1->setScaledContents(true);
    ui->ManC2->setPixmap(user_display);
    ui->ManC2->setScaledContents(true);
    ui->ManC3->setPixmap(user_display);
    ui->ManC3->setScaledContents(true);
    ui->ManC4->setPixmap(user_display);
    ui->ManC4->setScaledContents(true);

    ui->Stats1->setPixmap(Stats);
    ui->Stats1->setScaledContents(true);
    ui->Stats2->setPixmap(Stats);
    ui->Stats2->setScaledContents(true);
    ui->Stats3->setPixmap(Stats);
    ui->Stats3->setScaledContents(true);
    ui->Stats4->setPixmap(Stats);
    ui->Stats4->setScaledContents(true);



    ui->homeImage->setPixmap(logo);
    ui->homeImage->setScaledContents(true);
    //ui->waveDecoration->setPixmap(waves);
    //ui->waveDecoration->setScaledContents(true);

    ///-----end

    //frame
    ui->BackFrame_16->lower();
    ui->BackFrame_16->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_17->lower();
    ui->BackFrame_18->lower();
    ui->BackFrame_19->lower();
    ui->BackFrame_20->lower();
    ui->BackFrame_21->lower();
    ui->BackFrame_22->lower();
    ui->BackFrame_23->lower();
    ui->BackFrame_24->lower();
    ui->BackFrame_25->lower();
    ui->BackFrame_26->lower();
    ui->BackFrame_27->lower();
    ui->BackFrame_28->lower();
    ui->BackFrame_29->lower();
    ui->BackFrame_30->lower();
    ui->BackFrame_17->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_3->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_4->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_5->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_6->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_18->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_19->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_20->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_21->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_22->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_23->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_24->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_25->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_26->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_27->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_28->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_29->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_30->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ///=============web / pages titles START================

    ui->WebBrowsing->setTabText(1, "👨‍💻 Users");
    ui->WebBrowsing->setTabText(2, "🛳️ Manage Dock");
    ui->WebBrowsing->setTabText(3, "⛵ Boats Admission");
    ui->WebBrowsing->setTabText(4, "🐟  Product Restock");
    ui->WebBrowsing->setTabText(5, "🏢  Companies");

    ///=============web / pages titles END================

    //testing for the New/final version:

    //page USER
    connect(ui->add_user  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(ui->Manage  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(ui->Display  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(2);
    });
    connect(ui->add_user_2  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(ui->Manage_2  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(ui->Display_2  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(2);
    });
    connect(ui->add_user_3  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(ui->Manage_3 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(ui->Display_3  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(2);
    });

    connect(ui->add_user_3  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(ui->Manage_3 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(ui->Display_3  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(2);
    });

    //page DOCK
    connect(ui->add_user_18  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(0);
    });
    connect(ui->Manage_18 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(1);
    });
    connect(ui->Display_18  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(2);
    });
    connect(ui->add_user_17  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(0);
    });
    connect(ui->Manage_17 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(1);
    });
    connect(ui->Display_17  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(2);
    });
    connect(ui->add_user_5  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(0);
    });
    connect(ui->Manage_5 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(1);
    });
    connect(ui->Display_5  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(2);
    });
    connect(ui->add_user_6  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(0);
    });
    connect(ui->Manage_6 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(1);
    });
    connect(ui->Display_6  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(2);
    });
    connect(ui->forgetpwd_4  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(3);
    });
    connect(ui->forgetpwd_2  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(3);
    });
    connect(ui->forgetpwd_5  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(3);
    });
    connect(ui->forgetpwd_6  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(3);
    });

    //page BOAT :,D
    connect(ui->add_user_22  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_3->setCurrentIndex(0);
    });
    connect(ui->Manage_22 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_3->setCurrentIndex(1);
    });
    connect(ui->Display_22  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_3->setCurrentIndex(2);
    });
    connect(ui->add_user_21  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_3->setCurrentIndex(0);
    });
    connect(ui->Manage_21 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_3->setCurrentIndex(1);
    });
    connect(ui->Display_21  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_3->setCurrentIndex(2);
    });
    connect(ui->add_user_19  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_3->setCurrentIndex(0);
    });
    connect(ui->Manage_19 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_3->setCurrentIndex(1);
    });
    connect(ui->Display_19  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_3->setCurrentIndex(2);
    });
    connect(ui->forgetpwd_7  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_3->setCurrentIndex(3);
    });
    connect(ui->forgetpwd_8  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_3->setCurrentIndex(3);
    });
    connect(ui->forgetpwd_9  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_3->setCurrentIndex(3);
    });
    connect(ui->forgetpwd_10  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_3->setCurrentIndex(3);
    });

    //page Prod
    connect(ui->add_user_24  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(0);
    });
    connect(ui->Manage_24 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(1);
    });
    connect(ui->Display_24  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(2);
    });
    connect(ui->add_user_28  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(0);
    });
    connect(ui->Manage_28 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(1);
    });
    connect(ui->Display_28  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(2);
    });
    connect(ui->add_user_26  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(0);
    });
    connect(ui->Manage_26 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(1);
    });
    connect(ui->Display_26  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(2);
    });
    connect(ui->add_user_27  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(0);
    });
    connect(ui->Manage_27 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(1);
    });
    connect(ui->Display_27  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(2);
    });
    connect(ui->forgetpwd_12  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(3);
    });
    connect(ui->forgetpwd_14  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(3);
    });
    connect(ui->forgetpwd_15  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(3);
    });
    connect(ui->forgetpwd_16  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(3);
    });
    //cOMPANIES

    connect(ui->add_user_29  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(0);
    });
    connect(ui->Manage_29 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(1);
    });
    connect(ui->Display_29  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(2);
    });
    connect(ui->add_user_30 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(0);
    });
    connect(ui->Manage_30 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(1);
    });
    connect(ui->Display_30  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(2);
    });
    connect(ui->add_user_31 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(0);
    });
    connect(ui->Manage_31 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(1);
    });
    connect(ui->Display_31  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(2);
    });
    connect(ui->add_user_32 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(0);
    });
    connect(ui->Manage_32 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(1);
    });
    connect(ui->Display_32  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(2);
    });
    connect(ui->forgetpwd_20  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(3);
    });
    connect(ui->forgetpwd_17  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(3);
    });
    connect(ui->forgetpwd_18  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(3);
    });
    connect(ui->forgetpwd_19  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(3);
    });
    connect(ui->CheckInsightsComp  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(3);
    });
    connect(ui->GoBackCompanies  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(2);
    });
    //++++

    /// Exit page
    connect(ui->Exit, &QPushButton::clicked, qApp, &QApplication::quit);

    /// Log in page
    connect(ui->Goback, &QPushButton::clicked, this, [=]() {
        MainWindow *w = new MainWindow();
        w->show();
        this->close();   // or hide()
    });
}

//Add docking
void appwindow::on_CreateDocking_clicked()
{
    // Get values from UI widgets
    QString location = ui->location->text();
    QString length = ui->length->text();
    QString height = ui->height->text();
    QString status = ui->status->currentText();  // Assuming it's a QComboBox
    QString capacity = ui->capacity->text();
    QString startDate = ui->startDate->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString endDate = ui->endDate->dateTime().toString("yyyy-MM-dd hh:mm:ss");

    // Validate inputs
    if (location.isEmpty() || length.isEmpty() || height.isEmpty() ||
        capacity.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill in all required fields!");
        return;
    }

    // Call the create function
    if (dockingManager.createDocking(location, length, height, status, capacity, startDate, endDate)) {
        QMessageBox::information(this, "Success", "Docking created successfully!");
        // Clear the form
        ui->location->clear();
        ui->length->clear();
        ui->height->clear();
        ui->capacity->clear();
    } else {
        QMessageBox::critical(this, "Error", "Failed to create docking. Please check the database connection.");
    }
}

//add user
void appwindow::on_CreateUser_clicked()
{
    // Get values from UI widgets
    QString email = ui->email->text();
    QString firstName = ui->Fname->text();
    QString lastName = ui->Lname->text();
    QString password = ui->password->text();
    QString role = ui->role->currentText();
    QString gender = ui->gender->currentText().left(1).toUpper(); // M/F

    bool ok;
    double salary = ui->salary->text().toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "Salary must be a number!");
        return;
    }

    QString shiftStart = ui->startShift->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString shiftEnd = ui->endShift->dateTime().toString("yyyy-MM-dd HH:mm:ss");

    // Validate required fields
    if (email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill in all required fields!");
        return;
    }

    // Call the create function ONCE
    if (userManager.createUser(email, firstName, lastName, password, role, gender, salary, shiftStart, shiftEnd)) {
        QMessageBox::information(this, "Success", "User created successfully!");

        // Clear the form
        ui->email->clear();
        ui->Fname->clear();
        ui->Lname->clear();
        ui->password->clear();
        ui->role->setCurrentIndex(0);
        ui->gender->setCurrentIndex(0);
        ui->salary->clear();
        ui->startShift->setDateTime(QDateTime::currentDateTime());
        ui->endShift->setDateTime(QDateTime::currentDateTime());
    } else {
        QMessageBox::critical(this, "Error", "Failed to create user. Please check the database connection.");
    }
}

// Add product
void appwindow::on_checkProductButton_2_clicked()
{
    // Get values from UI widgets (object names based on appwindow.ui)
    QString id = ui->firstNameEdit_3->text();               // Product Code
    QString type = ui->firstNameEdit_4->text();             // Type of Fish
    QString status = ui->role_option_4->currentText();      // Status combo
    QString quantity = ui->firstNameEdit_5->text();          // Quantity
    QString price = ui->firstNameEdit_6->text();             // Price
    QString location = ui->locationEdit->text();             // location

    QString fishCaughtTime = ui->dateTimeEdit_6->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString dateOfPurchase = ui->dateTimeEdit_5->dateTime().toString("yyyy-MM-dd HH:mm:ss");




    // Validate required fields
    if (id.isEmpty() || type.isEmpty() || quantity.isEmpty() || price.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill in all required fields!");
        return;
    }

    // Optionally validate numeric fields
    bool ok;
    int qty = quantity.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "Quantity must be a number!");
        return;
    }
    double pr = price.toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "Price must be a number!");
        return;
    }

    // Call the create function
    if (productManager.createProduct(id, type, status, quantity, price,
                                     fishCaughtTime, dateOfPurchase, location)) {
        QMessageBox::information(this, "Success", "Product added successfully!");

        // Clear the form
        ui->firstNameEdit_3->clear();
        ui->firstNameEdit_4->clear();
        ui->role_option_4->setCurrentIndex(0);
        ui->firstNameEdit_5->clear();
        ui->firstNameEdit_6->clear();
        ui->dateTimeEdit_5->setDateTime(QDateTime::currentDateTime());
        ui->dateTimeEdit_6->setDateTime(QDateTime::currentDateTime());
        // If location field exists, clear it too
        // ui->locationEdit->clear();
    } else {
        QMessageBox::critical(this, "Error", "Failed to add product. Please check the database connection.");
    }
}

appwindow::~appwindow()
{
    if (m_database.isOpen()) {
        m_database.close();
    }
    delete ui;
}





=======
// ===============================================
// DATABASE CONNECTION METHODS
// ===============================================

bool appwindow::connectToDatabase()
{
    m_database = QSqlDatabase::addDatabase("QOCI");  // Oracle database driver
    
    // Database connection parameters
    // Update these based on your SQL Developer configuration
    m_database.setHostName("localhost");  // or your Oracle host
    m_database.setDatabaseName("hwata");  // or your service name/SID
    m_database.setUserName("system");     // Update with your username
    m_database.setPassword("password");   // Update with your password
    
    if (!m_database.open()) {
        QMessageBox::critical(this, "Database Error", 
            "Failed to connect to database:\n" + m_database.lastError().text());
        return false;
    }
    
    return true;
}

void appwindow::createProductTable()
{
    QSqlQuery query(m_database);
    
    // Create products table if it doesn't exist
    QString createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS products (
            product_id NUMBER PRIMARY KEY,
            product_code VARCHAR2(100) NOT NULL,
            fish_type VARCHAR2(100) NOT NULL,
            catch_date TIMESTAMP,
            catch_time TIMESTAMP,
            quantity NUMBER NOT NULL,
            status NUMBER NOT NULL,
            price NUMBER(10,2) NOT NULL,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        )
    )";
    
    if (!query.exec(createTableQuery)) {
        qDebug() << "Failed to create table:" << query.lastError().text();
        // Table might already exist, which is fine
    }
    
    // Create sequence for auto-incrementing product_id
    QString createSequenceQuery = "CREATE SEQUENCE product_seq START WITH 1 INCREMENT BY 1";
    query.exec(createSequenceQuery);  // Ignore error if sequence already exists
}

// ===============================================
// PRODUCT CRUD IMPLEMENTATION
// ===============================================

// Load products from database
void appwindow::loadProductsFromDB()
{
    m_products.clear();
    
    QSqlQuery query(m_database);
    query.prepare("SELECT product_id, product_code, fish_type, catch_date, catch_time, "
                  "quantity, status, price, created_at FROM products ORDER BY product_id");
    
    if (!query.exec()) {
        QMessageBox::warning(this, "Database Error", 
            "Failed to load products:\n" + query.lastError().text());
        return;
    }
    
    while (query.next()) {
        Product product(
            query.value(0).toInt(),                           // productId
            query.value(1).toString(),                        // productCode
            query.value(2).toString(),                        // fishType
            query.value(3).toDateTime(),                      // catchDate
            query.value(4).toDateTime(),                      // catchTime
            query.value(5).toInt(),                           // quantity
            static_cast<Product::ProductStatus>(query.value(6).toInt()), // status
            query.value(7).toDouble(),                        // price
            query.value(8).toDateTime()                       // createdAt
        );
        m_products.append(product);
    }
}

// Display products in table
void appwindow::displayProducts()
{
    // Clear existing rows
    m_productModel->removeRows(0, m_productModel->rowCount());
    
    // Populate table with products
    for (const Product &p : m_products) {
        QList<QStandardItem*> row;
        
        row.append(new QStandardItem(QString::number(p.getProductId())));
        row.append(new QStandardItem(p.getProductCode()));
        row.append(new QStandardItem(p.getFishType()));
        row.append(new QStandardItem(p.getCatchDate().toString("yyyy-MM-dd")));
        row.append(new QStandardItem(QString::number(p.getQuantity())));
        row.append(new QStandardItem(Product::statusToString(p.getStatus())));
        row.append(new QStandardItem(QString::number(p.getPrice(), 'f', 2)));
        row.append(new QStandardItem(p.getCreatedAt().toString("yyyy-MM-dd HH:mm")));
        
        m_productModel->appendRow(row);
    }
    
    ui->tableView_5->resizeColumnsToContents();
}

// Clear product form inputs
void appwindow::clearProductForm()
{
    ui->firstNameEdit_5->clear();  // Product Code
    ui->firstNameEdit_3->clear();  // Fish Type
    ui->dateTimeEdit_5->setDateTime(QDateTime::currentDateTime()); // Catch Date
    ui->dateTimeEdit_6->setDateTime(QDateTime::currentDateTime()); // Catch Time
    ui->firstNameEdit_4->clear();  // Quantity
    ui->role_option_4->setCurrentIndex(0); // Status
    ui->firstNameEdit_6->clear();  // Price
}

// Get next product ID
int appwindow::getNextProductId()
{
    int maxId = 0;
    for (const Product &p : m_products) {
        if (p.getProductId() > maxId) {
            maxId = p.getProductId();
        }
    }
    return maxId + 1;
}

// Add Product button handler
void appwindow::on_checkProductButton_2_clicked()
{
    // Get values from form
    QString productCode = ui->firstNameEdit_5->text().trimmed();  // Product Code
    QString fishType = ui->firstNameEdit_3->text().trimmed();      // Fish Type
    QDateTime catchDate = ui->dateTimeEdit_5->dateTime();
    QDateTime catchTime = ui->dateTimeEdit_6->dateTime();
    QString quantityStr = ui->firstNameEdit_4->text().trimmed();
    QString statusStr = ui->role_option_4->currentText();
    QString priceStr = ui->firstNameEdit_6->text().trimmed();
    
    // Validation
    if (productCode.isEmpty() || fishType.isEmpty() || quantityStr.isEmpty() || priceStr.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Please fill in all required fields.");
        return;
    }
    
    bool ok1, ok2;
    int quantity = quantityStr.toInt(&ok1);
    double price = priceStr.toDouble(&ok2);
    
    if (!ok1 || quantity <= 0) {
        QMessageBox::warning(this, "Validation Error", "Please enter a valid quantity (positive number).");
        return;
    }
    
    if (!ok2 || price < 0) {
        QMessageBox::warning(this, "Validation Error", "Please enter a valid price.");
        return;
    }
    
    // Convert status string to enum
    Product::ProductStatus status = Product::stringToStatus(statusStr);
    
    // Insert into database
    QSqlQuery query(m_database);
    query.prepare("INSERT INTO products (product_id, product_code, fish_type, catch_date, "
                  "catch_time, quantity, status, price, created_at) "
                  "VALUES (product_seq.NEXTVAL, :code, :fish_type, :catch_date, "
                  ":catch_time, :quantity, :status, :price, CURRENT_TIMESTAMP)");
    
    query.bindValue(":code", productCode);
    query.bindValue(":fish_type", fishType);
    query.bindValue(":catch_date", catchDate);
    query.bindValue(":catch_time", catchTime);
    query.bindValue(":quantity", quantity);
    query.bindValue(":status", static_cast<int>(status));
    query.bindValue(":price", price);
    
    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", 
            "Failed to add product:\n" + query.lastError().text());
        return;
    }
    
    QMessageBox::information(this, "Success", "Product added successfully!");
    clearProductForm();
}

// Check/Display Products button handler
void appwindow::on_checkProductButton_clicked()
{
    loadProductsFromDB();
    displayProducts();
    
    // Switch to display page (page 2 of the stacked widget)
    ui->stackedWidget_4->setCurrentIndex(1);
}

// Update Product button handler
void appwindow::on_pushButton_24_clicked()
{
    // Get selected row
    QModelIndexList selection = ui->tableView_5->selectionModel()->selectedRows();
    
    if (selection.isEmpty()) {
        QMessageBox::warning(this, "Selection Error", "Please select a product to update.");
        return;
    }
    
    int currentRow = selection.first().row();
    
    // Get product ID from table
    int productId = m_productModel->item(currentRow, 0)->text().toInt();
    
    // Get updated values from table (allowing inline editing)
    QString newCode = m_productModel->item(currentRow, 1)->text();
    QString newFishType = m_productModel->item(currentRow, 2)->text();
    int newQuantity = m_productModel->item(currentRow, 4)->text().toInt();
    double newPrice = m_productModel->item(currentRow, 6)->text().toDouble();
    
    // Update in database
    QSqlQuery query(m_database);
    query.prepare("UPDATE products SET product_code = :code, fish_type = :fish_type, "
                  "quantity = :quantity, price = :price WHERE product_id = :id");
    
    query.bindValue(":code", newCode);
    query.bindValue(":fish_type", newFishType);
    query.bindValue(":quantity", newQuantity);
    query.bindValue(":price", newPrice);
    query.bindValue(":id", productId);
    
    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", 
            "Failed to update product:\n" + query.lastError().text());
        return;
    }
    
    QMessageBox::information(this, "Success", "Product updated successfully!");
    loadProductsFromDB();
    displayProducts();
}

// Delete Product button handler (if pushButton_25 exists)
void appwindow::on_pushButton_25_clicked()
{
    // Get selected row
    QModelIndexList selection = ui->tableView_5->selectionModel()->selectedRows();
    
    if (selection.isEmpty()) {
        QMessageBox::warning(this, "Selection Error", "Please select a product to delete.");
        return;
    }
    
    // Confirm deletion
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, 
        "Confirm Delete", 
        "Are you sure you want to delete this product?",
        QMessageBox::Yes | QMessageBox::No
    );
    
    if (reply == QMessageBox::No) {
        return;
    }
    
    int currentRow = selection.first().row();
    
    // Get product ID from table
    int productId = m_productModel->item(currentRow, 0)->text().toInt();
    
    // Delete from database
    QSqlQuery query(m_database);
    query.prepare("DELETE FROM products WHERE product_id = :id");
    query.bindValue(":id", productId);
    
    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", 
            "Failed to delete product:\n" + query.lastError().text());
        return;
    }
    
    QMessageBox::information(this, "Success", "Product deleted successfully!");
    loadProductsFromDB();
    displayProducts();
}
