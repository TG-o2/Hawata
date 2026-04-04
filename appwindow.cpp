#include "appwindow.h"
#include "ui_appwindow.h"
#include "mainwindow.h"
#include "smtpclient.h"

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
#include <QCoreApplication>
#include <QDir>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QCalendarWidget>
#include <QColor>
#include <QFrame>
#include <QLabel>
#include <QTextCharFormat>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QGraphicsProxyWidget>
#include <QHBoxLayout>

#include <QTimer>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QItemSelectionModel>
namespace {
QString normalizeMonthAbbreviation(const QString &value)
{
    QString normalized = value.trimmed();
    if (normalized.isEmpty()) {
        return normalized;
    }

    const QRegularExpression monthPattern(R"((\b\d{1,2}[-/ ])([A-Za-z]{3})([-/ ]\d{2,4}\b))");
    QRegularExpressionMatch match = monthPattern.match(normalized);
    if (match.hasMatch()) {
        QString month = match.captured(2).toLower();
        month[0] = month[0].toUpper();
        normalized = match.captured(1) + month + match.captured(3);
    }

    return normalized;
}

QDate normalizeTwoDigitYear(QDate date)
{
    if (date.isValid() && date.year() < 1950) {
        return date.addYears(100);
    }

    return date;
}

QDate parseDockingDate(const QString &value)
{
    const QString trimmed = normalizeMonthAbbreviation(value);
    if (trimmed.isEmpty()) {
        return {};
    }

    const QStringList dateFormats = {
        "dd/MM/yy",
        "dd/MM/yyyy",
        "dd-MM-yy",
        "dd-MM-yyyy",
        "dd-MMM-yy",
        "dd-MMM-yyyy",
        "yyyy-MM-dd",
        "yyyy-MM-dd hh:mm:ss",
        "yyyy-MM-ddThh:mm:ss",
        "MM/dd/yy",
        "MM/dd/yyyy",
        "ddd MMM d hh:mm:ss yyyy",
        "ddd MMM dd hh:mm:ss yyyy"
    };

    for (const QString &format : dateFormats) {
        QDate date = QDate::fromString(trimmed, format);
        if (date.isValid()) {
            return normalizeTwoDigitYear(date);
        }

        QDateTime dateTime = QDateTime::fromString(trimmed, format);
        if (dateTime.isValid()) {
            return normalizeTwoDigitYear(dateTime.date());
        }
    }

    QDateTime isoDateTime = QDateTime::fromString(trimmed, Qt::ISODate);
    if (isoDateTime.isValid()) {
        return normalizeTwoDigitYear(isoDateTime.date());
    }

    return {};
}

class DockCalendarWidget : public QCalendarWidget
{
public:
    explicit DockCalendarWidget(QWidget *parent = nullptr)
        : QCalendarWidget(parent)
    {
    }

    void setDockColors(const QMap<QDate, QColor> &colors)
    {
        m_dockColors = colors;
        updateCells();
    }

protected:
    void paintCell(QPainter *painter, const QRect &rect, QDate date) const override
    {
        QCalendarWidget::paintCell(painter, rect, date);

        const QColor color = m_dockColors.value(date);
        if (!color.isValid()) {
            return;
        }

        QColor overlay = color;
        overlay.setAlpha(150);

        painter->save();
        painter->setPen(Qt::NoPen);
        painter->setBrush(overlay);
        painter->drawRect(rect.adjusted(1, 1, -1, -1));
        painter->restore();
    }

private:
    QMap<QDate, QColor> m_dockColors;
};

int statusPriority(const QString &status)
{
    if (status.trimmed().compare("Occupied", Qt::CaseInsensitive) == 0) {
        return 2;
    }

    if (status.trimmed().compare("Available", Qt::CaseInsensitive) == 0) {
        return 1;
    }

    return 0;
}

QColor statusColor(const QString &status)
{
    if (status.trimmed().compare("Occupied", Qt::CaseInsensitive) == 0) {
        return QColor("#f87171");
    }

    if (status.trimmed().compare("Available", Qt::CaseInsensitive) == 0) {
        return QColor("#4ade80");
    }

    return QColor();
}
}

appwindow::appwindow(QWidget *parent, int currentUserId, const QString &currentUserRole)
    : QDialog(parent)
    , ui(new Ui::appwindow)
    , connectedUserId(currentUserId)
    , connectedUserRole(currentUserRole)
{
    ui->setupUi(this);
    currentlySelectedId = -1;
    loadDockingTable();
    loadUsersTable();
    loadProductTable();    // Load product table on startup
    loadCompaniesTable();
    generateDockingStatistics();
    loadDockingHistoryView();

    //load boat table
    displayBoats();
    connect(ui->comboBox_15, &QComboBox::currentIndexChanged,
            this, &appwindow::on_comboBox_15_currentIndexChanged);

    connect(ui->pushButton_10, &QPushButton::clicked, this, &appwindow::on_pushButton_10_clicked);
    updateBoatStatusProgressBar();

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
    //BOATS

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
    //product
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
        generateDockingStatistics();
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
        generateDockingStatistics();

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
        generateDockingStatistics();

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
        generateDockingStatistics();
    });
    connect(ui->forgetpwd_4  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(3);
        loadDockingHistoryView();
    });
    connect(ui->forgetpwd_2  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(3);
        loadDockingHistoryView();
    });
    connect(ui->forgetpwd_5  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(3);
        loadDockingHistoryView();
    });
    connect(ui->forgetpwd_6  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(3);
        loadDockingHistoryView();

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
        updateBoatStatusProgressBar();
    });
    connect(ui->Display_20  , &QPushButton::clicked, this, [=]() {
        ui->boatPage->setCurrentIndex(2);
        updateBoatStatusProgressBar();
    });
    connect(ui->Display_21  , &QPushButton::clicked, this, [=]() {
        ui->boatPage->setCurrentIndex(2);
        updateBoatStatusProgressBar();
    });
    connect(ui->Display_19  , &QPushButton::clicked, this, [=]() {
        ui->boatPage->setCurrentIndex(2);
        updateBoatStatusProgressBar();
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
        refreshLowStockAlerts(true);
    });
    connect(ui->forgetpwd_14  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(3);
        refreshLowStockAlerts(true);
    });
    connect(ui->forgetpwd_15  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(3);
        refreshLowStockAlerts(true);
    });
    connect(ui->forgetpwd_16  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(3);
        refreshLowStockAlerts(true);
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

    ui->comboBox_12->setCurrentIndex(0);
    loadUserStatistics(true);

    //BOATS STATUS BAR




    //BOATS EMAILS
    maintenanceCheckTimer = new QTimer(this);
    connect(maintenanceCheckTimer, &QTimer::timeout, this, &appwindow::onCheckMaintenanceReminders);
    maintenanceCheckTimer->start(86400000);


    QTimer::singleShot(5000, this, &appwindow::onCheckMaintenanceReminders); // Check after 5 seconds
}

QString appwindow::dockingHistoryFilePath() const
{
    QStringList startDirs;
    startDirs << QDir::currentPath() << QCoreApplication::applicationDirPath();

    for (const QString &startPath : startDirs) {
        QDir dir(startPath);
        for (int i = 0; i < 8; ++i) {
            if (dir.exists("CMakeLists.txt")) {
                return dir.filePath("docking_history.txt");
            }
            if (!dir.cdUp()) {
                break;
            }
        }
    }

    return QDir::current().filePath("docking_history.txt");
}

void appwindow::ensureDockingHistoryFile()
{
    QFile file(dockingHistoryFilePath());
    if (!file.exists()) {
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            file.close();
        }
    }
}

void appwindow::appendDockingHistory(const QString &action, int dockId)
{
    ensureDockingHistoryFile();

    QFile file(dockingHistoryFilePath());
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Failed to open docking_history.txt for append:" << file.errorString();
        return;
    }

    const QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    QTextStream out(&file);
    out << timestamp << "\t" << action.toUpper() << "\t" << dockId << "\n";
    file.close();

    if (ui->stackedWidget_2->currentIndex() == 3) {
        loadDockingHistoryView();
    }
}

