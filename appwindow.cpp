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
#include <algorithm>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QPageLayout>
#include <QSqlQuery>
#include <QSqlDatabase>


appwindow::appwindow(QWidget *parent, int currentUserId, const QString &currentUserRole)
    : QDialog(parent)
    , ui(new Ui::appwindow)
    , connectedUserId(currentUserId)
    , connectedUserRole(currentUserRole)
{
    ui->setupUi(this);
    loadDockingTable();
    loadUsersTable();
    loadProductTable();  // Load product table on startup

    //load boat table
    displayBoats();

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

    // ============================ USER MODULE ============================
    // User UI assets + user management visuals
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
        setBoatMode(BoatMode::Add);
        ui->boatPage->setCurrentIndex(0);
    });
    connect(ui->add_user_21  , &QPushButton::clicked, this, [=]() {
        setBoatMode(BoatMode::Add);
        ui->boatPage->setCurrentIndex(0);
    });
    connect(ui->add_user_20  , &QPushButton::clicked, this, [=]() {
        setBoatMode(BoatMode::Add);
        ui->boatPage->setCurrentIndex(0);
    });
    connect(ui->add_user_19  , &QPushButton::clicked, this, [=]() {
        setBoatMode(BoatMode::Add);
        ui->boatPage->setCurrentIndex(0);
    });
    connect(ui->Manage_22 , &QPushButton::clicked, this, [=]() {
        ui->boatPage->setCurrentIndex(1);
    });
    connect(ui->Manage_20 , &QPushButton::clicked, this, [=]() {
        ui->boatPage->setCurrentIndex(1);
    });
    connect(ui->Manage_21 , &QPushButton::clicked, this, [=]() {
        ui->boatPage->setCurrentIndex(1);
    });
    connect(ui->Manage_19 , &QPushButton::clicked, this, [=]() {
        ui->boatPage->setCurrentIndex(1);
    });
    connect(ui->Display_22  , &QPushButton::clicked, this, [=]() {
        ui->boatPage->setCurrentIndex(2);
    });
    connect(ui->Display_20  , &QPushButton::clicked, this, [=]() {
        ui->boatPage->setCurrentIndex(2);
    });
    connect(ui->Display_21  , &QPushButton::clicked, this, [=]() {
        ui->boatPage->setCurrentIndex(2);
    });
    connect(ui->Display_19  , &QPushButton::clicked, this, [=]() {
        ui->boatPage->setCurrentIndex(2);
    });
    connect(ui->forgetpwd_7  , &QPushButton::clicked, this, [=]() {
        ui->boatPage->setCurrentIndex(3);
    });
    connect(ui->forgetpwd_8  , &QPushButton::clicked, this, [=]() {
        ui->boatPage->setCurrentIndex(3);
    });
    connect(ui->forgetpwd_9  , &QPushButton::clicked, this, [=]() {
        ui->boatPage->setCurrentIndex(3);
    });
    connect(ui->forgetpwd_10  , &QPushButton::clicked, this, [=]() {
        ui->boatPage->setCurrentIndex(3);
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
    
    QString startDateStr = startDate.toString("dd/MM/yy");
    QString endDateStr = endDate.toString("dd/MM/yy");
    
    // Call create docking + create manage relation in one transaction
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Error", "Database is not open.");
        return;
    }

    if (!db.transaction()) {
        QMessageBox::critical(this, "Error", "Failed to start database transaction.");
        return;
    }

    int createdDockId = -1;
    if (dockingManager.createDocking(location, length, height, status, capacity, startDateStr, endDateStr, &createdDockId)) {
        if (connectedUserId <= 0 || createdDockId <= 0) {
            db.rollback();
            QMessageBox::critical(this, "Error", "Failed to resolve UserID or DockID for MANAGE relation.");
            return;
        }

        if (!manageManager.ajouter_manage(connectedUserId, createdDockId)) {
            db.rollback();
            QMessageBox::critical(this, "Error", "Docking was created but MANAGE relation failed. Transaction rolled back.");
            return;
        }

        if (!db.commit()) {
            db.rollback();
            QMessageBox::critical(this, "Error", "Failed to commit docking transaction.");
            return;
        }

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
        loadDockingTable();
    } else {
        db.rollback();
        QMessageBox::critical(this, "Error", "Failed to create docking. Please check the database connection.");
    }
}

void appwindow::loadDockingTable()
{
    allDockingRecords = dockingManager.getAllDockings();
    qDebug() << "Records fetched:" << allDockingRecords.size();  // verify in output
    
    // Clear search and reset sort to default
    ui->searchbar_docking->blockSignals(true);
    ui->searchbar_docking->clear();
    ui->searchbar_docking->blockSignals(false);
    
    ui->docking_sort->blockSignals(true);
    ui->docking_sort->setCurrentIndex(0);  // Set to "Date" (default)
    ui->docking_sort->blockSignals(false);
    
    // Populate table with all records
    populateDockingTable(allDockingRecords);
}

