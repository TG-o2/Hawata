#include "appwindow.h"
#include "ui_appwindow.h"
#include "mainwindow.h"

#include <QPixmap>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDate>
#include <QDateTime>
#include <QTime>


appwindow::appwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::appwindow)
{
    ui->setupUi(this);
    loadDockingTable();

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
    QPixmap pic_2("logoQT.png");
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
    ui->Dock2->setPixmap(Dock);
    ui->Dock2->setScaledContents(true);

    ui->deluser_18->setPixmap(user_delete);
    ui->deluser_18->setScaledContents(true);

    ui->dispuser_18->setPixmap(Stats);
    ui->dispuser_18->setScaledContents(true);

    ui->Dock2->setPixmap(Dock);
    ui->Dock2->setScaledContents(true);

    ui->deluser_18->setPixmap(user_delete);
    ui->deluser_18->setScaledContents(true);

    ui->dispuser_18->setPixmap(Stats);
    ui->dispuser_18->setScaledContents(true);

    ui->Dock3->setPixmap(Dock);
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
        loadDockingTable();
    });
    connect(ui->Display_18  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(2);
    });
    connect(ui->add_user_17  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(0);
    });
    connect(ui->Manage_17 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(1);
        loadDockingTable();
    });
    connect(ui->Display_17  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(2);
        loadDockingTable();
    });
    connect(ui->add_user_5  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(0);
    });
    connect(ui->Manage_5 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(1);
        loadDockingTable();
    });
    connect(ui->Display_5  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(2);
        loadDockingTable();
    });
    connect(ui->add_user_6  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(0);
    });
    connect(ui->Manage_6 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(1);
        loadDockingTable();
    });
    connect(ui->Display_6  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(2);
        loadDockingTable();
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

    //docking connects

    // Wire double-click (add once, anywhere in the constructor)
    connect(ui->tabdocking, &QTableWidget::cellDoubleClicked,
            this, &appwindow::on_tabdocking_cellDoubleClicked);
    connect(ui->tabdocking, &QTableWidget::cellClicked,
            this, &appwindow::on_tabdocking_cellClicked);
}

