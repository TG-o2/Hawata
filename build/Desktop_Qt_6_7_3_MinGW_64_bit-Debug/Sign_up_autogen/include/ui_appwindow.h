/********************************************************************************
** Form generated from reading UI file 'appwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPWINDOW_H
#define UI_APPWINDOW_H

#include <QtCharts/QChartView>
#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
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
    QToolBox *COMPANIES;
    QWidget *companiePage;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QLabel *labelResults;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QPushButton *add_company;
    QPushButton *edit_company;
    QPushButton *delete_company;
    QPushButton *export_pdf;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *searchbar;
    QPushButton *clear;
    QWidget *COMPANIESPage2;
    QChartView *chartView;
    QLabel *labelStatsTitle;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QPushButton *pushButton_5;
    QWidget *page_3;
    QGroupBox *groupBox_target;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_target_2;
    QRadioButton *radio_inactive_2;
    QRadioButton *radio_promotion_2;
    QRadioButton *radio_custom_2;
    QSpacerItem *horizontalSpacer_4;
    QWidget *widget_filters_2;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_filters_2;
    QLabel *label_filter_fish_2;
    QComboBox *filter_fish_2;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_filter_location_2;
    QComboBox *filter_location_2;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_target_count_2;
    QWidget *layoutWidget_subject_2;
    QVBoxLayout *verticalLayout_subject_2;
    QLabel *label_subject_2;
    QLineEdit *input_subject_2;
    QLabel *label_template_2;
    QTextEdit *email_template_2;
    QWidget *horizontalLayoutWidget_presets_2;
    QHBoxLayout *horizontalLayout_presets_2;
    QLabel *label_presets_2;
    QPushButton *btn_template_inactive_2;
    QPushButton *btn_template_promo_2;
    QPushButton *btn_template_clear_2;
    QWidget *horizontalLayoutWidget_actions_2;
    QHBoxLayout *layout_buttons_2;
    QPushButton *btn_preview_2;
    QPushButton *btn_send_now_2;
    QLabel *label_schedule_2;
    QDateTimeEdit *schedule_date_2;
    QPushButton *btn_schedule_2;
    QWidget *page_4;
    QGroupBox *groupBox_trends;
    QWidget *horizontalLayoutWidget_filters;
    QHBoxLayout *horizontalLayout_time_filters;
    QLabel *label_time_range;
    QComboBox *combo_time_range;
    QSpacerItem *horizontalSpacer_trends;
    QLabel *label_chart_type;
    QComboBox *combo_chart_type;
    QSpacerItem *horizontalSpacer_trends2;
    QWidget *horizontalLayoutWidget_charts;
    QHBoxLayout *horizontalLayout_charts;
    QChartView *chartView_main;
    QVBoxLayout *verticalLayout_insights;
    QLabel *label_top_companies;
    QTableWidget *table_top_companies;
    QLabel *label_key_insights;
    QTextEdit *text_insights;
    QWidget *horizontalLayoutWidget_actions;
    QHBoxLayout *horizontalLayout_export_actions;
    QVBoxLayout *verticalLayout_summary;
    QLabel *label_summary_title;
    QLabel *label_total_purchases;
    QLabel *label_active_companies;
    QLabel *label_avg_purchase;
    QSpacerItem *horizontalSpacer_export;
    QVBoxLayout *verticalLayout_export;
    QLabel *label_export;
    QPushButton *btn_export_trends_pdf;
    QPushButton *btn_export_trends_csv;
    QWidget *tab_4;
    QWidget *tab_5;
    QWidget *tab_2;

    void setupUi(QDialog *appwindow)
    {
        if (appwindow->objectName().isEmpty())
            appwindow->setObjectName("appwindow");
        appwindow->resize(1256, 846);
        WebBrowsing = new QTabWidget(appwindow);
        WebBrowsing->setObjectName("WebBrowsing");
        WebBrowsing->setGeometry(QRect(10, 10, 1251, 831));
        tab = new QWidget();
        tab->setObjectName("tab");
        ToolBox_pages = new QToolBox(tab);
        ToolBox_pages->setObjectName("ToolBox_pages");
        ToolBox_pages->setGeometry(QRect(20, 10, 1211, 731));
        page = new QWidget();
        page->setObjectName("page");
        page->setGeometry(QRect(0, 0, 100, 30));
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
        page_2->setGeometry(QRect(0, 0, 1211, 661));
        ToolBox_pages->addItem(page_2, QString::fromUtf8("Page 2"));
        WebBrowsing->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        COMPANIES = new QToolBox(tab_3);
        COMPANIES->setObjectName("COMPANIES");
        COMPANIES->setGeometry(QRect(0, 0, 1191, 691));
        COMPANIES->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
        COMPANIES->setContextMenuPolicy(Qt::ContextMenuPolicy::PreventContextMenu);
        COMPANIES->setAutoFillBackground(true);
        companiePage = new QWidget();
        companiePage->setObjectName("companiePage");
        companiePage->setGeometry(QRect(0, 0, 1191, 551));
        layoutWidget = new QWidget(companiePage);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(91, 71, 881, 461));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget = new QTableWidget(layoutWidget);
        if (tableWidget->columnCount() < 7)
            tableWidget->setColumnCount(7);
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
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setAutoFillBackground(true);
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);
        tableWidget->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        tableWidget->setAlternatingRowColors(true);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        verticalLayout->addWidget(tableWidget);

        labelResults = new QLabel(layoutWidget);
        labelResults->setObjectName("labelResults");
        labelResults->setMinimumSize(QSize(151, 20));
        labelResults->setLineWidth(1);

        verticalLayout->addWidget(labelResults);

        layoutWidget1 = new QWidget(companiePage);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(1010, 180, 121, 251));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        add_company = new QPushButton(layoutWidget1);
        add_company->setObjectName("add_company");

        verticalLayout_2->addWidget(add_company);

        edit_company = new QPushButton(layoutWidget1);
        edit_company->setObjectName("edit_company");

        verticalLayout_2->addWidget(edit_company);

        delete_company = new QPushButton(layoutWidget1);
        delete_company->setObjectName("delete_company");

        verticalLayout_2->addWidget(delete_company);

        export_pdf = new QPushButton(layoutWidget1);
        export_pdf->setObjectName("export_pdf");
        export_pdf->setFlat(false);

        verticalLayout_2->addWidget(export_pdf);

        layoutWidget2 = new QWidget(companiePage);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(130, 20, 841, 31));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        searchbar = new QLineEdit(layoutWidget2);
        searchbar->setObjectName("searchbar");

        horizontalLayout_2->addWidget(searchbar);

        clear = new QPushButton(layoutWidget2);
        clear->setObjectName("clear");

        horizontalLayout_2->addWidget(clear);

        COMPANIES->addItem(companiePage, QString::fromUtf8("companies"));
        COMPANIESPage2 = new QWidget();
        COMPANIESPage2->setObjectName("COMPANIESPage2");
        COMPANIESPage2->setGeometry(QRect(0, 0, 1191, 551));
        chartView = new QChartView(COMPANIESPage2);
        chartView->setObjectName("chartView");
        chartView->setGeometry(QRect(110, 90, 971, 421));
        labelStatsTitle = new QLabel(COMPANIESPage2);
        labelStatsTitle->setObjectName("labelStatsTitle");
        labelStatsTitle->setGeometry(QRect(400, 0, 401, 51));
        labelStatsTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);
        labelStatsTitle->setWordWrap(false);
        layoutWidget3 = new QWidget(COMPANIESPage2);
        layoutWidget3->setObjectName("layoutWidget3");
        layoutWidget3->setGeometry(QRect(20, 40, 321, 41));
        horizontalLayout = new QHBoxLayout(layoutWidget3);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        comboBox = new QComboBox(layoutWidget3);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        horizontalLayout->addWidget(comboBox);

        pushButton_5 = new QPushButton(layoutWidget3);
        pushButton_5->setObjectName("pushButton_5");

        horizontalLayout->addWidget(pushButton_5);

        COMPANIES->addItem(COMPANIESPage2, QString::fromUtf8("statistics"));
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        page_3->setGeometry(QRect(0, 0, 1191, 551));
        groupBox_target = new QGroupBox(page_3);
        groupBox_target->setObjectName("groupBox_target");
        groupBox_target->setEnabled(true);
        groupBox_target->setGeometry(QRect(20, 0, 1081, 551));
        horizontalLayoutWidget_3 = new QWidget(groupBox_target);
        horizontalLayoutWidget_3->setObjectName("horizontalLayoutWidget_3");
        horizontalLayoutWidget_3->setGeometry(QRect(20, 30, 1060, 31));
        horizontalLayout_target_2 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_target_2->setObjectName("horizontalLayout_target_2");
        horizontalLayout_target_2->setContentsMargins(0, 0, 0, 0);
        radio_inactive_2 = new QRadioButton(horizontalLayoutWidget_3);
        radio_inactive_2->setObjectName("radio_inactive_2");
        radio_inactive_2->setChecked(true);

        horizontalLayout_target_2->addWidget(radio_inactive_2);

        radio_promotion_2 = new QRadioButton(horizontalLayoutWidget_3);
        radio_promotion_2->setObjectName("radio_promotion_2");

        horizontalLayout_target_2->addWidget(radio_promotion_2);

        radio_custom_2 = new QRadioButton(horizontalLayoutWidget_3);
        radio_custom_2->setObjectName("radio_custom_2");

        horizontalLayout_target_2->addWidget(radio_custom_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_target_2->addItem(horizontalSpacer_4);

        widget_filters_2 = new QWidget(groupBox_target);
        widget_filters_2->setObjectName("widget_filters_2");
        widget_filters_2->setGeometry(QRect(29, 70, 1041, 461));
        horizontalLayoutWidget_4 = new QWidget(widget_filters_2);
        horizontalLayoutWidget_4->setObjectName("horizontalLayoutWidget_4");
        horizontalLayoutWidget_4->setGeometry(QRect(10, 10, 1020, 41));
        horizontalLayout_filters_2 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_filters_2->setObjectName("horizontalLayout_filters_2");
        horizontalLayout_filters_2->setContentsMargins(0, 0, 0, 0);
        label_filter_fish_2 = new QLabel(horizontalLayoutWidget_4);
        label_filter_fish_2->setObjectName("label_filter_fish_2");

        horizontalLayout_filters_2->addWidget(label_filter_fish_2);

        filter_fish_2 = new QComboBox(horizontalLayoutWidget_4);
        filter_fish_2->addItem(QString());
        filter_fish_2->addItem(QString());
        filter_fish_2->addItem(QString());
        filter_fish_2->addItem(QString());
        filter_fish_2->addItem(QString());
        filter_fish_2->setObjectName("filter_fish_2");
        filter_fish_2->setMinimumSize(QSize(150, 0));

        horizontalLayout_filters_2->addWidget(filter_fish_2);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_filters_2->addItem(horizontalSpacer_5);

        label_filter_location_2 = new QLabel(horizontalLayoutWidget_4);
        label_filter_location_2->setObjectName("label_filter_location_2");

        horizontalLayout_filters_2->addWidget(label_filter_location_2);

        filter_location_2 = new QComboBox(horizontalLayoutWidget_4);
        filter_location_2->addItem(QString());
        filter_location_2->addItem(QString());
        filter_location_2->addItem(QString());
        filter_location_2->addItem(QString());
        filter_location_2->addItem(QString());
        filter_location_2->addItem(QString());
        filter_location_2->setObjectName("filter_location_2");
        filter_location_2->setMinimumSize(QSize(150, 0));

        horizontalLayout_filters_2->addWidget(filter_location_2);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_filters_2->addItem(horizontalSpacer_6);

        label_target_count_2 = new QLabel(horizontalLayoutWidget_4);
        label_target_count_2->setObjectName("label_target_count_2");
        label_target_count_2->setMinimumSize(QSize(150, 0));

        horizontalLayout_filters_2->addWidget(label_target_count_2);

        layoutWidget_subject_2 = new QWidget(widget_filters_2);
        layoutWidget_subject_2->setObjectName("layoutWidget_subject_2");
        layoutWidget_subject_2->setGeometry(QRect(10, 60, 1020, 55));
        verticalLayout_subject_2 = new QVBoxLayout(layoutWidget_subject_2);
        verticalLayout_subject_2->setObjectName("verticalLayout_subject_2");
        verticalLayout_subject_2->setContentsMargins(0, 0, 0, 0);
        label_subject_2 = new QLabel(layoutWidget_subject_2);
        label_subject_2->setObjectName("label_subject_2");

        verticalLayout_subject_2->addWidget(label_subject_2);

        input_subject_2 = new QLineEdit(layoutWidget_subject_2);
        input_subject_2->setObjectName("input_subject_2");

        verticalLayout_subject_2->addWidget(input_subject_2);

        label_template_2 = new QLabel(widget_filters_2);
        label_template_2->setObjectName("label_template_2");
        label_template_2->setGeometry(QRect(10, 120, 200, 20));
        email_template_2 = new QTextEdit(widget_filters_2);
        email_template_2->setObjectName("email_template_2");
        email_template_2->setGeometry(QRect(10, 145, 1020, 220));
        horizontalLayoutWidget_presets_2 = new QWidget(widget_filters_2);
        horizontalLayoutWidget_presets_2->setObjectName("horizontalLayoutWidget_presets_2");
        horizontalLayoutWidget_presets_2->setGeometry(QRect(10, 375, 931, 35));
        horizontalLayout_presets_2 = new QHBoxLayout(horizontalLayoutWidget_presets_2);
        horizontalLayout_presets_2->setObjectName("horizontalLayout_presets_2");
        horizontalLayout_presets_2->setContentsMargins(0, 0, 0, 0);
        label_presets_2 = new QLabel(horizontalLayoutWidget_presets_2);
        label_presets_2->setObjectName("label_presets_2");

        horizontalLayout_presets_2->addWidget(label_presets_2);

        btn_template_inactive_2 = new QPushButton(horizontalLayoutWidget_presets_2);
        btn_template_inactive_2->setObjectName("btn_template_inactive_2");

        horizontalLayout_presets_2->addWidget(btn_template_inactive_2);

        btn_template_promo_2 = new QPushButton(horizontalLayoutWidget_presets_2);
        btn_template_promo_2->setObjectName("btn_template_promo_2");

        horizontalLayout_presets_2->addWidget(btn_template_promo_2);

        btn_template_clear_2 = new QPushButton(horizontalLayoutWidget_presets_2);
        btn_template_clear_2->setObjectName("btn_template_clear_2");

        horizontalLayout_presets_2->addWidget(btn_template_clear_2);

        horizontalLayoutWidget_actions_2 = new QWidget(widget_filters_2);
        horizontalLayoutWidget_actions_2->setObjectName("horizontalLayoutWidget_actions_2");
        horizontalLayoutWidget_actions_2->setGeometry(QRect(200, 420, 821, 41));
        layout_buttons_2 = new QHBoxLayout(horizontalLayoutWidget_actions_2);
        layout_buttons_2->setObjectName("layout_buttons_2");
        layout_buttons_2->setContentsMargins(0, 0, 0, 0);
        btn_preview_2 = new QPushButton(horizontalLayoutWidget_actions_2);
        btn_preview_2->setObjectName("btn_preview_2");
        btn_preview_2->setMinimumSize(QSize(150, 35));

        layout_buttons_2->addWidget(btn_preview_2);

        btn_send_now_2 = new QPushButton(horizontalLayoutWidget_actions_2);
        btn_send_now_2->setObjectName("btn_send_now_2");
        btn_send_now_2->setMinimumSize(QSize(150, 35));

        layout_buttons_2->addWidget(btn_send_now_2);

        label_schedule_2 = new QLabel(horizontalLayoutWidget_actions_2);
        label_schedule_2->setObjectName("label_schedule_2");

        layout_buttons_2->addWidget(label_schedule_2);

        schedule_date_2 = new QDateTimeEdit(horizontalLayoutWidget_actions_2);
        schedule_date_2->setObjectName("schedule_date_2");
        schedule_date_2->setMinimumSize(QSize(180, 35));
        schedule_date_2->setDateTime(QDateTime(QDate(2025, 1, 1), QTime(0, 0, 0)));
        schedule_date_2->setDate(QDate(2025, 1, 1));
        schedule_date_2->setCalendarPopup(true);

        layout_buttons_2->addWidget(schedule_date_2);

        btn_schedule_2 = new QPushButton(horizontalLayoutWidget_actions_2);
        btn_schedule_2->setObjectName("btn_schedule_2");
        btn_schedule_2->setMinimumSize(QSize(120, 35));

        layout_buttons_2->addWidget(btn_schedule_2);

        COMPANIES->addItem(page_3, QString::fromUtf8("Automated Emails"));
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        groupBox_trends = new QGroupBox(page_4);
        groupBox_trends->setObjectName("groupBox_trends");
        groupBox_trends->setGeometry(QRect(20, 10, 1081, 561));
        horizontalLayoutWidget_filters = new QWidget(groupBox_trends);
        horizontalLayoutWidget_filters->setObjectName("horizontalLayoutWidget_filters");
        horizontalLayoutWidget_filters->setGeometry(QRect(10, 30, 1070, 41));
        horizontalLayout_time_filters = new QHBoxLayout(horizontalLayoutWidget_filters);
        horizontalLayout_time_filters->setObjectName("horizontalLayout_time_filters");
        horizontalLayout_time_filters->setContentsMargins(0, 0, 0, 0);
        label_time_range = new QLabel(horizontalLayoutWidget_filters);
        label_time_range->setObjectName("label_time_range");

        horizontalLayout_time_filters->addWidget(label_time_range);

        combo_time_range = new QComboBox(horizontalLayoutWidget_filters);
        combo_time_range->addItem(QString());
        combo_time_range->addItem(QString());
        combo_time_range->addItem(QString());
        combo_time_range->addItem(QString());
        combo_time_range->addItem(QString());
        combo_time_range->setObjectName("combo_time_range");
        combo_time_range->setMinimumSize(QSize(150, 0));

        horizontalLayout_time_filters->addWidget(combo_time_range);

        horizontalSpacer_trends = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_time_filters->addItem(horizontalSpacer_trends);

        label_chart_type = new QLabel(horizontalLayoutWidget_filters);
        label_chart_type->setObjectName("label_chart_type");

        horizontalLayout_time_filters->addWidget(label_chart_type);

        combo_chart_type = new QComboBox(horizontalLayoutWidget_filters);
        combo_chart_type->addItem(QString());
        combo_chart_type->addItem(QString());
        combo_chart_type->addItem(QString());
        combo_chart_type->addItem(QString());
        combo_chart_type->setObjectName("combo_chart_type");
        combo_chart_type->setMinimumSize(QSize(180, 0));

        horizontalLayout_time_filters->addWidget(combo_chart_type);

        horizontalSpacer_trends2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_time_filters->addItem(horizontalSpacer_trends2);

        horizontalLayoutWidget_charts = new QWidget(groupBox_trends);
        horizontalLayoutWidget_charts->setObjectName("horizontalLayoutWidget_charts");
        horizontalLayoutWidget_charts->setGeometry(QRect(10, 80, 1070, 331));
        horizontalLayout_charts = new QHBoxLayout(horizontalLayoutWidget_charts);
        horizontalLayout_charts->setObjectName("horizontalLayout_charts");
        horizontalLayout_charts->setContentsMargins(0, 0, 0, 0);
        chartView_main = new QChartView(horizontalLayoutWidget_charts);
        chartView_main->setObjectName("chartView_main");
        chartView_main->setMinimumSize(QSize(650, 0));

        horizontalLayout_charts->addWidget(chartView_main);

        verticalLayout_insights = new QVBoxLayout();
        verticalLayout_insights->setObjectName("verticalLayout_insights");
        label_top_companies = new QLabel(horizontalLayoutWidget_charts);
        label_top_companies->setObjectName("label_top_companies");

        verticalLayout_insights->addWidget(label_top_companies);

        table_top_companies = new QTableWidget(horizontalLayoutWidget_charts);
        if (table_top_companies->columnCount() < 3)
            table_top_companies->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        table_top_companies->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        table_top_companies->setHorizontalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        table_top_companies->setHorizontalHeaderItem(2, __qtablewidgetitem9);
        table_top_companies->setObjectName("table_top_companies");
        table_top_companies->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        table_top_companies->setAlternatingRowColors(true);
        table_top_companies->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        verticalLayout_insights->addWidget(table_top_companies);

        label_key_insights = new QLabel(horizontalLayoutWidget_charts);
        label_key_insights->setObjectName("label_key_insights");

        verticalLayout_insights->addWidget(label_key_insights);

        text_insights = new QTextEdit(horizontalLayoutWidget_charts);
        text_insights->setObjectName("text_insights");
        text_insights->setReadOnly(true);

        verticalLayout_insights->addWidget(text_insights);


        horizontalLayout_charts->addLayout(verticalLayout_insights);

        horizontalLayoutWidget_actions = new QWidget(groupBox_trends);
        horizontalLayoutWidget_actions->setObjectName("horizontalLayoutWidget_actions");
        horizontalLayoutWidget_actions->setGeometry(QRect(10, 420, 1070, 91));
        horizontalLayout_export_actions = new QHBoxLayout(horizontalLayoutWidget_actions);
        horizontalLayout_export_actions->setObjectName("horizontalLayout_export_actions");
        horizontalLayout_export_actions->setContentsMargins(0, 0, 0, 0);
        verticalLayout_summary = new QVBoxLayout();
        verticalLayout_summary->setObjectName("verticalLayout_summary");
        label_summary_title = new QLabel(horizontalLayoutWidget_actions);
        label_summary_title->setObjectName("label_summary_title");

        verticalLayout_summary->addWidget(label_summary_title);

        label_total_purchases = new QLabel(horizontalLayoutWidget_actions);
        label_total_purchases->setObjectName("label_total_purchases");

        verticalLayout_summary->addWidget(label_total_purchases);

        label_active_companies = new QLabel(horizontalLayoutWidget_actions);
        label_active_companies->setObjectName("label_active_companies");

        verticalLayout_summary->addWidget(label_active_companies);

        label_avg_purchase = new QLabel(horizontalLayoutWidget_actions);
        label_avg_purchase->setObjectName("label_avg_purchase");

        verticalLayout_summary->addWidget(label_avg_purchase);


        horizontalLayout_export_actions->addLayout(verticalLayout_summary);

        horizontalSpacer_export = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_export_actions->addItem(horizontalSpacer_export);

        verticalLayout_export = new QVBoxLayout();
        verticalLayout_export->setObjectName("verticalLayout_export");
        label_export = new QLabel(horizontalLayoutWidget_actions);
        label_export->setObjectName("label_export");

        verticalLayout_export->addWidget(label_export);

        btn_export_trends_pdf = new QPushButton(horizontalLayoutWidget_actions);
        btn_export_trends_pdf->setObjectName("btn_export_trends_pdf");
        btn_export_trends_pdf->setMinimumSize(QSize(200, 35));

        verticalLayout_export->addWidget(btn_export_trends_pdf);

        btn_export_trends_csv = new QPushButton(horizontalLayoutWidget_actions);
        btn_export_trends_csv->setObjectName("btn_export_trends_csv");
        btn_export_trends_csv->setMinimumSize(QSize(200, 35));

        verticalLayout_export->addWidget(btn_export_trends_csv);


        horizontalLayout_export_actions->addLayout(verticalLayout_export);

        COMPANIES->addItem(page_4, QString::fromUtf8("Trends and insights"));
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

        retranslateUi(appwindow);

        WebBrowsing->setCurrentIndex(1);
        ToolBox_pages->setCurrentIndex(1);


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
#if QT_CONFIG(accessibility)
        COMPANIES->setAccessibleName(QCoreApplication::translate("appwindow", "companies", nullptr));
#endif // QT_CONFIG(accessibility)
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("appwindow", "Company_ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("appwindow", "name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("appwindow", "location", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("appwindow", "email", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("appwindow", "phone", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("appwindow", "preferred fish", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("appwindow", "status", nullptr));
        labelResults->setText(QCoreApplication::translate("appwindow", "Showing 0 companies", nullptr));
        add_company->setText(QCoreApplication::translate("appwindow", "Add", nullptr));
        edit_company->setText(QCoreApplication::translate("appwindow", "Edit", nullptr));
        delete_company->setText(QCoreApplication::translate("appwindow", "Delete", nullptr));
        export_pdf->setText(QCoreApplication::translate("appwindow", "Export  PDF", nullptr));
        searchbar->setText(QString());
        searchbar->setPlaceholderText(QCoreApplication::translate("appwindow", "Search by name or phone", nullptr));
        clear->setText(QCoreApplication::translate("appwindow", "Clear", nullptr));
        COMPANIES->setItemText(COMPANIES->indexOf(companiePage), QCoreApplication::translate("appwindow", "companies", nullptr));
        labelStatsTitle->setText(QCoreApplication::translate("appwindow", "Company Statistics", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("appwindow", "preferred fish", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("appwindow", "status", nullptr));

        pushButton_5->setText(QCoreApplication::translate("appwindow", "generate", nullptr));
        COMPANIES->setItemText(COMPANIES->indexOf(COMPANIESPage2), QCoreApplication::translate("appwindow", "statistics", nullptr));
        groupBox_target->setTitle(QCoreApplication::translate("appwindow", "Target Companies", nullptr));
        radio_inactive_2->setText(QCoreApplication::translate("appwindow", "Inactive Companies (30+ days)", nullptr));
        radio_promotion_2->setText(QCoreApplication::translate("appwindow", "Promotion (All Active Companies)", nullptr));
        radio_custom_2->setText(QCoreApplication::translate("appwindow", "Custom Target", nullptr));
        label_filter_fish_2->setText(QCoreApplication::translate("appwindow", "Filter by Fish:", nullptr));
        filter_fish_2->setItemText(0, QCoreApplication::translate("appwindow", "All Fish Types", nullptr));
        filter_fish_2->setItemText(1, QCoreApplication::translate("appwindow", "Sardina", nullptr));
        filter_fish_2->setItemText(2, QCoreApplication::translate("appwindow", "Choro", nullptr));
        filter_fish_2->setItemText(3, QCoreApplication::translate("appwindow", "Tuna", nullptr));
        filter_fish_2->setItemText(4, QCoreApplication::translate("appwindow", "Other", nullptr));

        label_filter_location_2->setText(QCoreApplication::translate("appwindow", "Filter by Location:", nullptr));
        filter_location_2->setItemText(0, QCoreApplication::translate("appwindow", "All Locations", nullptr));
        filter_location_2->setItemText(1, QCoreApplication::translate("appwindow", "Tunis", nullptr));
        filter_location_2->setItemText(2, QCoreApplication::translate("appwindow", "Sousse", nullptr));
        filter_location_2->setItemText(3, QCoreApplication::translate("appwindow", "Bizerte", nullptr));
        filter_location_2->setItemText(4, QCoreApplication::translate("appwindow", "Sfax", nullptr));
        filter_location_2->setItemText(5, QCoreApplication::translate("appwindow", "Gabes", nullptr));

        label_target_count_2->setText(QCoreApplication::translate("appwindow", "Target: 0 companies", nullptr));
        label_subject_2->setText(QCoreApplication::translate("appwindow", "Email Subject:", nullptr));
        input_subject_2->setPlaceholderText(QCoreApplication::translate("appwindow", "Enter email subject line", nullptr));
        label_template_2->setText(QCoreApplication::translate("appwindow", "Email Template:", nullptr));
        email_template_2->setPlaceholderText(QCoreApplication::translate("appwindow", "Write your email template here. Use [Company Name], [Preferred Fish], [Location], [Email] as placeholders.\n"
"\n"
"Example:\n"
"Dear [Company Name],\n"
"\n"
"We noticed that we haven't had the pleasure of serving you recently. We would love to reconnect and discuss how we can continue to provide you with the finest [Preferred Fish] available.\n"
"\n"
"Our team is ready to assist you with your seafood needs.\n"
"\n"
"Best regards,\n"
"The Team", nullptr));
        label_presets_2->setText(QCoreApplication::translate("appwindow", "Quick Templates:", nullptr));
        btn_template_inactive_2->setText(QCoreApplication::translate("appwindow", "Inactive Template", nullptr));
        btn_template_promo_2->setText(QCoreApplication::translate("appwindow", "Promotion Template", nullptr));
        btn_template_clear_2->setText(QCoreApplication::translate("appwindow", "Clear Template", nullptr));
        btn_preview_2->setText(QCoreApplication::translate("appwindow", "\360\237\221\201\357\270\217 Preview Email", nullptr));
        btn_send_now_2->setText(QCoreApplication::translate("appwindow", "\360\237\223\247 Send Now", nullptr));
        label_schedule_2->setText(QCoreApplication::translate("appwindow", "Schedule for:", nullptr));
        btn_schedule_2->setText(QCoreApplication::translate("appwindow", "\342\217\260 Schedule", nullptr));
        COMPANIES->setItemText(COMPANIES->indexOf(page_3), QCoreApplication::translate("appwindow", "Automated Emails", nullptr));
        groupBox_trends->setTitle(QCoreApplication::translate("appwindow", "Activity & Purchase Pattern Analysis", nullptr));
        label_time_range->setText(QCoreApplication::translate("appwindow", "Time Range:", nullptr));
        combo_time_range->setItemText(0, QCoreApplication::translate("appwindow", "Last Month", nullptr));
        combo_time_range->setItemText(1, QCoreApplication::translate("appwindow", "Last 3 Months", nullptr));
        combo_time_range->setItemText(2, QCoreApplication::translate("appwindow", "Last 6 Months", nullptr));
        combo_time_range->setItemText(3, QCoreApplication::translate("appwindow", "Last Year", nullptr));
        combo_time_range->setItemText(4, QCoreApplication::translate("appwindow", "All Time", nullptr));

        label_chart_type->setText(QCoreApplication::translate("appwindow", "Analysis Type:", nullptr));
        combo_chart_type->setItemText(0, QCoreApplication::translate("appwindow", "Purchases by Fish Type", nullptr));
        combo_chart_type->setItemText(1, QCoreApplication::translate("appwindow", "Purchases by Location", nullptr));
        combo_chart_type->setItemText(2, QCoreApplication::translate("appwindow", "Purchases by Status", nullptr));
        combo_chart_type->setItemText(3, QCoreApplication::translate("appwindow", "Purchase Timeline", nullptr));

        label_top_companies->setText(QCoreApplication::translate("appwindow", "Top 5 Companies by Purchase Volume", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = table_top_companies->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("appwindow", "Rank", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = table_top_companies->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("appwindow", "Company", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = table_top_companies->horizontalHeaderItem(2);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("appwindow", "Purchases", nullptr));
        label_key_insights->setText(QCoreApplication::translate("appwindow", "Key Insights", nullptr));
        text_insights->setPlaceholderText(QCoreApplication::translate("appwindow", "Insights will appear here based on analysis...", nullptr));
        label_summary_title->setText(QCoreApplication::translate("appwindow", "Quick Summary", nullptr));
        label_total_purchases->setText(QCoreApplication::translate("appwindow", "Total Purchases: 0", nullptr));
        label_active_companies->setText(QCoreApplication::translate("appwindow", "Active Companies: 0", nullptr));
        label_avg_purchase->setText(QCoreApplication::translate("appwindow", "Avg Purchase/Company: 0", nullptr));
        label_export->setText(QCoreApplication::translate("appwindow", "Export Options", nullptr));
        btn_export_trends_pdf->setText(QCoreApplication::translate("appwindow", "Export Report as PDF", nullptr));
        btn_export_trends_csv->setText(QCoreApplication::translate("appwindow", "Export Data as CSV", nullptr));
        COMPANIES->setItemText(COMPANIES->indexOf(page_4), QCoreApplication::translate("appwindow", "Trends and insights", nullptr));
        WebBrowsing->setTabText(WebBrowsing->indexOf(tab_3), QCoreApplication::translate("appwindow", "companies", nullptr));
        WebBrowsing->setTabText(WebBrowsing->indexOf(tab_4), QCoreApplication::translate("appwindow", "Page", nullptr));
        WebBrowsing->setTabText(WebBrowsing->indexOf(tab_5), QCoreApplication::translate("appwindow", "Page", nullptr));
        WebBrowsing->setTabText(WebBrowsing->indexOf(tab_2), QCoreApplication::translate("appwindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class appwindow: public Ui_appwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPWINDOW_H