void appwindow::populateDockingTable(const QList<DockingRecord> &records)
{
    QTableWidget *table = ui->tabdocking;
    table->setRowCount(0);
    table->setColumnCount(8);
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

    // Update the count label at the bottom with the number of docks
    ui->labelResults_4->setText(QString("Showing %1 Docks").arg(records.size()));
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
    
    QString startDateStr = startDate.toString("dd/MM/yy");
    QString endDateStr = endDate.toString("dd/MM/yy");

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

void appwindow::on_searchbar_docking_textChanged(const QString &text)
{
    QString searchText = text.trimmed().toLower();
    QList<DockingRecord> filteredRecords;

    // Filter records based on search text (search in all attributes)
    for (const DockingRecord &r : allDockingRecords) {
        if (QString::number(r.id).contains(searchText, Qt::CaseInsensitive) ||
            r.status.contains(searchText, Qt::CaseInsensitive) ||
            r.startDate.contains(searchText, Qt::CaseInsensitive) ||
            r.endDate.contains(searchText, Qt::CaseInsensitive) ||
            r.location.contains(searchText, Qt::CaseInsensitive) ||
            r.length.contains(searchText, Qt::CaseInsensitive) ||
            r.height.contains(searchText, Qt::CaseInsensitive) ||
            r.capacity.contains(searchText, Qt::CaseInsensitive)) {
            filteredRecords.append(r);
        }
    }

    // Apply the current sort to the filtered results
    int sortIndex = ui->docking_sort->currentIndex();
    on_docking_sort_currentIndexChanged(sortIndex);
}

void appwindow::on_docking_sort_currentIndexChanged(int index)
{
    // Get the current filtered records (or all if no filter)
    QString searchText = ui->searchbar_docking->text().trimmed().toLower();
    QList<DockingRecord> recordsToSort;

    if (searchText.isEmpty()) {
        recordsToSort = allDockingRecords;
    } else {
        // Apply filter first
        for (const DockingRecord &r : allDockingRecords) {
            if (QString::number(r.id).contains(searchText, Qt::CaseInsensitive) ||
                r.status.contains(searchText, Qt::CaseInsensitive) ||
                r.startDate.contains(searchText, Qt::CaseInsensitive) ||
                r.endDate.contains(searchText, Qt::CaseInsensitive) ||
                r.location.contains(searchText, Qt::CaseInsensitive) ||
                r.length.contains(searchText, Qt::CaseInsensitive) ||
                r.height.contains(searchText, Qt::CaseInsensitive) ||
                r.capacity.contains(searchText, Qt::CaseInsensitive)) {
                recordsToSort.append(r);
            }
        }
    }

    // Sort based on start date
    if (index == 1) {  // Ascending - closest date to furthest (from today)
        QDate today = QDate::currentDate();
        std::sort(recordsToSort.begin(), recordsToSort.end(), [today](const DockingRecord &a, const DockingRecord &b) {
            QDate dateA = QDate::fromString(a.startDate, "yyyy-MM-dd");
            if (!dateA.isValid()) dateA = QDate::fromString(a.startDate, "MM/dd/yy");
            if (!dateA.isValid()) dateA = QDate::fromString(a.startDate, "dd/MM/yy");

            QDate dateB = QDate::fromString(b.startDate, "yyyy-MM-dd");
            if (!dateB.isValid()) dateB = QDate::fromString(b.startDate, "MM/dd/yy");
            if (!dateB.isValid()) dateB = QDate::fromString(b.startDate, "dd/MM/yy");

            qint64 distA = qAbs(today.daysTo(dateA));
            qint64 distB = qAbs(today.daysTo(dateB));
            return distA < distB;
        });
    } else if (index == 2) {  // Descending - furthest date to closest (from today)
        QDate today = QDate::currentDate();
        std::sort(recordsToSort.begin(), recordsToSort.end(), [today](const DockingRecord &a, const DockingRecord &b) {
            QDate dateA = QDate::fromString(a.startDate, "yyyy-MM-dd");
            if (!dateA.isValid()) dateA = QDate::fromString(a.startDate, "MM/dd/yy");
            if (!dateA.isValid()) dateA = QDate::fromString(a.startDate, "dd/MM/yy");

            QDate dateB = QDate::fromString(b.startDate, "yyyy-MM-dd");
            if (!dateB.isValid()) dateB = QDate::fromString(b.startDate, "MM/dd/yy");
            if (!dateB.isValid()) dateB = QDate::fromString(b.startDate, "dd/MM/yy");

            qint64 distA = qAbs(today.daysTo(dateA));
            qint64 distB = qAbs(today.daysTo(dateB));
            return distA > distB;
        });
    }
    // Index 0 = "Date" (default, no sorting needed)

    populateDockingTable(recordsToSort);
}

void appwindow::on_export_docking_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Export Docking Data to PDF"), "",
                                                    tr("PDF Files (*.pdf);;All Files (*)"));

    if (fileName.isEmpty())
        return;

    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive))
        fileName += ".pdf";

    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setPageOrientation(QPageLayout::Landscape); // Landscape for more width
    pdfWriter.setResolution(300);
    pdfWriter.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);

    QPainter painter(&pdfWriter);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor darkBlue(0, 102, 204);
    QColor veryLightBlue(230, 242, 255);
    QColor lightGray(245, 245, 245);
    QColor textColor(30, 30, 30);
    QColor borderColor(180, 180, 180);

    int pageWidth  = pdfWriter.width();
    int pageHeight = pdfWriter.height();

    // Use painter units directly (no extra margin since QPdfWriter margins are set)
    int marginLeft   = 0;
    int marginTop    = 0;
    int contentWidth = pageWidth;

    int yPos = marginTop;

    // ── TITLE BLOCK ──────────────────────────────────────────────────────────
    int titleBlockHeight = 120;
    // Background banner
    painter.fillRect(marginLeft, yPos, contentWidth, titleBlockHeight, darkBlue);

    // Title text
    QFont titleFont("Arial", 32, QFont::Bold);
    painter.setFont(titleFont);
    painter.setPen(Qt::white);
    painter.drawText(marginLeft, yPos, contentWidth, titleBlockHeight,
                     Qt::AlignCenter | Qt::AlignVCenter, "DOCKING DATA REPORT");

    yPos += titleBlockHeight + 30; // gap after banner

    // ── DATE LINE ────────────────────────────────────────────────────────────
    QFont dateFont("Arial", 11);
    painter.setFont(dateFont);
    painter.setPen(QColor(100, 100, 100));
    painter.drawText(marginLeft, yPos,
                     QString("Generated: %1")
                         .arg(QDateTime::currentDateTime()
                                  .toString("yyyy-MM-dd  hh:mm:ss")));
    yPos += 50;

    // ── TABLE ─────────────────────────────────────────────────────────────────
    QTableWidget *table = ui->tabdocking;
    int rowCount    = table->rowCount();
    int columnCount = table->columnCount();

    if (rowCount == 0) {
        painter.setFont(QFont("Arial", 14));
        painter.setPen(textColor);
        painter.drawText(marginLeft, yPos, "No data to export.");
        painter.end();
        QMessageBox::information(this, "No Data", "The table is empty. Nothing to export.");
        return;
    }

    // Distribute column widths evenly across full content width
    int columnWidth = contentWidth / columnCount;
    int headerHeight = 80;

    auto drawHeader = [&]() {
        // Header background
        painter.fillRect(marginLeft, yPos, contentWidth, headerHeight, darkBlue);

        QFont headerFont("Arial", 13, QFont::Bold);
        painter.setFont(headerFont);
        painter.setPen(Qt::white);

        int xPos = marginLeft;
        for (int col = 0; col < columnCount; col++) {
            QString headerText = table->horizontalHeaderItem(col)
            ? table->horizontalHeaderItem(col)->text()
            : "";
            painter.drawText(xPos + 8, yPos, columnWidth - 16, headerHeight,
                             Qt::AlignCenter | Qt::AlignVCenter | Qt::TextWordWrap,
                             headerText);

            // Vertical separator between columns
            if (col < columnCount - 1) {
                painter.setPen(QPen(Qt::white, 2));
                painter.drawLine(xPos + columnWidth, yPos,
                                 xPos + columnWidth, yPos + headerHeight);
                painter.setPen(Qt::white);
            }
            xPos += columnWidth;
        }
    };

    drawHeader();
    yPos += headerHeight;

    // Row sizing — fill available vertical space nicely
    int rowHeight    = 75;
    int footerHeight = 80;
    int rowsPerPage  = (pageHeight - yPos - footerHeight) / rowHeight;

    QFont cellFont("Arial", 11);
    painter.setFont(cellFont);

    for (int row = 0; row < rowCount; row++) {

        // ── New page if needed ──
        if (row > 0 && row % rowsPerPage == 0) {
            pdfWriter.newPage();
            yPos = marginTop;
            drawHeader();
            yPos += headerHeight;
            painter.setFont(cellFont);
        }

        // Alternating row background
        QColor rowBg = (row % 2 == 0) ? Qt::white : veryLightBlue;
        painter.fillRect(marginLeft, yPos, contentWidth, rowHeight, rowBg);

        // Row outer border
        painter.setPen(QPen(borderColor, 1));
        painter.drawRect(marginLeft, yPos, contentWidth, rowHeight);

        // Cell content + column separators
        int xPos = marginLeft;
        for (int col = 0; col < columnCount; col++) {
            QTableWidgetItem *item = table->item(row, col);
            QString cellText = item ? item->text() : "";

            painter.setPen(textColor);
            painter.drawText(xPos + 10, yPos, columnWidth - 20, rowHeight,
                             Qt::AlignCenter | Qt::AlignVCenter | Qt::TextWordWrap,
                             cellText);

            if (col < columnCount - 1) {
                painter.setPen(QPen(borderColor, 1));
                painter.drawLine(xPos + columnWidth, yPos,
                                 xPos + columnWidth, yPos + rowHeight);
            }
            xPos += columnWidth;
        }

        yPos += rowHeight;
    }

    // ── FOOTER ───────────────────────────────────────────────────────────────
    yPos += 30;

    // Thin separator line
    painter.setPen(QPen(darkBlue, 3));
    painter.drawLine(marginLeft, yPos, marginLeft + contentWidth, yPos);
    yPos += 20;

    painter.setFont(QFont("Arial", 11, QFont::Bold));
    painter.setPen(darkBlue);
    painter.drawText(marginLeft, yPos,
                     contentWidth, 50,
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QString("Total Records: %1").arg(rowCount));

    painter.drawText(marginLeft, yPos,
                     contentWidth, 50,
                     Qt::AlignRight | Qt::AlignVCenter,
                     QString("Marina Management System"));

    painter.end();

    QMessageBox::information(this, "Export Successful",
                             QString("PDF exported successfully to:\n%1").arg(fileName));
}



// =====================================================================
// =================== START OF USER MODULE ============================
// =====================================================================


/// Add / Update user  --> not really