void appwindow::loadDockingHistoryView()
{
    ensureDockingHistoryFile();

    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->history_view->model());
    if (!model) {
        model = new QStandardItemModel(ui->history_view);
        ui->history_view->setModel(model);
    }

    model->clear();
    model->setHorizontalHeaderLabels(QStringList() << "DateTime" << "Action" << "DockID");

    QFile file(dockingHistoryFilePath());
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QStringList lines;
        while (!in.atEnd()) {
            const QString line = in.readLine().trimmed();
            if (!line.isEmpty()) {
                lines.append(line);
            }
        }
        file.close();

        for (int i = lines.size() - 1; i >= 0; --i) {
            const QStringList parts = lines.at(i).split('\t');
            if (parts.size() < 3) {
                continue;
            }

            QList<QStandardItem*> row;
            for (int c = 0; c < 3; ++c) {
                QStandardItem *item = new QStandardItem(parts.at(c));
                item->setEditable(false);
                row.append(item);
            }
            model->appendRow(row);
        }
    }

    if (model->rowCount() == 0) {
        QList<QStandardItem*> row;
        row.append(new QStandardItem("-"));
        row.append(new QStandardItem("-"));
        row.append(new QStandardItem("-"));
        for (QStandardItem *item : row) {
            item->setEditable(false);
        }
        model->appendRow(row);
    }

    ui->history_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->history_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->history_view->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->history_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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

        appendDockingHistory("ADD", createdDockId);

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
    int updatedDockId = selectedDockingId;

    if (dockingManager.updateDocking(selectedDockingId, location, length,
                                     height, status, capacity, startDateStr, endDateStr)) {
        appendDockingHistory("UPDATE", updatedDockId);
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
            appendDockingHistory("DELETE", id);
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
    if (index == 1) {  // Ascending
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
    } else if (index == 2) {  // Descending
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
    allUserRecords = userManager.afficher_liste();

    int sortIndex = ui->comboBox_11->currentIndex();
    on_comboBox_11_currentIndexChanged(sortIndex);
}

void appwindow::on_searchbar_3_textChanged(const QString &text)
{
    Q_UNUSED(text);
    int sortIndex = ui->comboBox_11->currentIndex();
    on_comboBox_11_currentIndexChanged(sortIndex);
}

void appwindow::on_comboBox_11_currentIndexChanged(int index)
{
    QString searchText = ui->searchbar_3->text().trimmed();
    QList<User> recordsToDisplay;

    if (searchText.isEmpty()) {
        recordsToDisplay = allUserRecords;
    } else {
        bool isNumeric;
        searchText.toInt(&isNumeric);

        for (const User &r : allUserRecords) {
            if (isNumeric) {
                if (QString::number(r.getUserId()).contains(searchText)) {
                    recordsToDisplay.append(r);
                }
            } else if (r.getEmail().contains(searchText, Qt::CaseInsensitive)) {
                recordsToDisplay.append(r);
            }
        }
    }

    if (index == 0) { // Sort by Role
        std::sort(recordsToDisplay.begin(), recordsToDisplay.end(), [](const User &a, const User &b) {
            const int roleComparison = a.getRole().compare(b.getRole(), Qt::CaseInsensitive);
            if (roleComparison != 0) {
                return roleComparison < 0;
            }

            const int genderComparison = a.getGender().compare(b.getGender(), Qt::CaseInsensitive);
            if (genderComparison != 0) {
                return genderComparison < 0;
            }

            return a.getUserId() < b.getUserId();
        });
    } else if (index == 1) { // Sort by Gender
        std::sort(recordsToDisplay.begin(), recordsToDisplay.end(), [](const User &a, const User &b) {
            const int genderComparison = a.getGender().compare(b.getGender(), Qt::CaseInsensitive);
            if (genderComparison != 0) {
                return genderComparison < 0;
            }

            const int roleComparison = a.getRole().compare(b.getRole(), Qt::CaseInsensitive);
            if (roleComparison != 0) {
                return roleComparison < 0;
            }

            return a.getUserId() < b.getUserId();
        });
    }

    QTableWidget *table = ui->usersTable;
    table->setRowCount(0);
    table->setColumnCount(9);
    table->setHorizontalHeaderLabels(
        {"ID", "Email", "First Name", "Last Name", "Role", "Gender", "Salary", "Shift Start", "Shift End"});
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setAlternatingRowColors(true);

    for (const User &r : recordsToDisplay) {
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
    ui->labelResults_3->setText(QString("Showing %1 Users").arg(recordsToDisplay.size()));
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

    loadUsersTable();
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

void appwindow::on_export_pdf_user_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Export User Data to PDF"), "",
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

    int titleBlockHeight = 120;
    painter.fillRect(marginLeft, yPos, contentWidth, titleBlockHeight, darkBlue);

    QFont titleFont("Arial", 32, QFont::Bold);
    painter.setFont(titleFont);
    painter.setPen(Qt::white);
    painter.drawText(marginLeft, yPos, contentWidth, titleBlockHeight,
                     Qt::AlignCenter | Qt::AlignVCenter, "USER DATA REPORT");

    yPos += titleBlockHeight + 30;

    QFont dateFont("Arial", 11);
    painter.setFont(dateFont);
    painter.setPen(QColor(100, 100, 100));
    painter.drawText(marginLeft, yPos,
                     QString("Generated: %1")
                         .arg(QDateTime::currentDateTime()
                                  .toString("yyyy-MM-dd  hh:mm:ss")));
    yPos += 50;

    QTableWidget *table = ui->usersTable;
    int rowCount    = table->rowCount();
    int columnCount = table->columnCount();

    if (rowCount == 0 || columnCount == 0) {
        painter.setFont(QFont("Arial", 14));
        painter.setPen(textColor);
        painter.drawText(marginLeft, yPos, "No data to export.");
        painter.end();
        QMessageBox::information(this, "No Data", "The user table is empty. Nothing to export.");
        return;
    }

    int columnWidth  = contentWidth / columnCount;
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

void appwindow::loadUserStatistics(bool byRole)
{
    while (QLayoutItem *item = ui->statsiticslayout->takeAt(0)) {
        if (item->widget()) {
            item->widget()->deleteLater();
        }
        delete item;
    }

    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Users Count");
    QStringList categories;

    QSqlQuery query;
    const QString sql = byRole
                            ? "SELECT ROLE, COUNT(*) FROM USERS GROUP BY ROLE ORDER BY ROLE"
                            : "SELECT GENDER, COUNT(*) FROM USERS GROUP BY GENDER ORDER BY GENDER";

    if (!query.exec(sql)) {
        QLabel *errorLabel = new QLabel("Failed to load statistics data.");
        errorLabel->setAlignment(Qt::AlignCenter);
        ui->statsiticslayout->addWidget(errorLabel);
        return;
    }

    int maxCount = 0;
    while (query.next()) {
        const QString category = query.value(0).toString().trimmed().isEmpty()
        ? "Unknown"
        : query.value(0).toString().trimmed();
        const int count = query.value(1).toInt();

        *set << count;
        categories << category;
        if (count > maxCount) {
            maxCount = count;
        }
    }

    if (categories.isEmpty()) {
        *set << 0;
        categories << "No Data";
    }

    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(byRole ? "Users Statistics by Role" : "Users Statistics by Gender");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->addAxis(axis, Qt::AlignBottom);
    series->attachAxis(axis);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, qMax(1, maxCount));
    axisY->setLabelFormat("%d");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->statsiticslayout->addWidget(chartView);
}

void appwindow::on_pushButton_8_clicked()
{
    const bool byRole = (ui->comboBox_12->currentIndex() == 0);
    loadUserStatistics(byRole);
}


//log out special feature:



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

    // Get boat ID from input field
    int boatId = -1;
    if (!ui->boatCombo->text().isEmpty()) {
        bool ok;
        boatId = ui->boatCombo->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Error", "Boat ID must be a valid number!");
            return;
        }
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
                                         ui->fishdate2->dateTime(),
                                         boatId)) {
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
                                          ui->fishdate2->dateTime(),
                                          boatId)) {
            QMessageBox::critical(this, "Error", "Failed to add product. Please check the database connection.");
            return;
        }
        QMessageBox::information(this, "Success", "Product added successfully!");
    }

    // Clear form
    ui->fishtype->clear();
    ui->fishStatus->setCurrentIndex(0);
    ui->qtyfish->clear();
    ui->fishprice->clear();
    ui->fishdate1->setDateTime(QDateTime::currentDateTime());
    ui->fishdate2->setDateTime(QDateTime::currentDateTime());
    ui->locationfish->clear();
    ui->boatCombo->clear();
    selectedProductId = -1;

    // Reset button text back to "Add Product"
    ui->checkProductButton_2->setText("Add Product");

    // Refresh the table on manage page
    loadProductTable();
}
void appwindow::on_pushButton_11_clicked()
{
    // Get all products
    QList<ProductRecord> allProducts = productManager.getAllProducts();

    if (allProducts.isEmpty()) {
        QMessageBox::warning(this, "No Data", "No products in the system to analyze.");
        return;
    }

    // Determine which statistics to show
    int selectedOption = ui->comboBox_17->currentIndex();

    if (selectedOption == 0) {
        // Show statistics by Status (pie chart)
        generateProductStatisticsByStatus(allProducts);
    } else {
        // Show quantity distribution by fish type (pie chart)
        generateProductQuantityByType(allProducts);
    }
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
    table->setColumnCount(9);
    table->setHorizontalHeaderLabels(
        {"ID", "Status", "Type", "Fish Caught", "Date Purchase", "Quantity", "Location", "Original Price", "Discounted Price"});
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::ExtendedSelection);
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
        table->setItem(row, 7, new QTableWidgetItem(QString::number(r.originalPrice, 'f', 2)));
        table->setItem(row, 8, new QTableWidgetItem(QString::number(r.discountedPrice, 'f', 2)));
    }

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Update the count label
    ui->labelResults_6->setText(QString("Showing %1 Products").arg(records.size()));

    // Keep Discounts page alerts synced with current product quantities.
    refreshLowStockAlerts(false);
}



