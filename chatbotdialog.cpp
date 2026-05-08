#include "chatbotdialog.h"
#include "ui_chatbotdialog.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QStringList>

#include <QKeyEvent>
#include <QMouseEvent>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QTimer>
#include <QScrollBar>
#include <QApplication>

// ─────────────────────────────────────────────
//  Constructor / Destructor
// ─────────────────────────────────────────────
ChatbotDialog::ChatbotDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::chatbotdialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);

    if (parent) {
        QRect parentRect = parent->geometry();
        int x = parentRect.x() + (parentRect.width()  - width())  / 2;
        int y = parentRect.y() + (parentRect.height() - height()) / 2;
        move(x, y);
    }

    connect(ui->closeChatBtn, &QPushButton::clicked, this, &ChatbotDialog::hide);
    connect(ui->minimizeBtn,  &QPushButton::clicked, this, &ChatbotDialog::hide);
    connect(ui->sendBtn,      &QPushButton::clicked, this, &ChatbotDialog::onSendClicked);

    ui->messageInput->installEventFilter(this);

    connect(ui->chip1, &QPushButton::clicked, this, &ChatbotDialog::onChip1Clicked);
    connect(ui->chip2, &QPushButton::clicked, this, &ChatbotDialog::onChip2Clicked);
    connect(ui->chip3, &QPushButton::clicked, this, &ChatbotDialog::onChip3Clicked);

    addMessage("Hello! I'm your Harbor Assistant ⚓\n"
               "Ask me about docks, boats, fish stock, users, or companies.\n"
               "Try: \"low stock\", \"available docks\", \"boats at sea\", \"active companies\"", false);
}

ChatbotDialog::~ChatbotDialog()
{
    delete ui;
}

// ─────────────────────────────────────────────
//  Drag to move
// ─────────────────────────────────────────────
void ChatbotDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && event->pos().y() <= 60) {
        m_dragging   = true;
        m_dragOffset = event->globalPosition().toPoint() - frameGeometry().topLeft();
    }
    QDialog::mousePressEvent(event);
}

void ChatbotDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (m_dragging && (event->buttons() & Qt::LeftButton))
        move(event->globalPosition().toPoint() - m_dragOffset);
    QDialog::mouseMoveEvent(event);
}

void ChatbotDialog::mouseReleaseEvent(QMouseEvent *event)
{
    m_dragging = false;
    QDialog::mouseReleaseEvent(event);
}

// ─────────────────────────────────────────────
//  Enter key support
// ─────────────────────────────────────────────
bool ChatbotDialog::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->messageInput && event->type() == QEvent::KeyPress) {
        QKeyEvent *key = static_cast<QKeyEvent *>(event);
        if (key->key() == Qt::Key_Return || key->key() == Qt::Key_Enter) {
            onSendClicked();
            return true;
        }
    }
    return QDialog::eventFilter(obj, event);
}

