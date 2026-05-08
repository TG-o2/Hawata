
#ifndef APPWINDOW_H
#define APPWINDOW_H

#include "user.h"
#include "connection.h"
#include "arduino.h"
#include "product.h"
#include "boats.h"
#include "company.h"
#include "Docking.h"
#include "manage.h"
#include "chatbotdialog.h"
#include <QSettings>
#include <QDialog>
#include <QByteArray>
#include <QQuickWidget>

// WebEngine includes disabled - Qt6 WebEngineWidgets not installed
// #include <QWebEngineView>
// #include <QWebChannel>
// #include <QWebEngineProfile>
// #include <QWebEngineSettings>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>
#include <QDir>

QT_BEGIN_NAMESPACE
class QSerialPort;
class QQuickWidget;
QT_END_NAMESPACE

class QModelIndex;
class QSqlQueryModel;
class QTableWidgetItem;

namespace Ui {
class appwindow;
}

// Temperature threshold for fan control (max temp before fan turns on)
constexpr double MAX_TEMP_THRESHOLD = 30.0;

class appwindow : public QDialog
{
    Q_OBJECT

public:
    explicit appwindow(QWidget *parent = nullptr, int currentUserId = -1, const QString &currentUserRole = "");
    ~appwindow();

private slots:
    // ============================ START USER MODULE .h ============================
    // User CRUD slots 
    void fillUserForm(const QModelIndex &index);
    void on_UPDUser_clicked();
    void on_deleteUSERBtn_clicked();
    void on_editUSERBtn_clicked();
    void on_usersTable_cellClicked(int row, int column);
    void on_usersTable_cellDoubleClicked(int row, int column);
    void on_clear_3_clicked();
    void on_pushButton_8_clicked();
    void on_searchbar_3_textChanged(const QString &text);
    void on_comboBox_11_currentIndexChanged(int index);
    void on_export_pdf_user_clicked();
    void on_logout_clicked();

    // ============================ END USER MODULE .h ============================

    // docking CRUD
    void on_CreateDocking_clicked();
    void on_edit_Docking_clicked();
    void on_delete_docking_clicked();
    void on_DockCalender_clicked();
    void on_tabdocking_cellDoubleClicked(int row, int column);
    void on_tabdocking_cellClicked(int row, int column);
    void on_clear_docking_clicked();
    void on_searchbar_docking_textChanged(const QString &text);
    void on_docking_sort_currentIndexChanged(int index);
    void on_export_docking_clicked();

    // product CRUD
    void on_checkProductButton_2_clicked();
    void on_checkProductButton_clicked();
    void on_Manage_24_clicked();
    void on_tableWidget_10_cellClicked(int row, int column);
    void on_tableWidget_10_cellDoubleClicked(int row, int column);
    void on_edit_company_6_clicked();
    void on_delete_company_6_clicked();
    void on_clear_6_clicked();
    void on_searchbar_6_textChanged(const QString &text);
    void on_comboBox_18_currentIndexChanged(int index);
    void on_export_pdf_6_clicked();
    void on_pushButton_11_clicked();
    void update_label();


    // boats CRUD
    void on_addBoatButton_clicked();
    void on_editBoatButton_clicked();
    void on_deleteBoatButton_clicked();
    void on_updateBoatButton_clicked();
    void on_searchBoatButton_3_clicked();
    void on_Boatwidget_2_itemSelectionChanged();
    void on_Boatwidget_2_itemDoubleClicked(QTableWidgetItem *item);
    //boat special features
    void onCheckMaintenanceReminders();
    void on_export_pdf_5_clicked();

    //boat map
    void onUpdateBoatPositions();
    void on_pushButton_trackBoat_clicked();
    void on_pushButton_trackAll_clicked();
    void on_comboBox_selectBoat_currentIndexChanged(int index);

    //arduino
    void update_boat_location_arduino();   // new slot for Arduino GPS coordinates (boat ID 1)

    // companies CRUD
    void on_tableWidget_11_cellClicked(int row, int column);
    void on_tableWidget_11_cellDoubleClicked(int row, int column);
    void on_CreateUser_3_clicked();
    void on_edit_company_7_clicked();
    void on_delete_company_7_clicked();
    void on_clear_7_clicked();
    void on_searchbar_7_textChanged(const QString &arg1);
    void on_export_pdf_7_clicked();
    void on_pushButton_12_clicked();
    void on_comboBox_19_currentTextChanged(const QString &arg1);

    void on_clearBoatButton_clicked();
    void on_comboBox_15_currentIndexChanged(int index);
    void initEmailCampaignPage();
    void updateTargetCount();
    QList<Company> getTargetCompanies();
    QString buildEmailBody(const Company &company, const QString &templateText);
    void on_btn_template_inactive_2_clicked();
    void on_btn_template_promo_2_clicked();
    void on_btn_template_clear_2_clicked();
    void on_btn_preview_2_clicked();
    void on_btn_send_now_2_clicked();
    void on_btn_schedule_2_clicked();
    // WhatsApp / SMS Alert page
    void initWhatsAppSmsPage();
    void updateWaSmsRecipientCount();
    void updateWaCharCount();