void appwindow::on_UPDUser_clicked()
{
    QString email = ui->email->text().trimmed();
    QString firstName = ui->Fname->text().trimmed();
    QString lastName = ui->Lname->text().trimmed();
    QString password = ui->password->text().trimmed();
    QString role = ui->role->currentText();
    QString gender = ui->gender->currentText().left(1).toUpper(); // M/F

    bool ok;
    double salary = ui->salary->text().toDouble(&ok);
    if (!ok || salary <= 0) {
        QMessageBox::warning(this, "Error", "Salary must be a positive number!");
        return;
    }

    QString shiftStart = ui->startShift->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString shiftEnd = ui->endShift->dateTime().toString("yyyy-MM-dd HH:mm:ss");

    bool isEditMode = (selectedUserId != -1);

    if (email.isEmpty() || firstName.isEmpty() || lastName.isEmpty() || (!isEditMode && password.isEmpty())) {
        QMessageBox::warning(this, "Error", "Please fill in all required fields!");
        return;
    }

    if (ui->endShift->dateTime() < ui->startShift->dateTime()) {
        QMessageBox::warning(this, "Error", "Shift end must be on or after shift start.");
        return;
    }

    bool success = false;

    int supervisorId = 0;

    if (!isEditMode && connectedUserRole.compare("ADMIN", Qt::CaseInsensitive) == 0 && connectedUserId > 0) {
        supervisorId = connectedUserId;
    }

    if (isEditMode) {
        QSqlQuery supervisorQuery;
        supervisorQuery.prepare("SELECT SUPERVISORID FROM USERS WHERE USERID = :id");
        supervisorQuery.bindValue(":id", selectedUserId);
        if (supervisorQuery.exec() && supervisorQuery.next()) {
            supervisorId = supervisorQuery.value(0).toInt();
        }
    }

    if (isEditMode) {
        User editedUser(selectedUserId, email, firstName, lastName, password,
                        role, gender, salary, shiftStart, shiftEnd, supervisorId);
        success = editedUser.modifier_user();
    } else {
        User newUser(0, email, firstName, lastName, password,
                     role, gender, salary, shiftStart, shiftEnd, supervisorId);
        success = newUser.ajouter_user();
    }

    if (success) {
        QMessageBox::information(this, "Success", isEditMode ? "User updated successfully!" : "User created successfully!");

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
        ui->UPDUser->setText("Create User 💫");
        selectedUserId = -1;
        loadUsersTable();
        if (isEditMode) {
            ui->stackedWidget->setCurrentIndex(1);
        }
    } else {
        QMessageBox::critical(this, "Error", isEditMode
                                               ? "Failed to update user. Please check the database connection."
                                               : "Failed to create user. Please check the database connection.");
    }
}


// Load users table from database +++

void appwindow::loadUsersTable()
{
    QList<User> records = userManager.afficher_liste();

    QTableWidget *table = ui->usersTable;
    table->setRowCount(0);
    table->setColumnCount(9);
    table->setHorizontalHeaderLabels(
        {"ID", "Email", "First Name", "Last Name", "Role", "Gender", "Salary", "Shift Start", "Shift End"});
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setAlternatingRowColors(true);

    for (const User &r : records) {
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::number(r.getUserId())));
        table->setItem(row, 1, new QTableWidgetItem(r.getEmail()));
        table->setItem(row, 2, new QTableWidgetItem(r.getFirstName()));
        table->setItem(row, 3, new QTableWidgetItem(r.getLastName()));
        table->setItem(row, 4, new QTableWidgetItem(r.getRole()));
        table->setItem(row, 5, new QTableWidgetItem(r.getGender()));
        table->setItem(row, 6, new QTableWidgetItem(QString::number(r.getSalary())));
        table->setItem(row, 7, new QTableWidgetItem(r.getShiftStart()));
        table->setItem(row, 8, new QTableWidgetItem(r.getShiftEnd()));
    }

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->labelResults_3->setText(QString("Showing %1 Users").arg(records.size()));
}



// +++ Table logic for Display & Edit user ++++

void appwindow::fillUserForm(const QModelIndex &index)
{
    if (!index.isValid()) {
        return;
    }

    QAbstractItemModel *model = ui->usersTable->model();
    int row = index.row();

    selectedUserId = model->data(model->index(row, 0)).toInt();

    QString email = model->data(model->index(row, 1)).toString();
    QString firstName = model->data(model->index(row, 2)).toString();
    QString lastName = model->data(model->index(row, 3)).toString();
    QString role = model->data(model->index(row, 4)).toString();
    QString gender = model->data(model->index(row, 5)).toString();
    QString salary = model->data(model->index(row, 6)).toString();
    QString shiftStart = model->data(model->index(row, 7)).toString();
    QString shiftEnd = model->data(model->index(row, 8)).toString();

    ui->email->setText(email);
    ui->Fname->setText(firstName);
    ui->Lname->setText(lastName);
    ui->password->clear();
    ui->salary->setText(salary);

    int roleIdx = ui->role->findText(role);
    if (roleIdx >= 0) {
        ui->role->setCurrentIndex(roleIdx);
    }

    int genderIdx = ui->gender->findText(gender, Qt::MatchContains);
    if (genderIdx >= 0) {
        ui->gender->setCurrentIndex(genderIdx);
    }

    QDateTime startDt = QDateTime::fromString(shiftStart, "yyyy-MM-dd HH:mm:ss");
    if (!startDt.isValid()) {
        startDt = QDateTime::fromString(shiftStart, "MM/dd/yy");
    }
    if (startDt.isValid()) {
        ui->startShift->setDateTime(startDt);
    }

    QDateTime endDt = QDateTime::fromString(shiftEnd, "yyyy-MM-dd HH:mm:ss");
    if (!endDt.isValid()) {
        endDt = QDateTime::fromString(shiftEnd, "MM/dd/yy");
    }
    if (endDt.isValid()) {
        ui->endShift->setDateTime(endDt);
    }

    ui->stackedWidget->setCurrentIndex(0);
    ui->UPDUser->setText("Update User");
}


void appwindow::on_usersTable_cellClicked(int row, int /*column*/)
{
    if (row < 0 || !ui->usersTable->item(row, 0)) {
        return;
    }

    selectedUserId = ui->usersTable->item(row, 0)->text().toInt();
}


void appwindow::on_usersTable_cellDoubleClicked(int row, int column)
{
    if (row < 0) {
        return;
    }

    fillUserForm(ui->usersTable->model()->index(row, column));
}

// +++ Delete user ++++
void appwindow::on_deleteUSERBtn_clicked()
{
    QModelIndexList selected = ui->usersTable->selectionModel()->selectedRows();

    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a user to delete.");
        return;
    }

    int row = selected.first().row();

    int userId = ui->usersTable->model()->data(
                                            ui->usersTable->model()->index(row, 0)
                                            ).toInt();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Delete",
                                  "Are you sure you want to delete this user?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No)
        return;

    if (userManager.supprimer(userId)) {
        QMessageBox::information(this, "Success", "User deleted successfully!");
        selectedUserId = -1;
        loadUsersTable();
    } else {
        QMessageBox::critical(this, "Error", "Failed to delete user.");
    }
}

// +++ Clear user form +++ reset to create mode +++
void appwindow::on_clear_3_clicked()
{
    ui->email->clear();
    ui->Fname->clear();
    ui->Lname->clear();
    ui->password->clear();
    ui->salary->clear();
    ui->role->setCurrentIndex(0);
    ui->gender->setCurrentIndex(0);
    ui->startShift->setDateTime(QDateTime::currentDateTime());
    ui->endShift->setDateTime(QDateTime::currentDateTime());

    ui->searchbar_3->clear();
    ui->comboBox_11->setCurrentIndex(0);

    selectedUserId = -1;
    ui->UPDUser->setText("Create User 💫");
    if (ui->usersTable->selectionModel()) {
        ui->usersTable->selectionModel()->clearSelection();
    }
}

void appwindow::on_editUSERBtn_clicked()
{
    int row = ui->usersTable->currentRow();

    if (row < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a user row first.");
        return;
    }

    fillUserForm(ui->usersTable->model()->index(row, 0));
}






// =====================================================================
// ===================== END OF USER MODULE ============================
// =====================================================================






///PRODUCT

// Add product