// ─────────────────────────────────────────────
//   Call Ollama ai
// ─────────────────────────────────────────────
void ChatbotDialog::callOllama(const QString &input)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // Put model in query string (common Ollama pattern) and send JSON body
    QUrl url("http://localhost:11434/api/generate");
    QUrlQuery q;
    q.addQueryItem("model", "llama3");
    url.setQuery(q);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    // Provide clear system/context and the user message
    json["prompt"] =
        "You are a helpful harbor assistant for a fishing port system.\n"
        "Answer concisely and use friendly emoji when helpful.\n"
        "You have access to information about boats, docks, fish stock, users, and companies.\n\n"
        "User: " + input + "\nAssistant:";
    json["stream"] = false;
    json["temperature"] = 0.2;
    json["max_tokens"] = 512;

    // Try a sequence of common Ollama/completion endpoints if one returns 404
    QStringList endpoints = {
        "http://localhost:11434/api/generate?model=llama3",
        "http://localhost:11434/api/generate",
        "http://localhost:11434/api/completions",
        "http://localhost:11434/v1/completions"
    };

    std::function<void(int)> doRequest;
    doRequest = [=](int idx) mutable {
        if (idx >= endpoints.size()) {
            addMessage("Error: All endpoints tried and returned errors.", false);
            return;
        }

        QUrl u(endpoints[idx]);
        QNetworkRequest r(u);
        r.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        // include model in body too for endpoints that expect it there
        QJsonObject body = json;
        body["model"] = "llama3";

        QNetworkReply *rep = manager->post(r, QJsonDocument(body).toJson());

        connect(rep, &QNetworkReply::errorOccurred, this, [=](QNetworkReply::NetworkError){
            QString err = QString("Network error: %1").arg(rep->errorString());
            addMessage(err, false);
            rep->deleteLater();
        });

        connect(rep, &QNetworkReply::finished, this, [=]() mutable {
            int status = rep->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            QByteArray responseData = rep->readAll();

            if (status >= 200 && status < 300) {
                // parse success
                QString aiResponse;

                QJsonParseError parseError;
                QJsonDocument doc = QJsonDocument::fromJson(responseData, &parseError);

                if (parseError.error == QJsonParseError::NoError) {
                    if (doc.isObject()) {
                        QJsonObject obj = doc.object();

                        if (obj.contains("response") && obj["response"].isString())
                            aiResponse = obj["response"].toString();
                        else if (obj.contains("text") && obj["text"].isString())
                            aiResponse = obj["text"].toString();
                        else if (obj.contains("output") && obj["output"].isString())
                            aiResponse = obj["output"].toString();
                        else if (obj.contains("choices") && obj["choices"].isArray()) {
                            QJsonArray choices = obj["choices"].toArray();
                            if (!choices.isEmpty() && choices[0].isObject()) {
                                QJsonObject c0 = choices[0].toObject();
                                if (c0.contains("text")) aiResponse = c0["text"].toString();
                                else if (c0.contains("message") && c0["message"].isObject()) {
                                    QJsonObject msg = c0["message"].toObject();
                                    if (msg.contains("content")) aiResponse = msg["content"].toString();
                                }
                            }
                        } else if (obj.contains("results") && obj["results"].isArray()) {
                            QJsonArray res = obj["results"].toArray();
                            QStringList parts;
                            for (auto v : res) {
                                if (v.isObject()) {
                                    QJsonObject r = v.toObject();
                                    if (r.contains("content") && r["content"].isArray()) {
                                        QJsonArray cont = r["content"].toArray();
                                        for (auto c : cont) if (c.isObject()) {
                                            QJsonObject co = c.toObject();
                                            if (co.contains("text")) parts << co["text"].toString();
                                        }
                                    }
                                }
                            }
                            aiResponse = parts.join("\n");
                        }
                    } else if (doc.isArray()) {
                        QJsonArray arr = doc.array();
                        QStringList parts;
                        for (auto v : arr) {
                            if (v.isString()) parts << v.toString();
                            else if (v.isObject()) {
                                QJsonObject o = v.toObject();
                                if (o.contains("text")) parts << o["text"].toString();
                            }
                        }
                        aiResponse = parts.join("\n");
                    }
                }

                if (aiResponse.trimmed().isEmpty()) {
                    aiResponse = QString::fromUtf8(responseData).trimmed();
                    if (aiResponse.isEmpty()) aiResponse = "(No response from Ollama)";
                }

                addMessage(aiResponse, false);
                rep->deleteLater();
            } else if (status == 404) {
                // try next endpoint
                rep->deleteLater();
                doRequest(idx + 1);
            } else {
                // final error
                QString body = QString::fromUtf8(responseData).trimmed();
                QString msg = QString("HTTP %1: %2").arg(status).arg(body);
                addMessage(msg, false);
                rep->deleteLater();
            }
        });
    };

    doRequest(0);
}



// ─────────────────────────────────────────────
//  Send / Chip handlers
// ─────────────────────────────────────────────
void ChatbotDialog::onSendClicked()
{
    QString text = ui->messageInput->text().trimmed();
    if (text.isEmpty()) return;
    ui->messageInput->clear();
    addMessage(text, true);

    QString reply = processQuery(text.toLower());

    if (reply.contains("I'm not sure")) {
        // fallback to AI
        callOllama(text);
    } else {
        addMessage(reply, false);
    }
}

void ChatbotDialog::onChip1Clicked() {
    addMessage("🐟 Stock levels", true);
    addMessage(queryStock("summary"), false);
}
void ChatbotDialog::onChip2Clicked() {
    addMessage("⚓ Dock status", true);
    addMessage(queryDocks("summary"), false);
}
void ChatbotDialog::onChip3Clicked() {
    addMessage("🚢 Active boats", true);
    addMessage(queryBoats("summary"), false);
}

