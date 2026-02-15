#include "appwindow.h"
#include "ui_appwindow.h"
#include "mainwindow.h"


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
    delete ui;
}