void appwindow::on_checkProductButton_2_clicked()
{
    QString type = ui->fishtype->text();
    QString status = ui->fishStatus->currentText();
    QString quantity = ui->qtyfish->text();
    QString price = ui->fishprice->text();
    QString location = ui->locationfish->text();

    if (type.isEmpty() || quantity.isEmpty() || price.isEmpty() || location.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill in all required fields!");
        return;
    }

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

    // Check if editing or creating
    if (selectedProductId > 0) {
        // Update existing product
        if (productManager.updateProduct(selectedProductId,
                                        type,
                                        location,
                                        status,
                                        qty,
                                        pr,
                                        ui->fishdate1->dateTime(),
                                        ui->fishdate2->dateTime())) {
            QMessageBox::information(this, "Success", "Product updated successfully!");
            selectedProductId = -1;  // Reset for next operation
        } else {
            QMessageBox::critical(this, "Error", "Failed to update product!");
            return;
        }
    } else {
        // Create new product
        if (!productManager.createProduct(type,
                                         location,
                                         status,
                                         qty,
                                         pr,
                                         ui->fishdate1->dateTime(),
                                         ui->fishdate2->dateTime())) {
            QMessageBox::critical(this, "Error", "Failed to add product. Please check the database connection.");
            return;
        }
        QMessageBox::information(this, "Success", "Product added successfully!");
    }

    // Clear form
    ui->prodcode->clear();
    ui->fishtype->clear();
    ui->fishStatus->setCurrentIndex(0);
    ui->qtyfish->clear();
    ui->fishprice->clear();
    ui->fishdate1->setDateTime(QDateTime::currentDateTime());
    ui->fishdate2->setDateTime(QDateTime::currentDateTime());
    ui->locationfish->clear();
    selectedProductId = -1;
    
    // Reset button text back to "Add Product"
    ui->checkProductButton_2->setText("Add Product");
    
    // Refresh the table on manage page
    loadProductTable();
}

void appwindow::on_checkProductButton_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(1);  // Switch to Manage Products page
    loadProductTable();                        // Load the products
}

void appwindow::loadProductTable()
{
    QList<ProductRecord> records = productManager.getAllProducts();
    allProductRecords = records;  // Store all records for filtering
    qDebug() << "Product records fetched:" << records.size();

    QTableWidget *table = ui->tableWidget_10;
    table->setRowCount(0);
    table->setColumnCount(8);
    table->setHorizontalHeaderLabels(
        {"ID", "Status", "Type", "Fish Caught", "Date Purchase", "Quantity", "Location", "Price"});
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for (const ProductRecord &r : records) {
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::number(r.id)));
        table->setItem(row, 1, new QTableWidgetItem(r.status));
        table->setItem(row, 2, new QTableWidgetItem(r.type));
        table->setItem(row, 3, new QTableWidgetItem(r.fishCaught));
        table->setItem(row, 4, new QTableWidgetItem(r.dateOfPurchase));
        table->setItem(row, 5, new QTableWidgetItem(QString::number(r.quantity)));
        table->setItem(row, 6, new QTableWidgetItem(r.location));
        table->setItem(row, 7, new QTableWidgetItem(QString::number(r.price, 'f', 2)));
    }

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Update the count label
    ui->labelResults_6->setText(QString("Showing %1 Products").arg(records.size()));
}

void appwindow::on_Manage_24_clicked()
{
    loadProductTable();
}

void appwindow::on_tableWidget_10_cellClicked(int row, int /*column*/)
{
    if (row < 0) return;
    QString id = ui->tableWidget_10->item(row, 0)->text();
    selectedProductId = id.toInt();
    qDebug() << "Selected product ID:" << selectedProductId;
}

void appwindow::on_tableWidget_10_cellDoubleClicked(int row, int /*column*/)
{
    QTableWidget *table = ui->tableWidget_10;
    if (row < 0) return;

    selectedProductId = table->item(row, 0)->text().toInt();
    qDebug() << "Double-clicked product ID:" << selectedProductId;

    // Fill the form fields for editing
    ui->fishtype->setText(table->item(row, 2)->text());
    ui->qtyfish->setText(table->item(row, 5)->text());
    ui->fishprice->setText(table->item(row, 7)->text());
    ui->locationfish->setText(table->item(row, 6)->text());

    // Set status combobox
    int statusIdx = ui->fishStatus->findText(table->item(row, 1)->text());
    if (statusIdx >= 0) ui->fishStatus->setCurrentIndex(statusIdx);

    // Set date times
    QString fishCaughtStr = table->item(row, 3)->text();
    QString dateOfPurchaseStr = table->item(row, 4)->text();

    QDateTime fishCaughtDt = QDateTime::fromString(fishCaughtStr, "yyyy-MM-dd HH:mm:ss");
    if (!fishCaughtDt.isValid()) {
        fishCaughtDt = QDateTime::fromString(fishCaughtStr, "yyyy-MM-dd hh:mm:ss");
    }
    if (fishCaughtDt.isValid()) {
        ui->fishdate1->setDateTime(fishCaughtDt);
    }

    QDateTime dateOfPurchaseDt = QDateTime::fromString(dateOfPurchaseStr, "yyyy-MM-dd HH:mm:ss");
    if (!dateOfPurchaseDt.isValid()) {
        dateOfPurchaseDt = QDateTime::fromString(dateOfPurchaseStr, "yyyy-MM-dd hh:mm:ss");
    }
    if (dateOfPurchaseDt.isValid()) {
        ui->fishdate2->setDateTime(dateOfPurchaseDt);
    }

    // Update button text to show we're editing
    ui->checkProductButton_2->setText("Edit Product");
    
    // Navigate to the Add Product page to edit
    ui->stackedWidget_4->setCurrentIndex(0);
}

void appwindow::on_edit_company_6_clicked()
{
    if (selectedProductId <= 0) {
        QMessageBox::warning(this, "Error", "Please select a product to edit!");
        return;
    }

    // Find the product in the table to get current data
    QTableWidget *table = ui->tableWidget_10;
    int row = -1;
    for (int i = 0; i < table->rowCount(); i++) {
        if (table->item(i, 0)->text().toInt() == selectedProductId) {
            row = i;
            break;
        }
    }

    if (row < 0) {
        QMessageBox::warning(this, "Error", "Product not found in table!");
        return;
    }

    // Fill the form fields for editing
    ui->fishtype->setText(table->item(row, 2)->text());
    ui->qtyfish->setText(table->item(row, 5)->text());
    ui->fishprice->setText(table->item(row, 7)->text());
    ui->locationfish->setText(table->item(row, 6)->text());

    // Set status combobox
    int statusIdx = ui->fishStatus->findText(table->item(row, 1)->text());
    if (statusIdx >= 0) ui->fishStatus->setCurrentIndex(statusIdx);

    // Set date times
    QString fishCaughtStr = table->item(row, 3)->text();
    QString dateOfPurchaseStr = table->item(row, 4)->text();

    QDateTime fishCaughtDt = QDateTime::fromString(fishCaughtStr, "yyyy-MM-dd HH:mm:ss");
    if (!fishCaughtDt.isValid()) {
        fishCaughtDt = QDateTime::fromString(fishCaughtStr, "yyyy-MM-dd hh:mm:ss");
    }
    if (fishCaughtDt.isValid()) {
        ui->fishdate1->setDateTime(fishCaughtDt);
    }

    QDateTime dateOfPurchaseDt = QDateTime::fromString(dateOfPurchaseStr, "yyyy-MM-dd HH:mm:ss");
    if (!dateOfPurchaseDt.isValid()) {
        dateOfPurchaseDt = QDateTime::fromString(dateOfPurchaseStr, "yyyy-MM-dd hh:mm:ss");
    }
    if (dateOfPurchaseDt.isValid()) {
        ui->fishdate2->setDateTime(dateOfPurchaseDt);
    }

    // Update button text to show we're editing
    ui->checkProductButton_2->setText("Edit Product");
    
    // Navigate to the Add Product page to edit
    ui->stackedWidget_4->setCurrentIndex(0);
}

void appwindow::on_delete_company_6_clicked()
{
    if (selectedProductId <= 0) {
        QMessageBox::warning(this, "Error", "Please select a product to delete!");
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirm Delete",
                                                             "Are you sure you want to delete this product?",
                                                             QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (productManager.deleteProduct(selectedProductId)) {
            QMessageBox::information(this, "Success", "Product deleted successfully!");
            loadProductTable();
            // Clear form
            ui->fishtype->clear();
            ui->fishStatus->setCurrentIndex(0);
            ui->qtyfish->clear();
            ui->fishprice->clear();
            ui->locationfish->clear();
            ui->prodcode->clear();
            ui->fishdate1->setDateTime(QDateTime::currentDateTime());
            ui->fishdate2->setDateTime(QDateTime::currentDateTime());
            selectedProductId = -1;
            
            // Reset button text
            ui->checkProductButton_2->setText("Add Product");
        } else {
            QMessageBox::critical(this, "Error", "Failed to delete product!");
        }
    }
}