// ─────────────────────────────────────────────
//  Core keyword dispatcher
// ─────────────────────────────────────────────
QString ChatbotDialog::processQuery(const QString &input)
{
    // ── Greetings ────────────────────────────────────────
    if (input.contains("hello") || input.contains("hi") ||
        input.contains("hey")   || input.contains("salut") ||
        input.contains("bonjour"))
        return "Hello! 👋 How can I help you today?\n"
               "Ask me about stock, docks, boats, users, or companies.";

    if (input.contains("help") || input.contains("what can you"))
        return "I can answer questions about:\n"
               "🐟 Fish stock & products\n"
               "⚓ Dock availability\n"
               "🚢 Boat status & maintenance\n"
               "👤 Users & employees\n"
               "🏢 Companies\n"
               "📊 General summary\n\n"
               "Just ask naturally, e.g. \"how many boats are at sea?\"";

    // ── Summary ──────────────────────────────────────────
    if (input.contains("summary") || input.contains("overview") ||
        input.contains("dashboard") || input.contains("all"))
        return querySummary();

    // ── Stock / Products ─────────────────────────────────
    if (input.contains("stock")   || input.contains("fish")    ||
        input.contains("product") || input.contains("tuna")    ||
        input.contains("sardine") || input.contains("low")     ||
        input.contains("quantity")|| input.contains("price")   ||
        input.contains("inventory"))
        return queryStock(input);

    // ── Docks ────────────────────────────────────────────
    if (input.contains("dock")    || input.contains("port")    ||
        input.contains("berth")   || input.contains("slip")    ||
        input.contains("available")|| input.contains("occupied") ||
        input.contains("capacity"))
        return queryDocks(input);

    // ── Boats ────────────────────────────────────────────
    if (input.contains("boat")    || input.contains("vessel")  ||
        input.contains("ship")    || input.contains("sea")     ||
        input.contains("sailing") || input.contains("maintenance") ||
        input.contains("repair")  || input.contains("trip")    ||
        input.contains("docked"))
        return queryBoats(input);

    // ── Users ────────────────────────────────────────────
    if (input.contains("user")    || input.contains("employee") ||
        input.contains("staff")   || input.contains("admin")    ||
        input.contains("manager") || input.contains("salary")   ||
        input.contains("shift")   || input.contains("worker"))
        return queryUsers(input);

    // ── Companies ────────────────────────────────────────
    if (input.contains("compan")  || input.contains("client")  ||
        input.contains("customer")|| input.contains("partner")  ||
        input.contains("active")  || input.contains("inactive") ||
        input.contains("carrefour"))
        return queryCompanies(input);

    // ── Fallback ─────────────────────────────────────────
    return "🤔 I'm not sure what you mean. Try asking about:\n"
           "• \"low stock products\"\n"
           "• \"available docks\"\n"
           "• \"boats at sea\"\n"
           "• \"how many users\"\n"
           "• \"inactive companies\"\n"
           "• \"summary\"";
}

// ─────────────────────────────────────────────
//  Summary — all tables at a glance
// ─────────────────────────────────────────────
QString ChatbotDialog::querySummary()
{
    QString result = "📊 Harbor Summary\n";
    result += "─────────────────\n";

    QSqlQuery q;

    // Products
    q.exec("SELECT COUNT(*) FROM SMARTFISH.PRODUCTS");
    int prodTotal = q.next() ? q.value(0).toInt() : 0;
    q.exec("SELECT COUNT(*) FROM SMARTFISH.PRODUCTS WHERE QUANTITY < 30");
    int prodLow = q.next() ? q.value(0).toInt() : 0;
    result += QString("🐟 Products: %1 total, %2 low stock\n").arg(prodTotal).arg(prodLow);

    // Docks
    q.exec("SELECT COUNT(*) FROM SMARTFISH.DOCKING");
    int dockTotal = q.next() ? q.value(0).toInt() : 0;
    q.exec("SELECT COUNT(*) FROM SMARTFISH.DOCKING WHERE STATUS = 'Available'");
    int dockFree = q.next() ? q.value(0).toInt() : 0;
    result += QString("⚓ Docks: %1 total, %2 available\n").arg(dockTotal).arg(dockFree);

    // Boats
    q.exec("SELECT COUNT(*) FROM SMARTFISH.BOAT");
    int boatTotal = q.next() ? q.value(0).toInt() : 0;
    q.exec("SELECT COUNT(*) FROM SMARTFISH.BOAT WHERE STATUS = 0");
    int boatSea = q.next() ? q.value(0).toInt() : 0;
    result += QString("🚢 Boats: %1 total, %2 at sea\n").arg(boatTotal).arg(boatSea);

    // Users
    q.exec("SELECT COUNT(*) FROM SMARTFISH.USERS");
    int userTotal = q.next() ? q.value(0).toInt() : 0;
    result += QString("👤 Users: %1\n").arg(userTotal);

    // Companies
    q.exec("SELECT COUNT(*) FROM SMARTFISH.COMPANIES");
    int compTotal = q.next() ? q.value(0).toInt() : 0;
    q.exec("SELECT COUNT(*) FROM SMARTFISH.COMPANIES WHERE STATUS = 'ACTIVE'");
    int compActive = q.next() ? q.value(0).toInt() : 0;
    result += QString("🏢 Companies: %1 total, %2 active\n").arg(compTotal).arg(compActive);

    return result.trimmed();
}