void appwindow::on_Manage_24_clicked()
{
    loadProductTable();
}

void appwindow::refreshLowStockAlerts(bool showPopup)
{
    const QList<ProductRecord> products = productManager.getAllProducts();
    QStringList lowStockLines;

    auto resizeAlertArea = [&](int lineCount) {
        const int visibleLines = qMax(2, lineCount);
        const int contentHeight = 24 + (visibleLines * 24);
        const int dockHeight = contentHeight + 55;

        ui->dockWidget_2->setMinimumHeight(dockHeight);
        ui->dockWidget_2->resize(ui->dockWidget_2->width(), dockHeight);

        const int labelWidth = qMax(200, ui->dockWidgetContents_2->width() - 20);
        ui->label_3->setGeometry(10, 16, labelWidth, contentHeight);
        ui->label_3->setWordWrap(true);
        ui->label_3->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    };

    for (const ProductRecord &product : products) {
        if (product.quantity < 30) {
            lowStockLines << QString("- %1 (ID %2): %3 left")
                                 .arg(product.type)
                                 .arg(product.id)
                                 .arg(product.quantity);
        }
    }

    if (lowStockLines.isEmpty()) {
        resizeAlertArea(2);
        ui->dockWidget_2->setWindowTitle("Stock level looks good");
        ui->label_3->setText(QString("No low-stock products.\nTotal products: %1").arg(products.size()));
        ui->label_3->setStyleSheet("color: #14532d; font-weight: 600;");
        return;
    }

    resizeAlertArea(lowStockLines.size() + 1);
    ui->dockWidget_2->setWindowTitle(QString("Low-stock alert: %1 product(s) below 30").arg(lowStockLines.size()));
    ui->label_3->setText(lowStockLines.join("\n"));
    ui->label_3->setStyleSheet("color: #b91c1c; font-weight: 700;");

    if (showPopup && !lowStockWarningShown) {
        QMessageBox::warning(this,
                             "Low Stock Alert",
                             QString("At least one product is below quantity 30.\n\n%1")
                                 .arg(lowStockLines.join("\n")));
        lowStockWarningShown = true;
    }
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
            ui->boatCombo->clear();
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
    ui->boatCombo->clear();
    ui->fishdate1->setDateTime(QDateTime::currentDateTime());
    ui->fishdate2->setDateTime(QDateTime::currentDateTime());
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
        table->setItem(row, 7, new QTableWidgetItem(QString::number(r.originalPrice, 'f', 2)));
        table->setItem(row, 8, new QTableWidgetItem(QString::number(r.discountedPrice, 'f', 2)));
    }

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Update the count label
    ui->labelResults_6->setText(QString("Showing %1 Products").arg(recordsToDisplay.size()));
}

