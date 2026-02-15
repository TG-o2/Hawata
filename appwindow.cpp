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

    QPixmap pix("chart.png");

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

    //pictures for product--------
    QPixmap fish("icons/fishicon.png");
    QPixmap pic_2("logoQT.png");



    //product picture set up
    ui->pic->setPixmap(fish);
    ui->pic->setScaledContents(true);
    ui->pic_2->setPixmap(pic_2);
    ui->pic_2->setScaledContents(true);




    //end of product picture code--------------

    //chart for page 4 of window 1 (User management)

    ui->chart->setPixmap(pix);
    ui->chart->setScaledContents(true);
    ///----add manage display

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

    //dock page 4,5 & 6
    ui->adduser_4->setPixmap(Dock);
    ui->adduser_4->setScaledContents(true);

    ui->deluser_4->setPixmap(user_delete);
    ui->deluser_4->setScaledContents(true);

    ui->dispuser_4->setPixmap(user_display);
    ui->dispuser_4->setScaledContents(true);

    ui->adduser_5->setPixmap(Dock);
    ui->adduser_5->setScaledContents(true);

    ui->deluser_5->setPixmap(user_delete);
    ui->deluser_5->setScaledContents(true);

    ui->dispuser_5->setPixmap(user_display);
    ui->dispuser_5->setScaledContents(true);

    ui->adduser_6->setPixmap(Dock);
    ui->adduser_6->setScaledContents(true);

    ui->deluser_6->setPixmap(user_delete);
    ui->deluser_6->setScaledContents(true);

    ui->dispuser_6->setPixmap(user_display);
    ui->dispuser_6->setScaledContents(true);
    //boat page 7,8 & 9
    ui->adduser_7->setPixmap(Boat);
    ui->adduser_7->setScaledContents(true);

    ui->deluser_7->setPixmap(user_delete);
    ui->deluser_7->setScaledContents(true);

    ui->dispuser_7->setPixmap(user_display);
    ui->dispuser_7->setScaledContents(true);

    ui->adduser_8->setPixmap(Boat);
    ui->adduser_8->setScaledContents(true);

    ui->deluser_8->setPixmap(user_delete);
    ui->deluser_8->setScaledContents(true);

    ui->dispuser_8->setPixmap(user_display);
    ui->dispuser_8->setScaledContents(true);

    ui->adduser_9->setPixmap(Boat);
    ui->adduser_9->setScaledContents(true);

    ui->deluser_9->setPixmap(user_delete);
    ui->deluser_9->setScaledContents(true);

    ui->dispuser_9->setPixmap(user_display);
    ui->dispuser_9->setScaledContents(true);
    //PRODUCT page 10, 12 & 11
    ui->adduser_10->setPixmap(Prod);
    ui->adduser_10->setScaledContents(true);

    ui->deluser_10->setPixmap(user_delete);
    ui->deluser_10->setScaledContents(true);

    ui->dispuser_10->setPixmap(user_display);
    ui->dispuser_10->setScaledContents(true);

    ui->adduser_11->setPixmap(Prod);
    ui->adduser_11->setScaledContents(true);

    ui->deluser_11->setPixmap(user_delete);
    ui->deluser_11->setScaledContents(true);

    ui->dispuser_11->setPixmap(user_display);
    ui->dispuser_11->setScaledContents(true);

    ui->adduser_12->setPixmap(Prod);
    ui->adduser_12->setScaledContents(true);

    ui->deluser_12->setPixmap(user_delete);
    ui->deluser_12->setScaledContents(true);

    ui->dispuser_12->setPixmap(user_display);
    ui->dispuser_12->setScaledContents(true);
    //COMPANIES page 10, 12 & 11
    ui->adduser_13->setPixmap(Comp);
    ui->adduser_13->setScaledContents(true);

    ui->deluser_13->setPixmap(Stats);
    ui->deluser_13->setScaledContents(true);

    ui->dispuser_13->setPixmap(Email);
    ui->dispuser_13->setScaledContents(true);

    ui->adduser_14->setPixmap(Comp);
    ui->adduser_14->setScaledContents(true);

    ui->deluser_14->setPixmap(Stats);
    ui->deluser_14->setScaledContents(true);

    ui->dispuser_14->setPixmap(Email);
    ui->dispuser_14->setScaledContents(true);

    ui->adduser_15->setPixmap(Comp);
    ui->adduser_15->setScaledContents(true);

    ui->deluser_15->setPixmap(Stats);
    ui->deluser_15->setScaledContents(true);

    ui->dispuser_15->setPixmap(Email);
    ui->dispuser_15->setScaledContents(true);



    ///-----end

    //frame
    ui->BackFrame->lower();
    ui->BackFrame->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_2->lower();
    ui->BackFrame_3->lower();
    ui->BackFrame_4->lower();
    ui->BackFrame_5->lower();
    ui->BackFrame_6->lower();
    ui->BackFrame_7->lower();
    ui->BackFrame_8->lower();
    ui->BackFrame_9->lower();
    ui->BackFrame_10->lower();
    ui->BackFrame_11->lower();
    ui->BackFrame_12->lower();
    ui->BackFrame_13->lower();
    ui->BackFrame_14->lower();
    ui->BackFrame_15->lower();

    ui->BackFrame_2->setStyleSheet(
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
    ui->BackFrame_7->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_8->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_9->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_10->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_11->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_12->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_13->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_14->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );
    ui->BackFrame_15->setStyleSheet(
        "background: rgba(255, 255, 255, 0.3);"
        "border: 2px solid #42a5f5;"
        "border-radius: 8px;"
        );

    ///=============web / pages titles START================
    ui->WebBrowsing->setTabText(0, "👨‍💻 Users");
    ui->WebBrowsing->setTabText(1, "🛳️ Manage Dock");
    ui->WebBrowsing->setTabText(2, "⛵ Boats Admission");
    ui->WebBrowsing->setTabText(3, "🐟  Product Restock");
    ui->WebBrowsing->setTabText(4, "🏢  Companies");
    ui->WebBrowsing->setTabText(5, "🚪 Exit App");

    //ui->add_user_2->move()

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
    connect(ui->add_user_4  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(0);
    });
    connect(ui->Manage_4 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(1);
    });
    connect(ui->Display_4  , &QPushButton::clicked, this, [=]() {
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

    //page BOAT :,D
    connect(ui->add_user_7  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_3->setCurrentIndex(0);
    });
    connect(ui->Manage_7 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_3->setCurrentIndex(1);
    });
    connect(ui->Display_7  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_3->setCurrentIndex(2);
    });
    connect(ui->add_user_8  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_3->setCurrentIndex(0);
    });
    connect(ui->Manage_8 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_3->setCurrentIndex(1);
    });
    connect(ui->Display_8  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_3->setCurrentIndex(2);
    });
    connect(ui->add_user_9  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_3->setCurrentIndex(0);
    });
    connect(ui->Manage_9 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_3->setCurrentIndex(1);
    });
    connect(ui->Display_9  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_3->setCurrentIndex(2);
    });
    //page Prod
    connect(ui->add_user_10  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(0);
    });
    connect(ui->Manage_10 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(1);
    });
    connect(ui->Display_10  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(2);
    });
    connect(ui->add_user_11  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(0);
    });
    connect(ui->Manage_11 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(1);
    });
    connect(ui->Display_11  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(2);
    });
    connect(ui->add_user_12  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(0);
    });
    connect(ui->Manage_12 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(1);
    });
    connect(ui->Display_12  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_4->setCurrentIndex(2);
    });
    //cOMPANIES
    connect(ui->add_user_13  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(0);
    });
    connect(ui->Manage_13 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(1);
    });
    connect(ui->Display_13  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(2);
    });
    connect(ui->add_user_14  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(0);
    });
    connect(ui->Manage_14 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(1);
    });
    connect(ui->Display_14  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(2);
    });
    connect(ui->add_user_15 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(0);
    });
    connect(ui->Manage_15 , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(1);
    });
    connect(ui->Display_15  , &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_5->setCurrentIndex(2);
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

appwindow::~appwindow()
{
    if (m_database.isOpen()) {
        m_database.close();
    }
    delete ui;
}

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