// ─────────────────────────────────────────────
//  Stock / Products
// ─────────────────────────────────────────────
QString ChatbotDialog::queryStock(const QString &input)
{
    QSqlQuery q;

    // Count
    if (input.contains("how many") || input.contains("count") || input.contains("total")) {
        q.exec("SELECT COUNT(*) FROM SMARTFISH.PRODUCTS");
        if (q.next())
            return QString("📦 %1 products in the system.").arg(q.value(0).toInt());
    }

    // Low stock
    if (input.contains("low") || input.contains("running out") || input.contains("shortage")) {
        q.exec("SELECT TYPE, QUANTITY FROM SMARTFISH.PRODUCTS WHERE QUANTITY < 30 ORDER BY QUANTITY ASC");
        if (!q.next()) return "✅ All products have sufficient stock (above 30 units).";
        QString result = "⚠️ Low stock (< 30 units):\n";
        do {
            result += QString("• %1 — %2 units\n")
                          .arg(q.value("TYPE").toString())
                          .arg(q.value("QUANTITY").toInt());
        } while (q.next());
        return result.trimmed();
    }

    // Price
    if (input.contains("price") || input.contains("cost") || input.contains("expensive")) {
        q.exec("SELECT TYPE, PRICE FROM SMARTFISH.PRODUCTS ORDER BY PRICE DESC");
        if (!q.next()) return "No price data found.";
        QString result = "💰 Products by price:\n";
        int c = 0;
        do {
            result += QString("• %1 — %2 TND\n")
                          .arg(q.value("TYPE").toString())
                          .arg(q.value("PRICE").toDouble(), 0, 'f', 2);
        } while (q.next() && ++c < 8);
        return result.trimmed();
    }

    // Status breakdown
    if (input.contains("status") || input.contains("sold") || input.contains("available")) {
        q.exec("SELECT STATUS, COUNT(*) AS CNT FROM SMARTFISH.PRODUCTS GROUP BY STATUS");
        QString result = "📊 Products by status:\n";
        while (q.next())
            result += QString("• %1: %2\n")
                          .arg(q.value("STATUS").toString())
                          .arg(q.value("CNT").toInt());
        return result.trimmed();
    }

    // Default — full list
    q.exec("SELECT TYPE, STATUS, QUANTITY, PRICE FROM SMARTFISH.PRODUCTS ORDER BY PRODUCTID DESC");
    if (!q.next()) return "No products found in the database.";
    QString result = "🐟 Products:\n";
    int count = 0;
    do {
        result += QString("• %1 | %2 | Qty: %3 | %4 TND\n")
                      .arg(q.value("TYPE").toString())
                      .arg(q.value("STATUS").toString())
                      .arg(q.value("QUANTITY").toInt())
                      .arg(q.value("PRICE").toDouble(), 0, 'f', 2);
        count++;
    } while (q.next() && count < 10);
    return result.trimmed();
}