    // Quick template buttons
    void on_tpl_stock_available_clicked();
    void on_tpl_no_fish_clicked();
    void on_tpl_port_closed_clicked();
    void on_tpl_price_up_clicked();
    void on_tpl_maintenance_clicked();
    void on_tpl_pickup_ready_clicked();

    // Action buttons
    void on_btn_preview_msg_clicked();
    void on_btn_clear_msg_clicked();
    void on_btn_send_alert_clicked();
    void on_btn_schedule_alert_clicked();

private:
    Ui::appwindow *ui;

    // docks
    Docking dockingManager;
    Manage manageManager;
    int selectedDockingId = -1;
    void loadDockingTable();
    void populateDockingTable(const QList<DockingRecord> &records);
    void generateDockingStatistics();
    QString dockingHistoryFilePath() const;
    void ensureDockingHistoryFile();
    void appendDockingHistory(const QString &action, int dockId);
    void loadDockingHistoryView();
    QList<DockingRecord> allDockingRecords;

    // ============================ USER MODULE ============================
    // User state + managers used by User module integration
    User userManager;
    QSqlQueryModel *usersModel;
    int selectedUserId = -1;
    int connectedUserId = -1;
    QString connectedUserRole;
    void loadUsersTable();
    void loadUserStatistics(bool byRole);
    QList<User> allUserRecords;
    Connection conn;

    // products
    Product productManager;
    int selectedProductId = -1;
    void loadProductTable();
    void loadProductBoatIds();
    void refreshLowStockAlerts(bool showPopup = false);
    bool lowStockWarningShown = false;
    QList<ProductRecord> allProductRecords;
    /**
     * Arduino integration (slide pattern).
     *
     * A  — the Arduino object (replaces the old raw arduinoSerial pointer).
     * arduinoSerialBuffer — accumulates partial lines received via readyRead.
     *
     * Connection wired in setupArduinoTemperatureReader():
     *   QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(update_label()));
     */
    Arduino    A;                       // ← replaces QSerialPort *arduinoSerial
    QByteArray arduinoSerialBuffer;     // line-assembly buffer
    void setupArduinoTemperatureReader();


    //boats
    enum class BoatMode { Add, Edit };
    int findAvailableDock();
    bool isAnyDockAvailable();

    void displayBoats();
    void clearBoatInputs();
    void setBoatMode(BoatMode mode);
    void populateBoatForm(int boatId);
    int currentlySelectedId;
    BoatMode currentBoatMode = BoatMode::Add;

    Boats boatsTmp;
    void createBoatChart(const QStringList &categories, const QList<int> &values,const QString &title, const QString &yAxisLabel);
    void on_pushButton_10_clicked();

    QDate parseBoatMaintenanceDate(const QString &rawDate);
    void checkAndSendMaintenanceReminders();
    void sendMaintenanceReminderEmail(const QString &ownerEmail, const QString &ownerName,
    const QString &boatId, const QString &boatType,
    const QDate &lastMaintenanceDate, int weeksOverdue);
    QDate getNextMaintenanceDate(const QDate &lastMaintenanceDate);
    bool isEmailValid(const QString &email);

    // Timer for periodic checking
    QTimer *maintenanceCheckTimer;
    //status bar
    void updateBoatStatusProgressBar();

    // Boat tracking members
    QQuickWidget *boatMapView = nullptr;
    QTimer *locationUpdateTimer = nullptr;
    int currentTrackingBoatId = -1;
    double currentLatitude = 0.0;
    double currentLongitude = 0.0;
    QStringList trackedBoats;  // Store multiple boat IDs for tracking

    //Boat Map functions
    void setupGoogleMap();
    void updateBoatMapView(double latitude, double longitude);
    void populateBoatComboBox();
    void updateAllBoatPositions();
    void updateSingleBoatPosition(int boatId);
    bool getBoatCoordinates(int boatId, double &latitude, double &longitude, QString &boatName, QString &boatStatus);
    QString generateMapHTML();
    void injectJavaScript(const QString &script);
    




    // companies
    void loadCompaniesTable();
    void loadCompaniesTableFromList(const QList<Company> &records);
    void fillCompanyForm(int row);
    int selectedCompanyId = -1;
    QList<Company> getWaSmsTargetCompanies();
    QString normalizePhoneNumber(const QString &phone,
                                 const QString &countryCode = "+216");
    QString buildWaMessage(const Company &company, const QString &msgTemplate);
    QString buildSmsMessage(const Company &company, const QString &msgTemplate);
    QString buildWhatsAppUrl(const QString &phone, const QString &message);

    // product statistics
    void generateProductStatisticsByStatus(const QList<ProductRecord> &products);
    void generateProductQuantityByType(const QList<ProductRecord> &products);

    //chatbot
    ChatbotDialog *m_chatbot;



};

#endif // APPWINDOW_H