void appwindow::on_clear_6_clicked()
{
    ui->fishtype->clear();
    ui->fishStatus->setCurrentIndex(0);
    ui->qtyfish->clear();
    ui->fishprice->clear();
    ui->locationfish->clear();
    ui->fishdate1->setDateTime(QDateTime::currentDateTime());
    ui->fishdate2->setDateTime(QDateTime::currentDateTime());
    ui->prodcode->clear();
    selectedProductId = -1;
    
    // Reset button text to "Add Product"
    ui->checkProductButton_2->setText("Add Product");
    
    // Clear search and reload all products
    ui->searchbar_6->blockSignals(true);
    ui->searchbar_6->clear();
    ui->searchbar_6->blockSignals(false);
    ui->comboBox_18->setCurrentIndex(0);
    loadProductTable();
}

void appwindow::on_searchbar_6_textChanged(const QString &text)
{
    QString searchText = text.trimmed();
    QList<ProductRecord> filteredRecords;

    if (searchText.isEmpty()) {
        filteredRecords = allProductRecords;
    } else {
        bool isNumeric;
        searchText.toInt(&isNumeric);
        
        // If search text is numeric, search by ID only
        for (const ProductRecord &r : allProductRecords) {
            if (isNumeric && QString::number(r.id).contains(searchText)) {
                filteredRecords.append(r);
            } else if (!isNumeric && (
                r.type.contains(searchText, Qt::CaseInsensitive) ||
                r.status.contains(searchText, Qt::CaseInsensitive) ||
                r.location.contains(searchText, Qt::CaseInsensitive))) {
                filteredRecords.append(r);
            }
        }
    }

    // Apply the current sort to the filtered results
    int sortIndex = ui->comboBox_18->currentIndex();
    on_comboBox_18_currentIndexChanged(sortIndex);
}

void appwindow::on_comboBox_18_currentIndexChanged(int index)
{
    // Get the current filtered records (or all if no filter)
    QString searchText = ui->searchbar_6->text().trimmed();
    QList<ProductRecord> recordsToDisplay;

    if (searchText.isEmpty()) {
        recordsToDisplay = allProductRecords;
    } else {
        bool isNumeric;
        searchText.toInt(&isNumeric);
        
        // If search text is numeric, search by ID only
        for (const ProductRecord &r : allProductRecords) {
            if (isNumeric && QString::number(r.id).contains(searchText)) {
                recordsToDisplay.append(r);
            } else if (!isNumeric && (
                r.type.contains(searchText, Qt::CaseInsensitive) ||
                r.status.contains(searchText, Qt::CaseInsensitive) ||
                r.location.contains(searchText, Qt::CaseInsensitive))) {
                recordsToDisplay.append(r);
            }
        }
    }

    // Sort based on index
    if (index == 1) {  // Sort by Price
        std::sort(recordsToDisplay.begin(), recordsToDisplay.end(), [](const ProductRecord &a, const ProductRecord &b) {
            return a.price < b.price;
        });
    }
    // index == 0 is Type (default, no sorting needed as they come in order)

    // Update the table with filtered/sorted records
    QTableWidget *table = ui->tableWidget_10;
    table->setRowCount(0);

    for (const ProductRecord &r : recordsToDisplay) {
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::number(r.id)));
        table->setItem(row, 1, new QTableWidgetItem(r.status));
        table->setItem(row, 2, new QTableWidgetItem(r.type));
        table->setItem(row, 3, new QTableWidgetItem(r.fishCaught));
        table->setItem(row, 4, new QTableWidgetItem(r.dateOfPurchase));
        table->setItem(row, 5, new QTableWidgetItem(QString::number(r.quantity)));
        table->setItem(row, 6, new QTableWidgetItem(r.location));
        table->setItem(row, 7, new QTableWidgetItem(QString::number(r.price, 'f', 2)));
    }

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Update the count label
    ui->labelResults_6->setText(QString("Showing %1 Products").arg(recordsToDisplay.size()));
}

void appwindow::on_export_pdf_6_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Export Product Data to PDF"), "",
                                                    tr("PDF Files (*.pdf);;All Files (*)"));

    if (fileName.isEmpty())
        return;

    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive))
        fileName += ".pdf";

    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setPageOrientation(QPageLayout::Landscape);
    pdfWriter.setResolution(300);
    pdfWriter.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);

    QPainter painter(&pdfWriter);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor darkBlue(0, 102, 204);
    QColor veryLightBlue(230, 242, 255);
    QColor textColor(30, 30, 30);
    QColor borderColor(180, 180, 180);

    int pageWidth  = pdfWriter.width();
    int pageHeight = pdfWriter.height();

    int marginLeft   = 0;
    int marginTop    = 0;
    int contentWidth = pageWidth;

    int yPos = marginTop;

    // ── TITLE BLOCK ──────────────────────────────────────────────────────────
    int titleBlockHeight = 120;
    painter.fillRect(marginLeft, yPos, contentWidth, titleBlockHeight, darkBlue);

    QFont titleFont("Arial", 32, QFont::Bold);
    painter.setFont(titleFont);
    painter.setPen(Qt::white);
    painter.drawText(marginLeft, yPos, contentWidth, titleBlockHeight,
                     Qt::AlignCenter | Qt::AlignVCenter, "PRODUCT DATA REPORT");

    yPos += titleBlockHeight + 30;

    // ── DATE LINE ────────────────────────────────────────────────────────────
    QFont dateFont("Arial", 11);
    painter.setFont(dateFont);
    painter.setPen(QColor(100, 100, 100));
    painter.drawText(marginLeft, yPos,
                     QString("Generated: %1")
                         .arg(QDateTime::currentDateTime()
                                  .toString("yyyy-MM-dd  hh:mm:ss")));
    yPos += 50;

    // ── TABLE ─────────────────────────────────────────────────────────────────
    QTableWidget *table = ui->tableWidget_10;
    int rowCount    = table->rowCount();
    int columnCount = table->columnCount();

    if (rowCount == 0) {
        painter.setFont(QFont("Arial", 14));
        painter.setPen(textColor);
        painter.drawText(marginLeft, yPos, "No data to export.");
        painter.end();
        QMessageBox::information(this, "No Data", "The table is empty. Nothing to export.");
        return;
    }

    int columnWidth = contentWidth / columnCount;
    int headerHeight = 80;

    auto drawHeader = [&]() {
        painter.fillRect(marginLeft, yPos, contentWidth, headerHeight, darkBlue);

        QFont headerFont("Arial", 13, QFont::Bold);
        painter.setFont(headerFont);
        painter.setPen(Qt::white);

        int xPos = marginLeft;
        for (int col = 0; col < columnCount; col++) {
            QString headerText = table->horizontalHeaderItem(col)
            ? table->horizontalHeaderItem(col)->text()
            : "";
            painter.drawText(xPos + 8, yPos, columnWidth - 16, headerHeight,
                             Qt::AlignCenter | Qt::AlignVCenter | Qt::TextWordWrap,
                             headerText);

            if (col < columnCount - 1) {
                painter.setPen(QPen(Qt::white, 2));
                painter.drawLine(xPos + columnWidth, yPos,
                                 xPos + columnWidth, yPos + headerHeight);
                painter.setPen(Qt::white);
            }
            xPos += columnWidth;
        }
    };

    drawHeader();
    yPos += headerHeight;

    int rowHeight    = 75;
    int footerHeight = 80;
    int rowsPerPage  = (pageHeight - yPos - footerHeight) / rowHeight;

    QFont cellFont("Arial", 11);
    painter.setFont(cellFont);

    for (int row = 0; row < rowCount; row++) {

        // ── New page if needed ──
        if (row > 0 && row % rowsPerPage == 0) {
            pdfWriter.newPage();
            yPos = marginTop;
            drawHeader();
            yPos += headerHeight;
            painter.setFont(cellFont);
        }

        QColor rowBg = (row % 2 == 0) ? Qt::white : veryLightBlue;
        painter.fillRect(marginLeft, yPos, contentWidth, rowHeight, rowBg);

        painter.setPen(QPen(borderColor, 1));
        painter.drawRect(marginLeft, yPos, contentWidth, rowHeight);

        int xPos = marginLeft;
        for (int col = 0; col < columnCount; col++) {
            QTableWidgetItem *item = table->item(row, col);
            QString cellText = item ? item->text() : "";

            painter.setPen(textColor);
            painter.drawText(xPos + 10, yPos, columnWidth - 20, rowHeight,
                             Qt::AlignCenter | Qt::AlignVCenter | Qt::TextWordWrap,
                             cellText);

            if (col < columnCount - 1) {
                painter.setPen(QPen(borderColor, 1));
                painter.drawLine(xPos + columnWidth, yPos,
                                 xPos + columnWidth, yPos + rowHeight);
            }
            xPos += columnWidth;
        }

        yPos += rowHeight;
    }

    // ── FOOTER ───────────────────────────────────────────────────────────────
    yPos += 30;

    painter.setPen(QPen(darkBlue, 3));
    painter.drawLine(marginLeft, yPos, marginLeft + contentWidth, yPos);
    yPos += 20;

    painter.setFont(QFont("Arial", 11, QFont::Bold));
    painter.setPen(darkBlue);
    painter.drawText(marginLeft, yPos,
                     contentWidth, 50,
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QString("Total Records: %1").arg(rowCount));

    painter.drawText(marginLeft, yPos,
                     contentWidth, 50,
                     Qt::AlignRight | Qt::AlignVCenter,
                     QString("Marina Management System"));

    painter.end();

    QMessageBox::information(this, "Export Successful",
                             QString("PDF exported successfully to:\n%1").arg(fileName));
}