//add docking
void appwindow::on_CreateDocking_clicked()
{
    // Get values from UI widgets
    QString location = ui->location->text().trimmed();
    QString length = ui->length->text().trimmed();
    QString height = ui->height->text().trimmed();
    QString status = ui->status->currentText();
    QString capacity = ui->capacity->text().trimmed();
    QDateTime startDate = ui->startDate->dateTime();
    QDateTime endDate = ui->endDate->dateTime();
    
    // ===== VALIDATION CONTROLS =====
    
    // 1. Check all fields are not empty
    if (location.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Location is required. Please enter a location.");
        return;
    }
    
    // Check Location contains only letters and spaces (no numbers)
    for (QChar c : location) {
        if (c.isDigit()) {
            QMessageBox::warning(this, "Validation Error", "Location must contain only letters. Numbers are not allowed.");
            return;
        }
    }
    
    if (length.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Length is required. Please enter a length value.");
        return;
    }
    
    if (height.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Height is required. Please enter a height value.");
        return;
    }
    
    if (capacity.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Capacity is required. Please enter a capacity value.");
        return;
    }
    
    if (status.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Status is required. Please select a status.");
        return;
    }
    
    // 2. Validate numeric fields (Length, Height, Capacity)
    bool lengthOk, heightOk, capacityOk;
    double lengthVal = length.toDouble(&lengthOk);
    double heightVal = height.toDouble(&heightOk);
    double capacityVal = capacity.toDouble(&capacityOk);
    
    if (!lengthOk || lengthVal <= 0) {
        QMessageBox::warning(this, "Validation Error", "Length must be a positive number.");
        return;
    }
    
    if (!heightOk || heightVal <= 0) {
        QMessageBox::warning(this, "Validation Error", "Height must be a positive number.");
        return;
    }
    
    if (!capacityOk || capacityVal <= 0) {
        QMessageBox::warning(this, "Validation Error", "Capacity must be a positive number.");
        return;
    }
    
    // 3. Validate dates are in the future (tomorrow or later)
    QDateTime tomorrow = QDateTime(QDate::currentDate().addDays(1), QTime(0, 0));
    
    if (startDate < tomorrow) {
        QMessageBox::warning(this, "Validation Error", 
                           QString("Start Date must be in the future (tomorrow or later).\nCurrent date: %1\nMinimum date: %2")
                           .arg(QDate::currentDate().toString("MM/dd/yy"))
                           .arg(tomorrow.date().toString("MM/dd/yy")));
        return;
    }
    
    if (endDate < tomorrow) {
        QMessageBox::warning(this, "Validation Error", 
                           QString("End Date must be in the future (tomorrow or later).\nCurrent date: %1\nMinimum date: %2")
                           .arg(QDate::currentDate().toString("MM/dd/yy"))
                           .arg(tomorrow.date().toString("MM/dd/yy")));
        return;
    }
    
    // 4. Validate End Date >= Start Date
    if (endDate < startDate) {
        QMessageBox::warning(this, "Validation Error", "End Date must be on or after the Start Date.");
        return;
    }
    
    // ===== ALL VALIDATIONS PASSED =====
    
    QString startDateStr = startDate.toString("MM/dd/yy");
    QString endDateStr = endDate.toString("MM/dd/yy");
    
    // Call the create function
    if (dockingManager.createDocking(location, length, height, status, capacity, startDateStr, endDateStr)) {
        QMessageBox::information(this, "Success", "Docking created successfully!");
        // Clear the form
        ui->location->clear();
        ui->length->clear();
        ui->height->clear();
        ui->capacity->clear();
        ui->startDate->setDateTime(QDateTime::currentDateTime());
        ui->endDate->setDateTime(QDateTime::currentDateTime());
        // Reset to first index of status combo
        ui->status->setCurrentIndex(0);
    } else {
        QMessageBox::critical(this, "Error", "Failed to create docking. Please check the database connection.");
    }
}

void appwindow::loadDockingTable()
{
    QList<DockingRecord> records = dockingManager.getAllDockings();
    qDebug() << "Records fetched:" << records.size();  // verify in output

    QTableWidget *table = ui->tabdocking;
    table->setRowCount(0);
    table->setColumnCount(8);
    // ✅ Display all columns including Height and Capacity
    table->setHorizontalHeaderLabels(
        {"ID", "Status", "Date Start", "Date End", "Location", "Length", "Height", "Capacity"});
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for (const DockingRecord &r : records) {
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::number(r.id)));
        table->setItem(row, 1, new QTableWidgetItem(r.status));
        table->setItem(row, 2, new QTableWidgetItem(r.startDate));
        table->setItem(row, 3, new QTableWidgetItem(r.endDate));
        table->setItem(row, 4, new QTableWidgetItem(r.location));
        table->setItem(row, 5, new QTableWidgetItem(r.length));
        table->setItem(row, 6, new QTableWidgetItem(r.height));
        table->setItem(row, 7, new QTableWidgetItem(r.capacity));
    }

    // Stretch all columns to fill available space evenly
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Update the count label at the bottom if you have one
    // ui->countLabel->setText(QString("Showing %1 Docks").arg(records.size()));
}


void appwindow::on_tabdocking_cellClicked(int row, int /*column*/)
{
    if (row < 0) return;
    QString id = ui->tabdocking->item(row, 0)->text();
    ui->selected_id->setText(id);           // ✅ shows ID in your line edit
    selectedDockingId = id.toInt();
}