// ─────────────────────────────────────────────
//  Docks
// ─────────────────────────────────────────────
QString ChatbotDialog::queryDocks(const QString &input)
{
    QSqlQuery q;

    if (input.contains("available") || input.contains("free")) {
        q.exec("SELECT COUNT(*) FROM SMARTFISH.DOCKING WHERE STATUS = 'Available'");
        if (q.next())
            return QString("✅ %1 dock(s) currently available.").arg(q.value(0).toInt());
    }

    if (input.contains("occupied") || input.contains("full") || input.contains("taken")) {
        q.exec("SELECT COUNT(*) FROM SMARTFISH.DOCKING WHERE STATUS = 'Occupied'");
        if (q.next())
            return QString("🔴 %1 dock(s) currently occupied.").arg(q.value(0).toInt());
    }

    if (input.contains("how many") || input.contains("count") || input.contains("total")) {
        q.exec("SELECT COUNT(*) FROM SMARTFISH.DOCKING");
        if (q.next())
            return QString("⚓ %1 docks registered in total.").arg(q.value(0).toInt());
    }

    if (input.contains("capacity")) {
        q.exec("SELECT DOCKID, LOCATION, CAPACITY, STATUS FROM SMARTFISH.DOCKING ORDER BY CAPACITY DESC");
        if (!q.next()) return "No dock capacity data found.";
        QString result = "⚓ Dock capacities:\n";
        do {
            result += QString("• Dock #%1 | %2 | Cap: %3 | %4\n")
                          .arg(q.value("DOCKID").toInt())
                          .arg(q.value("LOCATION").toString())
                          .arg(q.value("CAPACITY").toString())
                          .arg(q.value("STATUS").toString());
        } while (q.next());
        return result.trimmed();
    }

    // Default — full list
    q.exec("SELECT DOCKID, LOCATION, STATUS, CAPACITY FROM SMARTFISH.DOCKING ORDER BY DOCKID");
    if (!q.next()) return "No docking stations found in the database.";
    QString result = "⚓ Docking stations:\n";
    do {
        result += QString("• Dock #%1 | %2 | %3 | Cap: %4\n")
                      .arg(q.value("DOCKID").toInt())
                      .arg(q.value("LOCATION").toString())
                      .arg(q.value("STATUS").toString())
                      .arg(q.value("CAPACITY").toString());
    } while (q.next());
    return result.trimmed();
}

// ─────────────────────────────────────────────
//  Boats
// ─────────────────────────────────────────────
QString ChatbotDialog::queryBoats(const QString &input)
{
    QSqlQuery q;

    if (input.contains("sea") || input.contains("outside") || input.contains("sailing")) {
        q.exec("SELECT BOATID, OWNERNAME, TYPE FROM SMARTFISH.BOAT WHERE STATUS = 0");
        if (!q.next()) return "🚢 No boats currently at sea.";
        QString result = "🌊 Boats at sea:\n";
        do {
            result += QString("• #%1 | %2 | %3\n")
                          .arg(q.value("BOATID").toInt())
                          .arg(q.value("OWNERNAME").toString())
                          .arg(q.value("TYPE").toString());
        } while (q.next());
        return result.trimmed();
    }

    if (input.contains("docked") || input.contains("inside") || input.contains("port")) {
        q.exec("SELECT BOATID, OWNERNAME, TYPE FROM SMARTFISH.BOAT WHERE STATUS = 1");
        if (!q.next()) return "⚓ No boats currently docked.";
        QString result = "⚓ Boats in port:\n";
        do {
            result += QString("• #%1 | %2 | %3\n")
                          .arg(q.value("BOATID").toInt())
                          .arg(q.value("OWNERNAME").toString())
                          .arg(q.value("TYPE").toString());
        } while (q.next());
        return result.trimmed();
    }

    if (input.contains("maintenance") || input.contains("repair")) {
        q.exec("SELECT OWNERNAME, TYPE, LASTMAINTENANCEDATE FROM SMARTFISH.BOAT ORDER BY LASTMAINTENANCEDATE ASC");
        if (!q.next()) return "No maintenance records found.";
        QString result = "🔧 Boats by last maintenance (oldest first):\n";
        int c = 0;
        do {
            result += QString("• %1 (%2) — Last: %3\n")
                          .arg(q.value("OWNERNAME").toString())
                          .arg(q.value("TYPE").toString())
                          .arg(q.value("LASTMAINTENANCEDATE").toString());
        } while (q.next() && ++c < 6);
        return result.trimmed();
    }

    if (input.contains("trip") || input.contains("fish caught")) {
        q.exec("SELECT OWNERNAME, TOTALTRIPS, TOTALFISH FROM SMARTFISH.BOAT ORDER BY TOTALFISH DESC");
        if (!q.next()) return "No trip data found.";
        QString result = "📈 Boat performance:\n";
        do {
            result += QString("• %1 | Trips: %2 | Fish: %3\n")
                          .arg(q.value("OWNERNAME").toString())
                          .arg(q.value("TOTALTRIPS").toInt())
                          .arg(q.value("TOTALFISH").toInt());
        } while (q.next());
        return result.trimmed();
    }

    if (input.contains("how many") || input.contains("count") || input.contains("total")) {
        q.exec("SELECT COUNT(*) FROM SMARTFISH.BOAT");
        if (q.next())
            return QString("🚢 %1 boats registered.").arg(q.value(0).toInt());
    }

    // Default — full list
    q.exec("SELECT BOATID, OWNERNAME, SIZEBOAT, STATUS, TYPE, TOTALTRIPS, TOTALFISH FROM SMARTFISH.BOAT ORDER BY BOATID");
    if (!q.next()) return "No boats found in the database.";
    QString result = "🚢 All boats:\n";
    do {
        QString st = q.value("STATUS").toInt() == 1 ? "In Port" : "At Sea";
        result += QString("• #%1 | %2 | %3 | %4 | Trips:%5 | Fish:%6\n")
                      .arg(q.value("BOATID").toInt())
                      .arg(q.value("OWNERNAME").toString())
                      .arg(q.value("TYPE").toString())
                      .arg(st)
                      .arg(q.value("TOTALTRIPS").toInt())
                      .arg(q.value("TOTALFISH").toInt());
    } while (q.next());
    return result.trimmed();
}