void appwindow::on_export_pdf_6_clicked()
{
    QTableWidget *table = ui->tableWidget_10;
    QList<int> selectedRows;

    if (table->selectionModel()) {
        const QModelIndexList selectedIndexes = table->selectionModel()->selectedRows();
        for (const QModelIndex &index : selectedIndexes) {
            selectedRows.append(index.row());
        }
    }

    std::sort(selectedRows.begin(), selectedRows.end());

    if (selectedRows.isEmpty()) {
        QMessageBox::information(this,
                                 "Select Products",
                                 "Please select one or more products from the table before exporting to PDF.");
        return;
    }

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
                     Qt::AlignCenter | Qt::AlignVCenter, "PRODUCTS SOLD");

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
    int rowCount    = selectedRows.size();
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

    int rowHeight       = 75;
    int footerReserve   = 260; // Keep space for summary and signature area at the bottom.

    QFont cellFont("Arial", 11);
    painter.setFont(cellFont);

    for (int exportRow = 0; exportRow < rowCount; exportRow++) {
        const int row = selectedRows.at(exportRow);

        // ── New page if needed ──
        if (exportRow > 0 && (yPos + rowHeight + footerReserve) > pageHeight) {
            pdfWriter.newPage();
            yPos = marginTop;
            drawHeader();
            yPos += headerHeight;
            painter.setFont(cellFont);
        }

        QColor rowBg = (exportRow % 2 == 0) ? Qt::white : veryLightBlue;
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
    const int summaryBlockHeight = 90;
    const int signatureBlockHeight = 420;
    const int gapBeforeSignature = 190;
    const int neededBottomSpace = 40 + summaryBlockHeight + gapBeforeSignature + signatureBlockHeight;

    if (yPos + neededBottomSpace > pageHeight) {
        pdfWriter.newPage();
        yPos = marginTop;
    }

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

    yPos += gapBeforeSignature;

    const int signatureWidth = (contentWidth * 7) / 10;
    const int signatureHeight = 420;
    const int signatureX = marginLeft + (contentWidth - signatureWidth) / 2;
    int signatureY = yPos;

    // Keep signature area intentionally low on the page.
    const int lowAnchorY = pageHeight - signatureHeight - 60;
    if (signatureY < lowAnchorY) {
        signatureY = lowAnchorY;
    }

    painter.setPen(QPen(QColor(190, 190, 190), 1));
    painter.setBrush(Qt::NoBrush);
    painter.drawRoundedRect(signatureX, signatureY,
                            signatureWidth, signatureHeight,
                            8, 8);

    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.setPen(QColor(90, 90, 90));
    painter.drawText(signatureX, signatureY + 24,
                     signatureWidth, 42,
                     Qt::AlignHCenter | Qt::AlignVCenter,
                     "AUTHORIZED SIGNATURE");

    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.setPen(QColor(95, 95, 95));
    painter.drawText(signatureX, signatureY + 102,
                     signatureWidth, 36,
                     Qt::AlignHCenter | Qt::AlignVCenter,
                     "Sign here");

    painter.setPen(QPen(QColor(70, 70, 70), 2));
    const int signatureLineY = signatureY + 280;
    painter.drawLine(signatureX + 100, signatureLineY, signatureX + signatureWidth - 100, signatureLineY);

    const QString reportDate = QDate::currentDate().toString("yyyy-MM-dd");
    painter.setFont(QFont("Arial", 11));
    const int detailsY = signatureLineY + 46;
    const int detailsLeft = signatureX + 40;
    const int detailsWidth = signatureWidth - 80;
    const int columnGap = 30;
    const int detailsColumnWidth = (detailsWidth - (2 * columnGap)) / 3;

    const int dateX = detailsLeft;
    const int nameX = dateX + detailsColumnWidth + columnGap;
    const int idX = nameX + detailsColumnWidth + columnGap;

    painter.drawText(dateX, detailsY,
                     detailsColumnWidth, 30,
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QString("Date: %1").arg(reportDate));

    painter.drawText(nameX, detailsY,
                     detailsColumnWidth, 30,
                     Qt::AlignLeft | Qt::AlignVCenter,
                     "Name: ____________");

    painter.drawText(idX, detailsY,
                     detailsColumnWidth, 30,
                     Qt::AlignLeft | Qt::AlignVCenter,
                     "ID/Stamp: ____________");

    painter.end();

    QMessageBox::information(this, "Export Successful",
                             QString("PDF exported successfully to:\n%1").arg(fileName));
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

    if (statusCount.isEmpty()) {
        QMessageBox::warning(this, "No Data", "No product status data available.");
        return;
    }

    // Calculate percentage of active/available products
    int activeQuantity = statusQuantity.value("Available", 0) +
                         statusQuantity.value("In Stock", 0);
    int percentage = (totalQuantity > 0) ? (activeQuantity * 100) / totalQuantity : 0;

    // Update progress bar
    ui->progressBar_6->setValue(percentage);

    // Build pie chart by product status for Product Activity page
    QPieSeries *series = new QPieSeries();
    QList<QColor> sliceColors = {
        QColor("#0ea5e9"),
        QColor("#22c55e"),
        QColor("#f59e0b"),
        QColor("#ef4444"),
        QColor("#6366f1"),
        QColor("#14b8a6")
    };

    int colorIndex = 0;
    for (auto it = statusCount.begin(); it != statusCount.end(); ++it) {
        QPieSlice *slice = series->append(it.key(), it.value());
        slice->setLabelVisible(true);
        const int pct = (it.value() * 100) / qMax(1, products.size());
        slice->setLabel(QString("%1 (%2, %3%)").arg(it.key()).arg(it.value()).arg(pct));
        slice->setColor(sliceColors.at(colorIndex % sliceColors.size()));
        colorIndex++;
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Products Distribution by Status");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    ui->chartView_5->setChart(chart);
    ui->chartView_5->setRenderHint(QPainter::Antialiasing);

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

    ui->label_78->setText(QString("Percentage of active Product in system: %1%").arg(percentage));

    QMessageBox::information(this, "Product Statistics", statsText);
}

void appwindow::generateProductQuantityByType(const QList<ProductRecord> &products)
{
    QMap<QString, int> quantityByType;
    int totalQuantity = 0;

    for (const ProductRecord &product : products) {
        const QString fishType = product.type.trimmed().isEmpty() ? "Unknown" : product.type.trimmed();
        quantityByType[fishType] += product.quantity;
        totalQuantity += product.quantity;
    }

    if (quantityByType.isEmpty() || totalQuantity <= 0) {
        QMessageBox::warning(this, "No Data", "No quantity data available for fish types.");
        return;
    }

    QPieSeries *series = new QPieSeries();
    QList<QColor> sliceColors = {
        QColor("#0ea5e9"),
        QColor("#22c55e"),
        QColor("#f59e0b"),
        QColor("#ef4444"),
        QColor("#6366f1"),
        QColor("#14b8a6")
    };

    int colorIndex = 0;
    for (auto it = quantityByType.begin(); it != quantityByType.end(); ++it) {
        QPieSlice *slice = series->append(it.key(), it.value());
        slice->setLabelVisible(true);
        const int pct = (it.value() * 100) / qMax(1, totalQuantity);
        slice->setLabel(QString("%1 (%2 units, %3%)").arg(it.key()).arg(it.value()).arg(pct));
        slice->setColor(sliceColors.at(colorIndex % sliceColors.size()));
        colorIndex++;
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Quantity Distribution by Fish Type");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    ui->chartView_5->setChart(chart);
    ui->chartView_5->setRenderHint(QPainter::Antialiasing);

    const int maxTypeQty = *std::max_element(quantityByType.begin(), quantityByType.end());
    const int dominantPct = (maxTypeQty * 100) / qMax(1, totalQuantity);
    ui->progressBar_6->setValue(dominantPct);
    ui->label_78->setText(QString("Quantity share of top fish type: %1%").arg(dominantPct));
}

void appwindow::generateDockingStatistics()
{
    // Delete old scene if exists
    QGraphicsScene *oldScene = ui->graph_docking->scene();
    if (oldScene) {
        delete oldScene;
    }

    // Create new scene
    QGraphicsScene *scene = new QGraphicsScene();

    // Get all docking records
    QList<DockingRecord> dockings = dockingManager.getAllDockings();

    if (dockings.isEmpty()) {
        QGraphicsTextItem *textItem = scene->addText("No docking data available");
        textItem->setPos(ui->graph_docking->width() / 2 - 100, ui->graph_docking->height() / 2 - 20);
        ui->graph_docking->setScene(scene);
        return;
    }

    // Get available dimensions
    int viewWidth = ui->graph_docking->width();
    int viewHeight = ui->graph_docking->height();
    int chartWidth = viewWidth / 2;

    // Chart 1: Total Count of Dockings
    QChart *chart1 = new QChart();
    chart1->setTitle("Total Dockings in Database");
    chart1->setBackgroundBrush(QBrush(Qt::white));
    chart1->setAnimationOptions(QChart::SeriesAnimations);
    chart1->setMargins(QMargins(10, 10, 10, 10));

    QPieSeries *pieSeries1 = new QPieSeries();
    QPieSlice *slice1 = pieSeries1->append("Total Dockings", dockings.count());
    slice1->setColor(QColor(173, 216, 230));  // Light blue
    slice1->setLabelVisible(true);
    slice1->setLabel(QString("Total: %1").arg(dockings.count()));

    chart1->addSeries(pieSeries1);
    chart1->legend()->setVisible(true);
    chart1->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView1 = new QChartView(chart1);
    chartView1->setRenderHint(QPainter::Antialiasing);
    chartView1->setStyleSheet("background-color: white;");
    chartView1->setFixedSize(chartWidth, viewHeight);

    // Chart 2: Status breakdown (Occupied vs Available)
    QChart *chart2 = new QChart();
    chart2->setTitle("Dockings by Status");
    chart2->setBackgroundBrush(QBrush(Qt::white));
    chart2->setAnimationOptions(QChart::SeriesAnimations);
    chart2->setMargins(QMargins(10, 10, 10, 10));

    QBarSeries *barSeries = new QBarSeries();
    QBarSet *statusSet = new QBarSet("Count");
    QStringList statusCategories;

    int occupied = 0, available = 0;
    for (const DockingRecord &dock : dockings) {
        if (dock.status == "Occupied") {
            occupied++;
        } else if (dock.status == "Available") {
            available++;
        }
    }

    *statusSet << occupied << available;
    statusCategories << "Occupied" << "Available";
    barSeries->append(statusSet);
    statusSet->setColor(QColor(0, 102, 204));  // Dark blue

    chart2->addSeries(barSeries);
    chart2->setTitle("Dockings by Status");

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(statusCategories);
    chart2->addAxis(axisX, Qt::AlignBottom);
    barSeries->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    int maxValue = qMax(occupied, available);
    axisY->setRange(0, maxValue > 0 ? maxValue + 1 : 5);
    axisY->setLabelFormat("%d");
    axisY->setTickCount(maxValue + 2);
    chart2->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisY);

    QChartView *chartView2 = new QChartView(chart2);
    chartView2->setRenderHint(QPainter::Antialiasing);
    chartView2->setStyleSheet("background-color: white;");
    chartView2->setFixedSize(chartWidth, viewHeight);

    // Create a layout to display both charts
    QWidget *chartWidget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(chartWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(chartView1, 1);
    layout->addWidget(chartView2, 1);
    chartWidget->setFixedSize(viewWidth, viewHeight);

    // Add widget to scene and set proper bounds
    QGraphicsProxyWidget *proxy = scene->addWidget(chartWidget);
    scene->setSceneRect(0, 0, viewWidth, viewHeight);
    proxy->setGeometry(QRectF(0, 0, viewWidth, viewHeight));
    
    ui->graph_docking->setScene(scene);
    ui->graph_docking->setAlignment(Qt::AlignTop | Qt::AlignLeft);
}

void appwindow::on_DockCalender_clicked()
{
    QList<DockingRecord> dockings = dockingManager.getAllDockings();

    QDialog dialog(this);
    dialog.setWindowTitle("Dock Calendar");
    dialog.setMinimumSize(980, 720);

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
    mainLayout->setContentsMargins(24, 24, 24, 24);
    mainLayout->setSpacing(16);

    QLabel *titleLabel = new QLabel("Dock Reservation Calendar", &dialog);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet(
        "font-family: 'Behove';"
        "font-size: 24px;"
        "font-weight: bold;"
        "color: #0a4c73;"
    );
    mainLayout->addWidget(titleLabel);

    QLabel *subtitleLabel = new QLabel(
        "Red = Occupied reservation, Green = Available reservation",
        &dialog);
    subtitleLabel->setAlignment(Qt::AlignCenter);
    subtitleLabel->setStyleSheet("color: #334155; font-size: 14px;");
    mainLayout->addWidget(subtitleLabel);

    QHBoxLayout *legendLayout = new QHBoxLayout();
    legendLayout->setSpacing(18);

    auto addLegendItem = [legendLayout, &dialog](const QString &labelText, const QColor &color) {
        QWidget *itemWidget = new QWidget(&dialog);
        QHBoxLayout *itemLayout = new QHBoxLayout(itemWidget);
        itemLayout->setContentsMargins(0, 0, 0, 0);
        itemLayout->setSpacing(8);

        QLabel *swatch = new QLabel(itemWidget);
        swatch->setFixedSize(18, 18);
        swatch->setStyleSheet(QString("background-color: %1; border: 1px solid #64748b; border-radius: 4px;")
                                  .arg(color.name()));

        QLabel *text = new QLabel(labelText, itemWidget);
        text->setStyleSheet("color: #334155; font-size: 13px;");

        itemLayout->addWidget(swatch);
        itemLayout->addWidget(text);
        itemLayout->addStretch();
        legendLayout->addWidget(itemWidget);
    };

    addLegendItem("Occupied", QColor("#f87171"));
    addLegendItem("Available", QColor("#4ade80"));
    legendLayout->addStretch();
    mainLayout->addLayout(legendLayout);

    DockCalendarWidget *calendar = new DockCalendarWidget(&dialog);
    calendar->setGridVisible(true);
    calendar->setNavigationBarVisible(true);
    calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    calendar->setFirstDayOfWeek(Qt::Monday);
    calendar->setSelectedDate(QDate::currentDate());
    calendar->setStyleSheet(
        "QCalendarWidget QWidget { background: white; }"
        "QCalendarWidget QToolButton { height: 34px; font-size: 14px; font-weight: bold; color: #0a4c73; }"
        "QCalendarWidget QAbstractItemView:enabled { selection-background-color: #0ea5e9; selection-color: white; }"
    );

    QMap<QDate, int> priorities;
    QMap<QDate, QColor> dateColors;

    for (const DockingRecord &dock : dockings) {
        QDate startDate = parseDockingDate(dock.startDate);
        QDate endDate = parseDockingDate(dock.endDate);
        QColor color = statusColor(dock.status);

        if (!startDate.isValid() || !endDate.isValid() || !color.isValid() || endDate < startDate) {
            continue;
        }

        const int priority = statusPriority(dock.status);
        for (QDate current = startDate; current <= endDate; current = current.addDays(1)) {
            if (priority > priorities.value(current, 0)) {
                priorities[current] = priority;
                dateColors[current] = color;
            }
        }
    }

    for (auto it = dateColors.cbegin(); it != dateColors.cend(); ++it) {
        QTextCharFormat format;
        format.setBackground(QBrush(it.value()));
        format.setForeground(QBrush(Qt::black));
        calendar->setDateTextFormat(it.key(), format);
    }

    calendar->setDockColors(dateColors);

    if (dateColors.isEmpty()) {
        QLabel *emptyLabel = new QLabel("No dock reservations were found.", &dialog);
        emptyLabel->setAlignment(Qt::AlignCenter);
        emptyLabel->setStyleSheet("color: #475569; font-size: 14px;");
        mainLayout->addWidget(emptyLabel);
    }

    mainLayout->addWidget(calendar, 1);

    dialog.exec();
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

    // ── DATE PARSING ──────────────────────────────────────────
    QString rawDate = boatsTmp.getLastMaintenanceDate();
    QDate date;

    // Oracle returns month in all-caps (e.g. "23/MAR/17") — normalize to "23/Mar/17"
    QStringList parts = rawDate.split('/');
    QString normalizedDate = rawDate;
    if (parts.size() == 3) {
        QString month = parts[1];
        month = month[0].toUpper() + month.mid(1).toLower();
        normalizedDate = parts[0] + "/" + month + "/" + parts[2];
    }

    for (const QString &fmt : {"dd/MMM/yy", "dd/MMM/yyyy", "yyyy-MM-dd", "dd-MMM-yyyy"}) {
        date = QDate::fromString(normalizedDate, fmt);
        if (date.isValid()) break;
    }

    if (date.isValid()) {
        // Fix two-digit year: Qt may interpret "17" as 1917 instead of 2017
        if (date.year() < 2000) {
            date = date.addYears(100);
        }
        ui->boatMaintenanceDateEdit->setDate(date);
    } else {
        qDebug() << "Could not parse date:" << rawDate;
        ui->boatMaintenanceDateEdit->setDate(QDate::currentDate());
    }
    // ── END DATE PARSING ──────────────────────────────────────

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


void appwindow::on_Boatwidget_2_itemSelectionChanged()
{
    int currentRow = ui->Boatwidget_2->currentRow();
    if (currentRow < 0) {
        currentlySelectedId = -1;
        ui->deleteBoatButton->setEnabled(false);
        ui->updateBoatButton->setEnabled(false);
        return;
    }

    QTableWidgetItem *idItem = ui->Boatwidget_2->item(currentRow, 0);
    if (idItem) {
        currentlySelectedId = idItem->data(Qt::UserRole).toInt();
        qDebug() << "Selected boat ID:" << currentlySelectedId;
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

    updateBoatStatusProgressBar();
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


    updateBoatStatusProgressBar();
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



    updateBoatStatusProgressBar();
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
    QString searchText = ui->boatSearchLineEdit->text().trimmed();

    if (searchText.isEmpty()) {
        displayBoats();
        return;
    }

    ui->Boatwidget_2->blockSignals(true);
    ui->Boatwidget_2->setRowCount(0);

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "DB Error", "Database is not open!");
        ui->Boatwidget_2->blockSignals(false);
        return;
    }

    QSqlQuery query(db);
    query.prepare(
        "SELECT BOATID, SIZEBOAT, LOCATION, OWNERNAME, OWNERMAIL, "
        "STATUS, TYPE, LASTMAINTENANCEDATE, TOTALTRIPS, TOTALFISH "
        "FROM BOAT "
        "WHERE CAST(BOATID AS VARCHAR2(20)) LIKE :search "
        "OR UPPER(OWNERNAME) LIKE UPPER(:search2) "
        "ORDER BY BOATID"
        );
    query.bindValue(":search",  "%" + searchText + "%");
    query.bindValue(":search2", "%" + searchText + "%");

    if (!query.exec()) {
        QMessageBox::critical(this, "Search Error", query.lastError().text());
        ui->Boatwidget_2->blockSignals(false);
        return;
    }

    int row = 0;
    while (query.next()) {
        ui->Boatwidget_2->insertRow(row);

        for (int col = 0; col < 10; col++) {
            QTableWidgetItem *item;
            if (col == 5) {
                QString statusText = query.value(col).toInt() == 1 ? "IN PORT" : "OUT";
                item = new QTableWidgetItem(statusText);
            } else {
                item = new QTableWidgetItem(query.value(col).toString());
            }
            if (col == 0)
                item->setData(Qt::UserRole, query.value("BOATID").toInt());
            ui->Boatwidget_2->setItem(row, col, item);
        }
        row++;
    }

    ui->Boatwidget_2->blockSignals(false);

    if (row == 0) {
        QMessageBox::information(this, "Not Found",
                                 "No boat found matching: " + searchText);
        displayBoats();
    }
}

void appwindow::on_pushButton_10_clicked()
{
    qDebug() << "=== PushButton_10 clicked ===";
    qDebug() << "ComboBox current index:" << ui->comboBox_16->currentIndex();

    // Get all boats
    QSqlQuery allBoats = Boats::getAll();

    if (!allBoats.isActive()) {
        qDebug() << "Query failed:" << allBoats.lastError().text();
        QMessageBox::warning(this, "Error", "Failed to retrieve boat data from database.");
        return;
    }

    qDebug() << "Query active, checking for boats...";

    int rowCount = 0;
    while (allBoats.next()) {
        rowCount++;
        qDebug() << "Boat ID:" << allBoats.value(0).toInt();
    }

    qDebug() << "Total boats found:" << rowCount;

    if (rowCount == 0) {
        QMessageBox::warning(this, "No Data", "No boats found in the system to analyze.");
        return;
    }

    // Reset the query to get data again
    allBoats = Boats::getAll();

    // Determine which chart to show based on comboBox selection
    int selectedOption = ui->comboBox_16->currentIndex();
    qDebug() << "Selected option:" << selectedOption << "(0=Fish, 1=Trips)";

    // Prepare data containers
    QStringList boatLabels;
    QList<int> values;

    // Collect data based on selection
    if (selectedOption == 0) {
        // Show Total Fish by Boat
        while (allBoats.next()) {
            int boatId = allBoats.value(0).toInt();
            int totalFish = allBoats.value(9).toInt(); // TOTALFISH is column 9

            // Create a label for each boat
            QString boatLabel = QString("Boat %1").arg(boatId);

            boatLabels.append(boatLabel);
            values.append(totalFish);

            qDebug() << "Boat" << boatId << "Fish:" << totalFish;
        }

        // Check if there's data
        if (boatLabels.isEmpty()) {
            QMessageBox::warning(this, "No Data", "No boat data available.");
            return;
        }

        qDebug() << "Creating Fish chart with" << boatLabels.size() << "boats";
        // Create the chart
        createBoatChart(boatLabels, values, "Total Fish Captured by Boat", "Fish Count");

    } else if (selectedOption == 1) {
        // Show Total Trips by Boat
        while (allBoats.next()) {
            int boatId = allBoats.value(0).toInt();
            int totalTrips = allBoats.value(8).toInt(); // TOTALTRIPS is column 8

            QString boatLabel = QString("Boat %1").arg(boatId);

            boatLabels.append(boatLabel);
            values.append(totalTrips);

            qDebug() << "Boat" << boatId << "Trips:" << totalTrips;
        }

        // Check if there's data
        if (boatLabels.isEmpty()) {
            QMessageBox::warning(this, "No Data", "No boat data available.");
            return;
        }

        qDebug() << "Creating Trips chart with" << boatLabels.size() << "boats";
        // Create the chart
        createBoatChart(boatLabels, values, "Total Trips by Boat", "Number of Trips");
    }
}

void appwindow::createBoatChart(const QStringList &categories, const QList<int> &values,
                                const QString &title, const QString &yAxisLabel)
{
    qDebug() << "Creating chart with" << categories.size() << "categories";

    // Clear any existing chart
    if (ui->chartView_4->chart()) {
        ui->chartView_4->chart()->deleteLater();
    }

    // Create bar series
    QBarSeries *series = new QBarSeries();
    QBarSet *barSet = new QBarSet(yAxisLabel);

    // Add all values to the bar set
    for (int value : values) {
        *barSet << value;
        qDebug() << "Adding value:" << value;
    }

    series->append(barSet);

    // Create chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(title);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Create category axis for X-axis
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("Boats");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Create value axis for Y-axis
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText(yAxisLabel);

    // Find max value for proper scaling
    int maxValue = 0;
    for (int value : values) {
        if (value > maxValue) maxValue = value;
    }

    // Add some padding to the top
    double maxRange = maxValue > 0 ? maxValue + (maxValue * 0.2) : 10;
    axisY->setRange(0, maxRange);
    axisY->setLabelFormat("%d");
    axisY->setTickCount(6);

    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Enable legend
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Set the chart to the chartView_4
    ui->chartView_4->setChart(chart);
    ui->chartView_4->setRenderHint(QPainter::Antialiasing);

    // Force an update
    ui->chartView_4->update();
    ui->chartView_4->repaint();

    qDebug() << "Chart created successfully";
}



////EMAILS BOATS
// Add this function to check and send maintenance reminders
void appwindow::checkAndSendMaintenanceReminders()
{
    qDebug() << "Checking for boats due for maintenance...";

    QSqlQuery allBoats = Boats::getAll();

    if (!allBoats.isActive()) {
        qDebug() << "Failed to retrieve boats for maintenance check";
        return;
    }

    QDate today = QDate::currentDate();
    int remindersSent = 0;
    int errorsEncountered = 0;

    while (allBoats.next()) {
        int boatId = allBoats.value(0).toInt();
        QString size = allBoats.value(1).toString();
        QString location = allBoats.value(2).toString();
        QString ownerName = allBoats.value(3).toString();
        QString ownerEmail = allBoats.value(4).toString();
        int status = allBoats.value(5).toInt();
        QString boatType = allBoats.value(6).toString();
        QString lastMaintenanceDateStr = allBoats.value(7).toString();

        // Skip boats without email or invalid email
        if (ownerEmail.isEmpty() || !isEmailValid(ownerEmail)) {
            qDebug() << "Skipping boat" << boatId << "- Invalid or missing email:" << ownerEmail;
            continue;
        }

        // Parse the last maintenance date
        QDate lastMaintenanceDate = QDate::fromString(lastMaintenanceDateStr, "yyyy-MM-dd");
        if (!lastMaintenanceDate.isValid()) {
            // Try alternative date formats
            lastMaintenanceDate = QDate::fromString(lastMaintenanceDateStr, "dd-MMM-yyyy");
            if (!lastMaintenanceDate.isValid()) {
                lastMaintenanceDate = QDate::fromString(lastMaintenanceDateStr, "MM/dd/yy");
            }
        }

        if (!lastMaintenanceDate.isValid()) {
            qDebug() << "Skipping boat" << boatId << "- Invalid maintenance date:" << lastMaintenanceDateStr;
            continue;
        }

        // Calculate days since last maintenance
        int daysSinceMaintenance = lastMaintenanceDate.daysTo(today);
        int weeksSinceMaintenance = daysSinceMaintenance / 7;

        // Check if maintenance is overdue (more than 365 days / 52 weeks)
        if (daysSinceMaintenance >= 365) {
            int weeksOverdue = (daysSinceMaintenance - 365) / 7;

            // Send reminder for first overdue or weekly thereafter
            if (weeksOverdue == 0 || weeksOverdue % 1 == 0) { // Weekly reminders
                qDebug() << "Boat" << boatId << "is overdue by" << weeksOverdue << "weeks";
                sendMaintenanceReminderEmail(ownerEmail, ownerName, QString::number(boatId),
                                             boatType, lastMaintenanceDate, weeksOverdue);
                remindersSent++;
            }
        } else {
            // Calculate days until maintenance is due
            int daysUntilDue = 365 - daysSinceMaintenance;
            qDebug() << "Boat" << boatId << "maintenance due in" << daysUntilDue << "days";
        }
    }

    qDebug() << "Maintenance check complete. Sent" << remindersSent << "reminders. Errors:" << errorsEncountered;


}

//status boat
void appwindow::updateBoatStatusProgressBar()
{
    // Get all boats
    QSqlQuery allBoats = Boats::getAll();

    if (!allBoats.isActive()) {
        qDebug() << "Failed to retrieve boats for progress bar";
        return;
    }

    int totalBoats = 0;
    int boatsInPort = 0;

    // Count boats
    while (allBoats.next()) {
        totalBoats++;
        int status = allBoats.value(5).toInt(); // STATUS is column 5 (0=OUT, 1=IN PORT)
        if (status == 1) {
            boatsInPort++;
        }
    }

    if (totalBoats == 0) {
        ui->progressBar_5->setValue(0);
        ui->label_77->setText("Percentage of active boats: 0% (No boats in system)");
        return;
    }

    // Calculate percentage of boats IN PORT
    int percentageInPort = (boatsInPort * 100) / totalBoats;

    // Update progress bar
    ui->progressBar_5->setValue(percentageInPort);

    // Update label with detailed information
    QString statusText = QString("Boats IN PORT: %1% (%2 of %3 boats)")
                             .arg(percentageInPort)
                             .arg(boatsInPort)
                             .arg(totalBoats);
    ui->label_77->setText(statusText);

    qDebug() << "Boat status update - Total:" << totalBoats
             << "In Port:" << boatsInPort
             << "Percentage:" << percentageInPort << "%";
}


// Send maintenance reminder email
void appwindow::sendMaintenanceReminderEmail(const QString &ownerEmail, const QString &ownerName,
                                             const QString &boatId, const QString &boatType,
                                             const QDate &lastMaintenanceDate, int weeksOverdue)
{
    // Prepare subject
    QString subject;
    if (weeksOverdue == 0) {
        subject = "URGENT: Boat Maintenance Overdue - Hawata Marina";
    } else {
        subject = QString("MAINTENANCE REMINDER - %1 Week%2 Overdue - Hawata Marina")
        .arg(weeksOverdue)
            .arg(weeksOverdue > 1 ? "s" : "");
    }

    // Prepare body
    QString body;
    if (weeksOverdue == 0) {
        body = QString(
                   "Dear %1,\n\n"
                   "This is an important reminder that your boat (ID: %2, Type: %3) is now OVERDUE for maintenance.\n\n"
                   "Last Maintenance Date: %4\n"
                   "Current Status: OVERDUE BY 1 YEAR\n\n"
                   "Regular maintenance is crucial for:\n"
                   "✓ Ensuring safety of your vessel and crew\n"
                   "✓ Preventing costly repairs in the future\n"
                   "✓ Maintaining optimal performance\n"
                   "✓ Compliance with marina regulations\n\n"
                   "Please contact our maintenance department immediately to schedule your appointment.\n\n"
                   "To schedule maintenance, please reply to this email or call us at +216 XX XXX XXX.\n\n"
                   "Thank you for your prompt attention to this matter.\n\n"
                   "Best regards,\n"
                   "Hawata Marina Maintenance Team"
                   ).arg(ownerName, boatId, boatType, lastMaintenanceDate.toString("MMMM dd, yyyy"));
    } else {
        body = QString(
                   "Dear %1,\n\n"
                   "This is a follow-up reminder that your boat (ID: %2, Type: %3) is now %4 week%5 overdue for maintenance.\n\n"
                   "Last Maintenance Date: %6\n"
                   "Overdue By: %4 week%5\n\n"
                   "Please schedule your maintenance appointment as soon as possible.\n\n"
                   "To schedule your maintenance, please contact us at:\n"
                   "📞 Phone: +216 XX XXX XXX\n"
                   "📧 Email: maintenance@hawatamarina.com\n\n"
                   "We look forward to serving you.\n\n"
                   "Best regards,\n"
                   "Hawata Marina Maintenance Team"
                   ).arg(ownerName, boatId, boatType)
                   .arg(weeksOverdue)
                   .arg(weeksOverdue > 1 ? "s" : "")
                   .arg(lastMaintenanceDate.toString("MMMM dd, yyyy"));
    }

    // Show confirmation (remove in production)
    QMessageBox::information(this, "Maintenance Reminder",
                             QString("Sending reminder to:\n%1\n\nSubject: %2").arg(ownerEmail, subject));

    // Create SMTP client
    SmtpClient *smtp = new SmtpClient("smtp.gmail.com", 465, this);
    smtp->setUsername("your-email@gmail.com");  // Replace with your email
    smtp->setPassword("your-app-password");     // Replace with app password

    connect(smtp, &SmtpClient::mailSent, [this, ownerEmail, subject](bool success, const QString &error) {
        if (success) {
            qDebug() << "Email sent successfully to:" << ownerEmail;
            QMessageBox::information(this, "Email Sent",
                                     QString("Maintenance reminder sent to:\n%1").arg(ownerEmail));
        } else {
            qDebug() << "Failed to send email to:" << ownerEmail << "Error:" << error;
            QMessageBox::warning(this, "Email Failed",
                                 QString("Failed to send to %1\nError: %2").arg(ownerEmail, error));
        }
        sender()->deleteLater();
    });

    smtp->sendMail("your-email@gmail.com", ownerEmail, subject, body);
}

// Validate email format
bool appwindow::isEmailValid(const QString &email)
{
    QRegularExpression emailRegex("^[\\w\\.]+@[\\w\\.]+\\.[a-zA-Z]{2,}$");
    return emailRegex.match(email).hasMatch();
}

// Get the next maintenance date (one year after last maintenance)
QDate appwindow::getNextMaintenanceDate(const QDate &lastMaintenanceDate)
{
    return lastMaintenanceDate.addYears(1);
}



// Slot to check maintenance reminders (called by timer)
void appwindow::onCheckMaintenanceReminders()
{
    checkAndSendMaintenanceReminders();
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

    if (!table->item(row, 0)) return; // safety

    selectedCompanyId = table->item(row, 0)->text().toInt();

    ui->firstNameEdit_8->setText(table->item(row, 1) ? table->item(row, 1)->text() : "");
    ui->lastNameEdit_7->setText(table->item(row, 2) ? table->item(row, 2)->text() : "");
    ui->emailEdit_4->setText(table->item(row, 3) ? table->item(row, 3)->text() : "");
    ui->passwordEdit_3->setText(table->item(row, 4) ? table->item(row, 4)->text() : "");
    ui->lastNameEdit_8->setText(table->item(row, 5) ? table->item(row, 5)->text() : "");

    QString statusText = table->item(row, 6) ? table->item(row, 6)->text() : "";
    int statusIdx = ui->role_option_7->findText(statusText);
    if (statusIdx >= 0)
        ui->role_option_7->setCurrentIndex(statusIdx);

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
    QString name          = ui->firstNameEdit_8->text().trimmed();
    QString location      = ui->lastNameEdit_7->text().trimmed();
    QString email         = ui->emailEdit_4->text().trimmed();
    QString phone         = ui->passwordEdit_3->text().trimmed();
    QString preferredFish = ui->lastNameEdit_8->text().trimmed();
    QString status        = ui->role_option_7->currentText().trimmed().toUpper();

    // ===== VALIDATION =====
    QRegularExpression nameRegex("^[A-Za-z\\s]{8,}$");
    if (!nameRegex.match(name).hasMatch()) {
        QMessageBox::warning(this, "Validation Error",
                             "Name must contain only letters and be at least 8 characters.");
        return;
    }

    if (preferredFish.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Preferred fish is required.");
        return;
    }

    QRegularExpression emailRegex("^[\\w\\.]+@[\\w\\.]+\\.[a-zA-Z]{2,}$");
    if (!emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Validation Error", "Invalid email format.");
        return;
    }

    QRegularExpression phoneRegex("^[0-9]{8}$");
    if (!phoneRegex.match(phone).hasMatch()) {
        QMessageBox::warning(this, "Validation Error",
                             "Phone number must contain exactly 8 digits.");
        return;
    }

    if (status != "ACTIVE" && status != "INACTIVE") {
        QMessageBox::warning(this, "Validation Error", "Status must be ACTIVE or INACTIVE.");
        return;
    }

    bool success = false;

    // ===== CREATE OR UPDATE =====
    if (selectedCompanyId == -1) {
        // CREATE
        success = companyManager.createCompany(
            name, location, email, phone, preferredFish, status);

        if (success) {
            QMessageBox::information(this, "Success", "Company created successfully.");
        }
    } else {
        // UPDATE
        success = companyManager.updateCompany(
            selectedCompanyId,
            name, location, email, phone, preferredFish, status);

        if (success) {
            QMessageBox::information(this, "Success", "Company updated successfully.");
        }
    }

    if (!success) {
        QMessageBox::critical(this, "Error", "Operation failed.");
        return;
    }

    // Refresh table
    loadCompaniesTable();

    // Clear form
    on_clear_7_clicked();
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
    if (id <= 0) {
        QMessageBox::warning(this, "Error", "Invalid company ID.");
        return;
    }
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
// search
void appwindow::on_searchbar_7_textChanged(const QString &text)
{
    for (int row = 0; row < ui->tableWidget_11->rowCount(); ++row) {
        bool match = false;

        for (int col = 0; col < ui->tableWidget_11->columnCount(); ++col) {
            QTableWidgetItem *item = ui->tableWidget_11->item(row, col);
            if (item && item->text().contains(text, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }

        ui->tableWidget_11->setRowHidden(row, !match);
    }
}

///CLEAR
void appwindow::on_clear_7_clicked()
{
    selectedCompanyId = -1;

    ui->firstNameEdit_8->clear();
    ui->lastNameEdit_7->clear();
    ui->emailEdit_4->clear();
    ui->passwordEdit_3->clear();
    ui->lastNameEdit_8->clear();
    ui->role_option_7->setCurrentIndex(0);

    ui->CreateUser_3->setText("Create Company");

    if (ui->tableWidget_11->selectionModel())
        ui->tableWidget_11->clearSelection();
}


void appwindow::on_export_pdf_7_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(
        this, "Export PDF", "", "PDF Files (*.pdf)");

    if (fileName.isEmpty())
        return;

    QTextDocument document;

    int total = ui->tableWidget_11->rowCount();

    QString html = R"(
    <html>
    <head>
    <style>
        body {
            font-family: Arial;
            margin: 0;
            padding: 0;
        }

        /* ===== HEADER ===== */
        .header {
            background: linear-gradient(to right, #003E7E, #005CBF);
            color: white;
            padding: 25px;
        }

        .header h1 {
            margin: 0;
            font-size: 26px;
        }

        .subtitle {
            font-size: 12px;
            opacity: 0.8;
        }

        /* ===== SECTION TITLE ===== */
        .section-title {
            margin-top: 30px;
            font-size: 18px;
            font-weight: bold;
            color: #003E7E;
            border-left: 6px solid #005CBF;
            padding-left: 10px;
        }

        /* ===== KPI CARD ===== */
        .card-container {
            margin-top: 15px;
        }

        .card {
            background-color: #F4F6F9;
            border-radius: 6px;
            padding: 15px;
            width: 250px;
            display: inline-block;
            margin-right: 15px;
            box-shadow: 2px 2px 8px rgba(0,0,0,0.1);
        }

        .card-title {
            font-size: 13px;
            color: #555;
        }

        .card-value {
            font-size: 26px;
            font-weight: bold;
            color: #003E7E;
        }

        /* ===== TABLE ===== */
        table {
            border-collapse: collapse;
            width: 100%;
            margin-top: 20px;
            font-size: 12px;
        }

        th {
            background-color: #003E7E;
            color: white;
            padding: 10px;
            text-align: left;
        }

        td {
            padding: 8px;
            border-bottom: 1px solid #ddd;
        }

        tr:nth-child(even) {
            background-color: #F4F6F9;
        }

        /* ===== FOOTER ===== */
        .footer {
            margin-top: 40px;
            font-size: 10px;
            color: #777;
            text-align: center;
            border-top: 1px solid #ccc;
            padding-top: 10px;
        }

    </style>
    </head>
    <body>
    )";

    // ===== HEADER =====
    html += "<div class='header'>";
    html += "<h1>COMPANY PERFORMANCE REPORT</h1>";
    html += "<div class='subtitle'>Marina Management System | Generated on "
            + QDate::currentDate().toString("dd MMM yyyy") + "</div>";
    html += "</div>";

    // ===== EXECUTIVE SUMMARY =====
    html += "<div class='section-title'>EXECUTIVE SUMMARY</div>";

    html += "<div class='card-container'>";
    html += "<div class='card'>";
    html += "<div class='card-title'>Total Companies</div>";
    html += "<div class='card-value'>" + QString::number(total) + "</div>";
    html += "</div>";
    html += "</div>";

    // ===== TABLE SECTION =====
    html += "<div class='section-title'>COMPANY REGISTRY</div>";

    html += "<table>";
    html += "<tr>"
            "<th>ID</th>"
            "<th>Name</th>"
            "<th>Location</th>"
            "<th>Email</th>"
            "<th>Phone</th>"
            "<th>Preferred Fish</th>"
            "<th>Status</th>"
            "</tr>";

    for (int row = 0; row < ui->tableWidget_11->rowCount(); ++row)
    {
        html += "<tr>";

        for (int col = 0; col < ui->tableWidget_11->columnCount(); ++col)
        {
            QString text = ui->tableWidget_11->item(row, col)->text();
            html += "<td>" + text + "</td>";
        }

        html += "</tr>";
    }

    html += "</table>";

    // ===== FOOTER =====
    html += "<div class='footer'>";
    html += "Marina Management System - Company Report - CONFIDENTIAL";
    html += "</div>";

    html += "</body></html>";

    document.setHtml(html);

    QPdfWriter writer(fileName);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setResolution(300);

    document.print(&writer);

    QMessageBox::information(this, "Success", "PDF exported successfully!");
}
void appwindow::loadCompaniesTableFromList(const QList<CompanyRecord> &records)
{
    QTableWidget *table = ui->tableWidget_11;
    table->setRowCount(0);

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

    ui->labelResults_7->setText(QString("Showing %1 Companies").arg(records.size()));
}
void appwindow::on_comboBox_19_currentTextChanged(const QString &arg1)
{
    QList<CompanyRecord> records;

    if (arg1 == "Name")
        records = companyManager.sortCompaniesBy("NAME");
    else if (arg1 == "Preferred Fish")
        records = companyManager.sortCompaniesBy("PREFERRED_FISH");
    else
        records = companyManager.getAllCompanies();

    loadCompaniesTableFromList(records);
}
void appwindow::on_pushButton_12_clicked()
{
    QString filterType = ui->comboBox_20->currentText();

    QMap<QString, int> stats;

    // Loop through tableWidget_11 (Companies table)
    for (int row = 0; row < ui->tableWidget_11->rowCount(); ++row)
    {
        QString key;

        if (filterType == "Status")
        {
            // Assuming Status column index = 6
            key = ui->tableWidget_11->item(row, 6)->text();
        }
        else if (filterType == "Preferred Fish")
        {
            // Assuming Preferred Fish column index = 5
            key = ui->tableWidget_11->item(row, 5)->text();
        }

        stats[key]++;
    }

    // ===== Create Bar Series =====
    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet(filterType);

    QStringList categories;

    for (auto it = stats.begin(); it != stats.end(); ++it)
    {
        *set << it.value();
        categories << it.key();
    }

    series->append(set);

    // ===== Create Chart =====
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Company Distribution by " + filterType);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Number of Companies");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);

    // ===== Display in chartView_6 =====
    ui->chartView_6->setChart(chart);
    ui->chartView_6->setRenderHint(QPainter::Antialiasing);
}

//boat new functionalities
void appwindow::on_clearBoatButton_clicked()
{

    ui->boatSizeLineEdit->clear();
    ui->boatLocationLineEdit->clear();
    ui->boatOwnerNameLineEdit->clear();
    ui->boatOwnerEmailLineEdit->clear();
    ui->boatTypeLineEdit->clear();
    ui->boatStatusComboBox->setCurrentIndex(1);
    ui->boatMaintenanceDateEdit->setDate(QDate::currentDate());
    ui->boatTripsSpinBox->setValue(0);
    ui->boatFishSpinBox->setValue(0);

    // If we're in Edit mode, switch back to Add mode
    if (currentBoatMode == BoatMode::Edit) {
        setBoatMode(BoatMode::Add);
    }
}


void appwindow::on_comboBox_15_currentIndexChanged(int index)
{
    switch (index) {                                                              break; // Sort by...
    case 1: ui->Boatwidget_2->setSortingEnabled(true);
        ui->Boatwidget_2->sortByColumn(1, Qt::AscendingOrder);
        ui->Boatwidget_2->setSortingEnabled(false);                                       break; // Size
    case 2: ui->Boatwidget_2->setSortingEnabled(true);
        ui->Boatwidget_2->sortByColumn(7, Qt::AscendingOrder);
        ui->Boatwidget_2->setSortingEnabled(false);                                       break; // Last Maintenance Date
    default: break;
    }
}

void appwindow::on_logout_clicked()
{
    QSettings settings("MyApp", "UserLogin");
    settings.clear(); // remove saved session

    MainWindow *login = new MainWindow();
    login->show();
    this->close();
}