// Double click → fill form and go to edit page
void appwindow::on_tabdocking_cellDoubleClicked(int row, int /*column*/)
{
    QTableWidget *table = ui->tabdocking;
    if (row < 0) return;

    selectedDockingId = table->item(row, 0)->text().toInt();
    ui->selected_id->setText(QString::number(selectedDockingId));

    // Fill the form fields — column order: ID, Status, DateStart, DateEnd, Location, Length, Height, Capacity
    int idx = ui->status->findText(table->item(row, 1)->text());
    if (idx >= 0) ui->status->setCurrentIndex(idx);

    // Parse dates - try multiple formats since database may store in different format
    QString startDateStr = table->item(row, 2)->text();
    QString endDateStr = table->item(row, 3)->text();
    
    QDateTime startDt = QDateTime::fromString(startDateStr, "yyyy-MM-dd hh:mm:ss");
    if (!startDt.isValid()) {
        startDt = QDateTime::fromString(startDateStr, "MM/dd/yy");
        // Fix 2-digit year: if year < 1950, it's 20xx, otherwise 19xx
        if (startDt.isValid() && startDt.date().year() < 1950) {
            startDt = startDt.addYears(100);
        }
    }
    if (!startDt.isValid()) {
        startDt = QDateTime::fromString(startDateStr, "dd/MM/yy");
        // Fix 2-digit year: if year < 1950, it's 20xx, otherwise 19xx
        if (startDt.isValid() && startDt.date().year() < 1950) {
            startDt = startDt.addYears(100);
        }
    }
    if (startDt.isValid()) {
        ui->startDate->setDateTime(startDt);
    }
    
    QDateTime endDt = QDateTime::fromString(endDateStr, "yyyy-MM-dd hh:mm:ss");
    if (!endDt.isValid()) {
        endDt = QDateTime::fromString(endDateStr, "MM/dd/yy");
        // Fix 2-digit year: if year < 1950, it's 20xx, otherwise 19xx
        if (endDt.isValid() && endDt.date().year() < 1950) {
            endDt = endDt.addYears(100);
        }
    }
    if (!endDt.isValid()) {
        endDt = QDateTime::fromString(endDateStr, "dd/MM/yy");
        // Fix 2-digit year: if year < 1950, it's 20xx, otherwise 19xx
        if (endDt.isValid() && endDt.date().year() < 1950) {
            endDt = endDt.addYears(100);
        }
    }
    if (endDt.isValid()) {
        ui->endDate->setDateTime(endDt);
    }

    ui->location->setText(table->item(row, 4)->text());
    ui->length->setText(table->item(row, 5)->text());
    ui->height->setText(table->item(row, 6)->text());
    ui->capacity->setText(table->item(row, 7)->text());

    // Navigate to the create/edit page
    ui->stackedWidget_2->setCurrentIndex(0);
}