// ─────────────────────────────────────────────
//  Users
// ─────────────────────────────────────────────
QString ChatbotDialog::queryUsers(const QString &input)
{
    QSqlQuery q;

    if (input.contains("how many") || input.contains("count") || input.contains("total")) {
        q.exec("SELECT COUNT(*) FROM SMARTFISH.USERS");
        if (q.next())
            return QString("👤 %1 users in the system.").arg(q.value(0).toInt());
    }

    if (input.contains("role") || input.contains("admin") ||
        input.contains("manager") || input.contains("employee")) {
        q.exec("SELECT ROLE, COUNT(*) AS CNT FROM SMARTFISH.USERS GROUP BY ROLE ORDER BY CNT DESC");
        QString result = "👥 Users by role:\n";
        while (q.next())
            result += QString("• %1: %2\n")
                          .arg(q.value("ROLE").toString())
                          .arg(q.value("CNT").toInt());
        return result.trimmed();
    }

    if (input.contains("salary")) {
        q.exec("SELECT FIRST_NAME, LAST_NAME, SALARY FROM SMARTFISH.USERS ORDER BY SALARY DESC");
        if (!q.next()) return "No salary data found.";
        QString result = "💰 Salaries:\n";
        do {
            result += QString("• %1 %2 — %3 TND\n")
                          .arg(q.value("FIRST_NAME").toString())
                          .arg(q.value("LAST_NAME").toString())
                          .arg(q.value("SALARY").toDouble(), 0, 'f', 0);
        } while (q.next());
        return result.trimmed();
    }

    // Default — full list
    q.exec("SELECT USERID, FIRST_NAME, LAST_NAME, ROLE, EMAIL FROM SMARTFISH.USERS ORDER BY USERID");
    if (!q.next()) return "No users found in the database.";
    QString result = "👤 Users:\n";
    do {
        result += QString("• #%1 | %2 %3 | %4 | %5\n")
                      .arg(q.value("USERID").toInt())
                      .arg(q.value("FIRST_NAME").toString())
                      .arg(q.value("LAST_NAME").toString())
                      .arg(q.value("ROLE").toString())
                      .arg(q.value("EMAIL").toString());
    } while (q.next());
    return result.trimmed();
}