void appwindow::on_pushButton_12_clicked()
{
    // Get all products
    QList<ProductRecord> allProducts = productManager.getAllProducts();
    
    if (allProducts.isEmpty()) {
        QMessageBox::warning(this, "No Data", "No products in the system to analyze.");
        return;
    }
    
    // Determine which statistics to show
    int selectedOption = ui->comboBox_20->currentIndex();
    
    if (selectedOption == 0) {
        // Show statistics by Status
        generateProductStatisticsByStatus(allProducts);
    } else {
        // Show statistics by Preferred Fish (for companies)
        generateProductStatisticsByStatus(allProducts);
    }
}

void appwindow::generateProductStatisticsByStatus(const QList<ProductRecord> &products)
{
    // Group products by status and calculate totals
    QMap<QString, int> statusCount;
    QMap<QString, int> statusQuantity;
    int totalQuantity = 0;
    
    for (const ProductRecord &product : products) {
        statusCount[product.status]++;
        statusQuantity[product.status] += product.quantity;
        totalQuantity += product.quantity;
    }
    
    if (totalQuantity == 0) {
        QMessageBox::warning(this, "No Data", "No products with quantity data.");
        return;
    }
    
    // Calculate percentage of active/available products
    int activeQuantity = statusQuantity.value("Available", 0) + 
                         statusQuantity.value("In Stock", 0);
    int percentage = (totalQuantity > 0) ? (activeQuantity * 100) / totalQuantity : 0;
    
    // Update progress bar
    ui->progressBar_7->setValue(percentage);
    
    // Update label with statistics
    QString statsText = QString("Percentage of Active Products in system: %1%\n").arg(percentage);
    statsText += "---Status Breakdown---\n";
    
    for (auto it = statusQuantity.begin(); it != statusQuantity.end(); ++it) {
        int count = statusCount[it.key()];
        int qty = it.value();
        int pct = (qty * 100) / totalQuantity;
        statsText += QString("%1: %2 items, %3 units (%4%)\n")
                        .arg(it.key())
                        .arg(count)
                        .arg(qty)
                        .arg(pct);
    }
    
    ui->label_79->setText(statsText);
    
    QMessageBox::information(this, "Product Statistics", statsText);
}


///END
appwindow::~appwindow()
{
    delete ui;
}




//boat section

// ─────────────────────────────────────────────
//  Mode helper — switches label, shows/hides buttons
// ─────────────────────────────────────────────
void appwindow::setBoatMode(BoatMode mode)
{
    currentBoatMode = mode;

    if (mode == BoatMode::Add) {
        ui->label_99->setText("Create Boat:");
        ui->addBoatButton->setVisible(true);
        ui->editBoatButton->setVisible(false);
        clearBoatInputs();
    } else {
        ui->label_99->setText("Edit Boat:");
        ui->addBoatButton->setVisible(false);
        ui->editBoatButton->setVisible(true);
    }
}

// ─────────────────────────────────────────────
//  Shared helper — loads a boat into the form fields
// ─────────────────────────────────────────────
void appwindow::populateBoatForm(int boatId)
{
    boatsTmp.setId(boatId);
    boatsTmp.read();

    if (!boatsTmp.getLastError().isEmpty()) {
        QMessageBox::warning(this, "Load Error",
                             "Could not load boat: " + boatsTmp.getLastError());
        return;
    }

    currentlySelectedId = boatId;

    ui->boatSizeLineEdit->setText(boatsTmp.getSize());
    ui->boatLocationLineEdit->setText(boatsTmp.getLocation());
    ui->boatOwnerNameLineEdit->setText(boatsTmp.getOwnerName());
    ui->boatOwnerEmailLineEdit->setText(boatsTmp.getOwnerEmail());
    ui->boatStatusComboBox->setCurrentIndex(boatsTmp.getStatus());
    ui->boatTypeLineEdit->setText(boatsTmp.getType());

    QDate date = QDate::fromString(boatsTmp.getLastMaintenanceDate(), "yyyy-MM-dd");
    ui->boatMaintenanceDateEdit->setDate(date.isValid() ? date : QDate::currentDate());

    ui->boatTripsSpinBox->setValue(boatsTmp.getTotalTrips());
    ui->boatFishSpinBox->setValue(boatsTmp.getTotalFish());
}

void appwindow::displayBoats()
{
    // Block signals so inserting rows does not fire itemClicked,
    // which would overwrite input fields and reset currentlySelectedId.
    ui->Boatwidget_2->blockSignals(true);

    ui->Boatwidget_2->setRowCount(0);
    ui->Boatwidget_2->setColumnCount(10);

    QStringList headers;
    headers << "Boat ID" << "Size" << "Location" << "Owner Name"
            << "Owner Email" << "Status" << "Type" << "Last Maintenance"
            << "Total Trips" << "Total Fish";
    ui->Boatwidget_2->setHorizontalHeaderLabels(headers);

    QSqlQuery query = Boats::getAll();

    if (!query.isActive()) {
        ui->Boatwidget_2->blockSignals(false);
        QMessageBox::critical(this, "Error", "Failed to retrieve boats");
        return;
    }

    int row = 0;
    while (query.next()) {
        ui->Boatwidget_2->insertRow(row);

        for (int col = 0; col < 10; col++) {
            QTableWidgetItem *item;

            if (col == 5) {
                int statusValue = query.value(col).toInt();
                QString statusText = (statusValue == 1) ? "IN PORT" : "OUT";
                item = new QTableWidgetItem(statusText);
            } else {
                item = new QTableWidgetItem(query.value(col).toString());
            }

            if (col == 0) {
                item->setData(Qt::UserRole, query.value("BOATID").toInt());
            }

            ui->Boatwidget_2->setItem(row, col, item);
        }
        row++;
    }

    ui->Boatwidget_2->resizeColumnsToContents();
    ui->Boatwidget_2->horizontalHeader()->setStretchLastSection(true);

    // Restore signals now that the table is fully populated
    ui->Boatwidget_2->blockSignals(false);
}

void appwindow::clearBoatInputs()
{
    ui->boatSizeLineEdit->clear();
    ui->boatLocationLineEdit->clear();
    ui->boatOwnerNameLineEdit->clear();
    ui->boatOwnerEmailLineEdit->clear();
    ui->boatStatusComboBox->setCurrentIndex(1); // Default to IN PORT
    ui->boatTypeLineEdit->clear();
    ui->boatMaintenanceDateEdit->setDate(QDate::currentDate());
    ui->boatTripsSpinBox->setValue(0);
    ui->boatFishSpinBox->setValue(0);
    ui->boatSearchLineEdit->clear();

    currentlySelectedId = -1;
    ui->deleteBoatButton->setEnabled(false);
    ui->updateBoatButton->setEnabled(false);
}