// ─────────────────────────────────────────────
//  Edit / Update button
// ─────────────────────────────────────────────
void appwindow::on_edit_Docking_clicked()
{
    if (selectedDockingId == -1) {
        QMessageBox::warning(this, "No Selection", "Please double-click a row in the table first.");
        return;
    }

    QString location  = ui->location->text().trimmed();
    QString length    = ui->length->text().trimmed();
    QString height    = ui->height->text().trimmed();
    QString status    = ui->status->currentText();
    QString capacity  = ui->capacity->text().trimmed();
    QDateTime startDate = ui->startDate->dateTime();
    QDateTime endDate = ui->endDate->dateTime();

    // ===== VALIDATION CONTROLS =====
    
    // 1. Check all fields are not empty
    if (location.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Location is required. Please enter a location.");
        return;
    }
    
    // Check Location contains only letters and spaces (no numbers)
    for (QChar c : location) {
        if (c.isDigit()) {
            QMessageBox::warning(this, "Validation Error", "Location must contain only letters. Numbers are not allowed.");
            return;
        }
    }
    
    if (length.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Length is required. Please enter a length value.");
        return;
    }
    
    if (height.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Height is required. Please enter a height value.");
        return;
    }
    
    if (capacity.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Capacity is required. Please enter a capacity value.");
        return;
    }
    
    if (status.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Status is required. Please select a status.");
        return;
    }
    
    // 2. Validate numeric fields (Length, Height, Capacity)
    bool lengthOk, heightOk, capacityOk;
    double lengthVal = length.toDouble(&lengthOk);
    double heightVal = height.toDouble(&heightOk);
    double capacityVal = capacity.toDouble(&capacityOk);
    
    if (!lengthOk || lengthVal <= 0) {
        QMessageBox::warning(this, "Validation Error", "Length must be a positive number.");
        return;
    }
    
    if (!heightOk || heightVal <= 0) {
        QMessageBox::warning(this, "Validation Error", "Height must be a positive number.");
        return;
    }
    
    if (!capacityOk || capacityVal <= 0) {
        QMessageBox::warning(this, "Validation Error", "Capacity must be a positive number.");
        return;
    }
    
    // 3. Validate dates are in the future (tomorrow or later)
    QDateTime tomorrow = QDateTime(QDate::currentDate().addDays(1), QTime(0, 0));
    
    if (startDate < tomorrow) {
        QMessageBox::warning(this, "Validation Error", 
                           QString("Start Date must be in the future (tomorrow or later).\nCurrent date: %1\nMinimum date: %2")
                           .arg(QDate::currentDate().toString("MM/dd/yy"))
                           .arg(tomorrow.date().toString("MM/dd/yy")));
        return;
    }
    
    if (endDate < tomorrow) {
        QMessageBox::warning(this, "Validation Error", 
                           QString("End Date must be in the future (tomorrow or later).\nCurrent date: %1\nMinimum date: %2")
                           .arg(QDate::currentDate().toString("MM/dd/yy"))
                           .arg(tomorrow.date().toString("MM/dd/yy")));
        return;
    }
    
    // 4. Validate End Date >= Start Date
    if (endDate < startDate) {
        QMessageBox::warning(this, "Validation Error", "End Date must be on or after the Start Date.");
        return;
    }
    
    // ===== ALL VALIDATIONS PASSED =====
    
    QString startDateStr = startDate.toString("MM/dd/yy");
    QString endDateStr = endDate.toString("MM/dd/yy");

    if (dockingManager.updateDocking(selectedDockingId, location, length,
                                     height, status, capacity, startDateStr, endDateStr)) {
        QMessageBox::information(this, "Success", "Docking updated successfully!");
        selectedDockingId = -1;          // reset selection
        loadDockingTable();              // refresh table
        ui->stackedWidget_2->setCurrentIndex(1);  // go back to display page
    } else {
        QMessageBox::critical(this, "Error", "Failed to update docking.");
    }
}

// ─────────────────────────────────────────────
//  Delete button
// ─────────────────────────────────────────────
void appwindow::on_delete_docking_clicked()
{
    QTableWidget *table = ui->tabdocking;
    int currentRow = table->currentRow();

    if (currentRow < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a row to delete.");
        return;
    }

    int id       = table->item(currentRow, 0)->text().toInt();
    QString loc  = table->item(currentRow, 1)->text();

    QMessageBox::StandardButton reply =
        QMessageBox::question(this, "Confirm Delete",
                              QString("Are you sure you want to delete docking at \"%1\" (ID: %2)?")
                                  .arg(loc).arg(id),
                              QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (dockingManager.deleteDocking(id)) {
            QMessageBox::information(this, "Deleted", "Docking deleted successfully.");
            loadDockingTable();   // refresh the table
        } else {
            QMessageBox::critical(this, "Error", "Failed to delete docking.");
        }
    }
}

// ─────────────────────────────────────────────
//  Clear button
// ─────────────────────────────────────────────
void appwindow::on_clear_docking_clicked()
{
    ui->location->clear();
    ui->length->clear();
    ui->height->clear();
    ui->capacity->clear();
    ui->startDate->setDateTime(QDateTime::currentDateTime());
    ui->endDate->setDateTime(QDateTime::currentDateTime());
    ui->status->setCurrentIndex(0);
    ui->selected_id->clear();
    selectedDockingId = -1;
}


appwindow::~appwindow()
{
    delete ui;
}