// ─────────────────────────────────────────────
//  Companies
// ─────────────────────────────────────────────
QString ChatbotDialog::queryCompanies(const QString &input)
{
    QSqlQuery q;

    if (input.contains("active") && !input.contains("inactive")) {
        q.exec("SELECT NAME, LOCATION, PREFERRED_FISH FROM SMARTFISH.COMPANIES WHERE STATUS = 'ACTIVE'");
        if (!q.next()) return "No active companies found.";
        QString result = "✅ Active companies:\n";
        do {
            result += QString("• %1 | %2 | Prefers: %3\n")
                          .arg(q.value("NAME").toString())
                          .arg(q.value("LOCATION").toString())
                          .arg(q.value("PREFERRED_FISH").toString());
        } while (q.next());
        return result.trimmed();
    }

    if (input.contains("inactive")) {
        q.exec("SELECT NAME, EMAIL, LOCATION FROM SMARTFISH.COMPANIES WHERE STATUS = 'INACTIVE'");
        if (!q.next()) return "✅ No inactive companies — all partners are active!";
        QString result = "🔴 Inactive companies:\n";
        do {
            result += QString("• %1 | %2 | %3\n")
                          .arg(q.value("NAME").toString())
                          .arg(q.value("LOCATION").toString())
                          .arg(q.value("EMAIL").toString());
        } while (q.next());
        return result.trimmed();
    }

    if (input.contains("how many") || input.contains("count") || input.contains("total")) {
        q.exec("SELECT COUNT(*) FROM SMARTFISH.COMPANIES");
        if (q.next())
            return QString("🏢 %1 companies registered.").arg(q.value(0).toInt());
    }

    if (input.contains("fish") || input.contains("prefer") || input.contains("tuna") ||
        input.contains("sardine")) {
        q.exec("SELECT PREFERRED_FISH, COUNT(*) AS CNT FROM SMARTFISH.COMPANIES GROUP BY PREFERRED_FISH ORDER BY CNT DESC");
        QString result = "🐟 Companies by preferred fish:\n";
        while (q.next())
            result += QString("• %1: %2 compan%3\n")
                          .arg(q.value("PREFERRED_FISH").toString())
                          .arg(q.value("CNT").toInt())
                          .arg(q.value("CNT").toInt() == 1 ? "y" : "ies");
        return result.trimmed();
    }

    // Default — full list
    q.exec("SELECT NAME, LOCATION, PREFERRED_FISH, STATUS FROM SMARTFISH.COMPANIES ORDER BY COMPANY_ID");
    if (!q.next()) return "No companies found in the database.";
    QString result = "🏢 Companies:\n";
    do {
        result += QString("• %1 | %2 | Prefers: %3 | %4\n")
                      .arg(q.value("NAME").toString())
                      .arg(q.value("LOCATION").toString())
                      .arg(q.value("PREFERRED_FISH").toString())
                      .arg(q.value("STATUS").toString());
    } while (q.next());
    return result.trimmed();
}

// ─────────────────────────────────────────────
//  UI helpers
// ─────────────────────────────────────────────
void ChatbotDialog::addMessage(const QString &text, bool isUser)
{
    QLabel *bubble = new QLabel(text);
    bubble->setWordWrap(true);
    bubble->setMaximumWidth(270);
    bubble->setTextInteractionFlags(Qt::TextSelectableByMouse);

    if (isUser) {
        bubble->setStyleSheet(
            "background-color: #2EC4B6;"
            "color: #0A2540;"
            "border-radius: 14px;"
            "padding: 10px 13px;"
            "font-size: 13px;"
            "font-weight: 500;"
            );
    } else {
        bubble->setStyleSheet(
            "background-color: #0D3060;"
            "color: #C8E0F4;"
            "border: 1px solid rgba(46,196,182,0.2);"
            "border-radius: 14px;"
            "padding: 10px 13px;"
            "font-size: 13px;"
            );
    }

    QHBoxLayout *row = new QHBoxLayout();
    row->setContentsMargins(0, 0, 0, 0);
    if (isUser) {
        row->addStretch();
        row->addWidget(bubble);
    } else {
        row->addWidget(bubble);
        row->addStretch();
    }

    int idx = ui->messagesLayout->count() - 1;
    ui->messagesLayout->insertLayout(idx, row);
    scrollToBottom();
}

void ChatbotDialog::scrollToBottom()
{
    QTimer::singleShot(50, this, [this]() {
        ui->chatScrollArea->verticalScrollBar()->setValue(
            ui->chatScrollArea->verticalScrollBar()->maximum()
            );
    });
}