void appwindow::on_Boatwidget_2_clicked(QTableWidgetItem *item)
{
    if (!item) return;

    int currentRow = ui->Boatwidget_2->currentRow();
    if (currentRow < 0) return;

    QTableWidgetItem *idItem = ui->Boatwidget_2->item(currentRow, 0);
    if (idItem) {
        currentlySelectedId = idItem->data(Qt::UserRole).toInt();
        qDebug() << "Selected boat ID:" << currentlySelectedId;

        // Enable action buttons on the list page
        ui->deleteBoatButton->setEnabled(true);
        ui->updateBoatButton->setEnabled(true);
    }
}

// ─────────────────────────────────────────────
//  Double-click → populate form and switch to Edit mode
// ─────────────────────────────────────────────
void appwindow::on_Boatwidget_2_itemDoubleClicked(QTableWidgetItem *item)
{
    if (!item) return;

    int currentRow = ui->Boatwidget_2->currentRow();
    if (currentRow < 0) return;

    QTableWidgetItem *idItem = ui->Boatwidget_2->item(currentRow, 0);
    if (!idItem) return;

    int boatId = idItem->data(Qt::UserRole).toInt();

    // Load data into the form
    populateBoatForm(boatId);

    // Switch to Edit mode and navigate to the form page
    setBoatMode(BoatMode::Edit);
    ui->boatPage->setCurrentIndex(0);
}




void appwindow::on_addBoatButton_clicked()
{
    // Input validation
    if (ui->boatSizeLineEdit->text().isEmpty() ||
        ui->boatLocationLineEdit->text().isEmpty() ||
        ui->boatOwnerNameLineEdit->text().isEmpty() ||
        ui->boatOwnerEmailLineEdit->text().isEmpty() ||
        ui->boatTypeLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "All fields must be filled!");
        return;
    }

    // Email validation (basic)
    if (!ui->boatOwnerEmailLineEdit->text().contains('@')) {
        QMessageBox::warning(this, "Validation Error", "Please enter a valid email address!");
        return;
    }

    // Create boats object with input data (ID is auto-generated, so we pass 0)
    Boats newBoat(
        0, // ID is auto-generated, value will be ignored in create()
        ui->boatSizeLineEdit->text(),
        ui->boatLocationLineEdit->text(),
        ui->boatOwnerNameLineEdit->text(),
        ui->boatOwnerEmailLineEdit->text(),
        ui->boatStatusComboBox->currentIndex(), // 1=IN PORT, 0=OUT
        ui->boatTypeLineEdit->text(),
        ui->boatMaintenanceDateEdit->date().toString("yyyy-MM-dd"),
        ui->boatTripsSpinBox->value(),
        ui->boatFishSpinBox->value()
        );

    // Call create method
    if (newBoat.create()) {
        QMessageBox::information(this, "Success",
                                 "Boat added successfully with ID: " + QString::number(newBoat.getId()));
        clearBoatInputs();
        displayBoats(); // Refresh display after addition
    } else {
        QMessageBox::critical(this, "Error", "Failed to add boat: " + newBoat.getLastError());
    }
}

// ─────────────────────────────────────────────
//  "Save Changes" button on the form (Edit mode only)
// ─────────────────────────────────────────────
void appwindow::on_editBoatButton_clicked()
{
    if (currentlySelectedId <= 0) {
        QMessageBox::warning(this, "Selection Error", "No boat selected for editing.");
        return;
    }

    // Validation
    if (ui->boatSizeLineEdit->text().trimmed().isEmpty() ||
        ui->boatLocationLineEdit->text().trimmed().isEmpty() ||
        ui->boatOwnerNameLineEdit->text().trimmed().isEmpty() ||
        ui->boatOwnerEmailLineEdit->text().trimmed().isEmpty() ||
        ui->boatTypeLineEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "All fields must be filled!");
        return;
    }
    if (!ui->boatOwnerEmailLineEdit->text().contains('@')) {
        QMessageBox::warning(this, "Validation Error", "Please enter a valid email address!");
        return;
    }

    int     boatId  = currentlySelectedId;
    QString size    = ui->boatSizeLineEdit->text().trimmed();
    QString loc     = ui->boatLocationLineEdit->text().trimmed();
    QString oName   = ui->boatOwnerNameLineEdit->text().trimmed();
    QString oEmail  = ui->boatOwnerEmailLineEdit->text().trimmed();
    int     status  = ui->boatStatusComboBox->currentIndex();
    QString type    = ui->boatTypeLineEdit->text().trimmed();
    QString dateStr = ui->boatMaintenanceDateEdit->date().toString("dd-MMM-yyyy").toUpper();
    int     trips   = ui->boatTripsSpinBox->value();
    int     fish    = ui->boatFishSpinBox->value();

    qDebug() << "=== EDIT BOAT ATTEMPT ===" << "ID:" << boatId << "Date:" << dateStr;

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "DB Error", "Database is not open!");
        return;
    }

    QSqlQuery q(db);
    q.prepare(
        "UPDATE BOAT SET "
        "  SIZEBOAT            = :size,    "
        "  LOCATION            = :loc,     "
        "  OWNERNAME           = :oName,   "
        "  OWNERMAIL           = :oEmail,  "
        "  STATUS              = :status,  "
        "  TYPE                = :type,    "
        "  LASTMAINTENANCEDATE = TO_DATE(:dateStr, 'DD-MON-YYYY'), "
        "  TOTALTRIPS          = :trips,   "
        "  TOTALFISH           = :fish     "
        "WHERE BOATID = :boatId"
    );
    q.bindValue(":size",    size);
    q.bindValue(":loc",     loc);
    q.bindValue(":oName",   oName);
    q.bindValue(":oEmail",  oEmail);
    q.bindValue(":status",  status);
    q.bindValue(":type",    type);
    q.bindValue(":dateStr", dateStr);
    q.bindValue(":trips",   trips);
    q.bindValue(":fish",    fish);
    q.bindValue(":boatId",  boatId);

    if (!q.exec()) {
        QString err = q.lastError().text();
        qDebug() << "EDIT FAILED:" << err;
        QMessageBox::critical(this, "Update Failed",
                              "Oracle error:\n\n" + err +
                              "\n\nBoat ID: " + QString::number(boatId) +
                              "\nDate sent: " + dateStr);
        return;
    }

    if (q.numRowsAffected() == 0) {
        QMessageBox::warning(this, "Not Updated",
                             "No row was changed. Boat ID " +
                             QString::number(boatId) + " may not exist.");
        return;
    }

    QMessageBox::information(this, "Success", "Boat updated successfully!");
    displayBoats();

    // Return to list page and reset back to Add mode
    setBoatMode(BoatMode::Add);
    ui->boatPage->setCurrentIndex(1);
}

// FIXED
void appwindow::on_deleteBoatButton_clicked()
{
    if (currentlySelectedId <= 0) {
        QMessageBox::warning(this, "Selection Error", "Please select a boat to delete!");        QMessageBox::warning(this, "Selection Error", "Please select a boat to delete!");
        return;
    }

    // Confirm deletion
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirm Delete",
        "Are you sure you want to delete boat with ID: " + QString::number(currentlySelectedId) + "?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        // Set the ID in the temporary boats object
        boatsTmp.setId(currentlySelectedId);

        // Call delete method
        if (boatsTmp.deleteBoat()) {
            QMessageBox::information(this, "Success", "Boat deleted successfully!");
            clearBoatInputs();
            displayBoats(); // Refresh display after deletion
        } else {
            QMessageBox::critical(this, "Error", "Failed to delete boat: " + boatsTmp.getLastError());
        }
    }
}

// ─────────────────────────────────────────────
//  "Edit" button on the list page → navigate to form in Edit mode
// ─────────────────────────────────────────────
void appwindow::on_updateBoatButton_clicked()
{
    if (currentlySelectedId <= 0) {
        QMessageBox::warning(this, "Selection Error",
                             "Please click a row in the table first to select a boat.");
        return;
    }

    // Load data into the form and switch to Edit mode
    populateBoatForm(currentlySelectedId);
    setBoatMode(BoatMode::Edit);
    ui->boatPage->setCurrentIndex(0);
}


void appwindow::on_searchBoatButton_3_clicked()
{
    // Search by ID
    if (ui->boatSearchLineEdit->text().isEmpty()) {
        displayBoats(); // Show all if search is empty
        return;
    }

    bool ok;
    int id = ui->boatSearchLineEdit->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Validation Error", "Search ID must be a number!");
        return;
    }

    // Clear table and show only the searched boat
    ui->Boatwidget_2->setRowCount(0);

    // Set ID in temporary boats and read from database
    boatsTmp.setId(id);
    boatsTmp.read();

    if (boatsTmp.getLastError().isEmpty()) {
        ui->Boatwidget_2->insertRow(0);
        ui->Boatwidget_2->setItem(0, 0, new QTableWidgetItem(QString::number(boatsTmp.getId())));
        ui->Boatwidget_2->setItem(0, 1, new QTableWidgetItem(boatsTmp.getSize()));
        ui->Boatwidget_2->setItem(0, 2, new QTableWidgetItem(boatsTmp.getLocation()));
        ui->Boatwidget_2->setItem(0, 3, new QTableWidgetItem(boatsTmp.getOwnerName()));
        ui->Boatwidget_2->setItem(0, 4, new QTableWidgetItem(boatsTmp.getOwnerEmail()));

        QString statusText = boatsTmp.getStatus() == 1 ? "IN PORT" : "OUT";
        ui->Boatwidget_2->setItem(0, 5, new QTableWidgetItem(statusText));

        ui->Boatwidget_2->setItem(0, 6, new QTableWidgetItem(boatsTmp.getType()));
        ui->Boatwidget_2->setItem(0, 7, new QTableWidgetItem(boatsTmp.getLastMaintenanceDate()));
        ui->Boatwidget_2->setItem(0, 8, new QTableWidgetItem(QString::number(boatsTmp.getTotalTrips())));
        ui->Boatwidget_2->setItem(0, 9, new QTableWidgetItem(QString::number(boatsTmp.getTotalFish())));

        // Store the boat ID in the first column item
        ui->Boatwidget_2->item(0, 0)->setData(Qt::UserRole, boatsTmp.getId());
    } else {
        QMessageBox::information(this, "Not Found", "No boat found with ID: " + QString::number(id));
        displayBoats(); // Show all boats
    }
}
///=============COMPANY SECTION=============


void appwindow::loadCompaniesTable()
{
    QList<CompanyRecord> records = companyManager.getAllCompanies();

    QTableWidget *table = ui->tableWidget_11;
    table->setRowCount(0);
    table->setColumnCount(7);
    table->setHorizontalHeaderLabels(
        {"ID", "Name", "Location", "Email", "Phone", "Preferred Fish", "Status"});
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setAlternatingRowColors(true);

    for (const CompanyRecord &r : records) {
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::number(r.id())));
        table->setItem(row, 1, new QTableWidgetItem(r.name()));
        table->setItem(row, 2, new QTableWidgetItem(r.location()));
        table->setItem(row, 3, new QTableWidgetItem(r.email()));
        table->setItem(row, 4, new QTableWidgetItem(r.phone()));
        table->setItem(row, 5, new QTableWidgetItem(r.preferredFish()));
        table->setItem(row, 6, new QTableWidgetItem(r.status()));
    }

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->labelResults_7->setText(QString("Showing %1 Companies").arg(records.size()));
}

void appwindow::fillCompanyForm(int row)
{
    if (row < 0) return;

    QTableWidget *table = ui->tableWidget_11;

    selectedCompanyId = table->item(row, 0)->text().toInt();

    ui->firstNameEdit_8->setText(table->item(row, 1)->text());   // Name
    ui->lastNameEdit_7->setText(table->item(row, 2)->text());    // Location
    ui->emailEdit_4->setText(table->item(row, 3)->text());       // Email
    ui->passwordEdit_3->setText(table->item(row, 4)->text());    // Phone
    ui->lastNameEdit_8->setText(table->item(row, 5)->text());    // Preferred Fish

    int statusIdx = ui->role_option_7->findText(table->item(row, 6)->text());
    if (statusIdx >= 0) ui->role_option_7->setCurrentIndex(statusIdx);

    // Switch to Add page and update button label
    ui->stackedWidget_5->setCurrentIndex(0);
    ui->CreateUser_3->setText("Update Company");
}

void appwindow::on_tableWidget_11_cellClicked(int row, int /*column*/)
{
    if (row < 0 || !ui->tableWidget_11->item(row, 0)) return;
    selectedCompanyId = ui->tableWidget_11->item(row, 0)->text().toInt();
}

void appwindow::on_tableWidget_11_cellDoubleClicked(int row, int column)
{
    Q_UNUSED(column);
    fillCompanyForm(row);
}

///CREATE / UPDATE
void appwindow::on_CreateUser_3_clicked()
{
    QString name         = ui->firstNameEdit_8->text().trimmed();
    QString location     = ui->lastNameEdit_7->text().trimmed();
    QString email        = ui->emailEdit_4->text().trimmed();
    QString phone        = ui->passwordEdit_3->text().trimmed();
    QString preferredFish= ui->lastNameEdit_8->text().trimmed();
    QString status       = ui->role_option_7->currentText();

    // ===== VALIDATION =====
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Company name is required.");
        return;
    }
    if (location.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Location is required.");
        return;
    }
    if (email.isEmpty() || !email.contains('@')) {
        QMessageBox::warning(this, "Validation Error", "A valid email is required.");
        return;
    }
    if (phone.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Phone number is required.");
        return;
    }
    // Phone: digits only
    for (QChar c : phone) {
        if (!c.isDigit() && c != '+' && c != '-' && c != ' ') {
            QMessageBox::warning(this, "Validation Error", "Phone must contain only digits.");
            return;
        }
    }
    if (preferredFish.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Preferred fish is required.");
        return;
    }

    // ===== ALL VALIDATIONS PASSED =====
    bool isEditMode = (selectedCompanyId != -1);
    bool success = false;

    if (isEditMode) {
        success = companyManager.updateCompany(selectedCompanyId, name, location,
                                               email, phone, preferredFish, status);
    } else {
        success = companyManager.createCompany(name, location, email,
                                               phone, preferredFish, status);
    }

    if (success) {
        QMessageBox::information(this, "Success",
                                 isEditMode ? "Company updated successfully!" : "Company created successfully!");

        // Clear form
        ui->firstNameEdit_8->clear();
        ui->lastNameEdit_7->clear();
        ui->emailEdit_4->clear();
        ui->passwordEdit_3->clear();
        ui->lastNameEdit_8->clear();
        ui->role_option_7->setCurrentIndex(0);
        ui->CreateUser_3->setText("Create Company");
        selectedCompanyId = -1;

        loadCompaniesTable();
        if (isEditMode) {
            ui->stackedWidget_5->setCurrentIndex(1); // go back to manage page
        }
    } else {
        QMessageBox::critical(this, "Error",
                              isEditMode ? "Failed to update company." : "Failed to create company.");
    }
}

///EDIT
void appwindow::on_edit_company_7_clicked()
{
    int row = ui->tableWidget_11->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a company row first.");
        return;
    }
    fillCompanyForm(row);
}

///DELETE
void appwindow::on_delete_company_7_clicked()
{
    QModelIndexList selected = ui->tableWidget_11->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "No Selection", "Please select a company to delete.");
        return;
    }

    int row = selected.first().row();
    int id  = ui->tableWidget_11->item(row, 0)->text().toInt();
    QString name = ui->tableWidget_11->item(row, 1)->text();

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirm Delete",
        QString("Are you sure you want to delete \"%1\" (ID: %2)?").arg(name).arg(id),
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (companyManager.deleteCompany(id)) {
            QMessageBox::information(this, "Deleted", "Company deleted successfully.");
            selectedCompanyId = -1;
            loadCompaniesTable();
        } else {
            QMessageBox::critical(this, "Error", "Failed to delete company.");
        }
    }
}

///CLEAR
void appwindow::on_clear_7_clicked()
{
    ui->firstNameEdit_8->clear();
    ui->lastNameEdit_7->clear();
    ui->emailEdit_4->clear();
    ui->passwordEdit_3->clear();
    ui->lastNameEdit_8->clear();
    ui->role_option_7->setCurrentIndex(0);
    ui->searchbar_7->clear();
    ui->comboBox_19->setCurrentIndex(0);
    ui->CreateUser_3->setText("Create Company");
    selectedCompanyId = -1;

    if (ui->tableWidget_11->selectionModel())
        ui->tableWidget_11->selectionModel()->clearSelection();
}


