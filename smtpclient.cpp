#include "smtpclient.h"
#include <QDebug>
#include <QDateTime>

SmtpClient::SmtpClient(const QString &host, int port, QObject *parent)
    : QObject(parent), host(host), port(port), state(0), waitingForResponse(false), mailSentEmitted(false)
{
    socket = new QSslSocket(this);
    connect(socket, &QSslSocket::connected, this, &SmtpClient::onConnected);
    connect(socket, &QSslSocket::readyRead, this, &SmtpClient::onReadyRead);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QSslSocket::errorOccurred),
            this, &SmtpClient::onErrorOccurred);
}

void SmtpClient::setUsername(const QString &username)
{
    this->username = username;
}

void SmtpClient::setPassword(const QString &password)
{
    this->password = password;
}

void SmtpClient::sendMail(const QString &from, const QString &to,
                          const QString &subject, const QString &body)
{
    fromAddress = from;
    toAddress = to;
    mailSubject = subject;
    mailBody = body;

    qDebug() << "Connecting to SMTP server:" << host << port;
    socket->connectToHostEncrypted(host, port);
}

void SmtpClient::onConnected()
{
    qDebug() << "Connected to SMTP server";
    waitingForResponse = true;
}

void SmtpClient::onReadyRead()
{
    responseBuffer += socket->readAll();
    if (responseBuffer.contains("\r\n")) {
        waitingForResponse = false;
        processResponse();
    }
}

void SmtpClient::sendCommand(const QString &cmd)
{
    qDebug() << "Sending:" << cmd.trimmed();
    socket->write(cmd.toUtf8());
    waitingForResponse = true;
}

QString SmtpClient::base64Encode(const QString &str)
{
    return QString::fromLatin1(str.toUtf8().toBase64());
}

void SmtpClient::processResponse()
{
    if (mailSentEmitted) {
        // Already emitted result, ignore further responses
        responseBuffer.clear();
        return;
    }

    QString response = responseBuffer.trimmed();
    qDebug() << "Response:" << response;

    bool positiveResponse = (response.startsWith("2") || response.startsWith("3"));

    // State machine for SMTP with authentication
    if (state == 0) {
        // Send EHLO after connection
        sendCommand("EHLO localhost\r\n");
        state = 1;
        responseBuffer.clear();
        return;
    }

    if (state == 1) {
        if (positiveResponse) {
            // Start AUTH LOGIN
            sendCommand("AUTH LOGIN\r\n");
            state = 2;
        } else {
            emit mailSent(false, response);
        }
        responseBuffer.clear();
        return;
    }

    if (state == 2) {
        if (positiveResponse) {
            // Send username in base64
            sendCommand(base64Encode(username) + "\r\n");
            state = 3;
        } else {
            emit mailSent(false, response);
        }
        responseBuffer.clear();
        return;
    }

    if (state == 3) {
        if (positiveResponse) {
            // Send password in base64
            sendCommand(base64Encode(password) + "\r\n");
            state = 4;
        } else {
            emit mailSent(false, response);
        }
        responseBuffer.clear();
        return;
    }

    if (state == 4) {
        if (positiveResponse) {
            // Authentication successful, send MAIL FROM
            sendCommand("MAIL FROM:<" + fromAddress + ">\r\n");
            state = 5;
        } else {
            emit mailSent(false, response);
        }
        responseBuffer.clear();
        return;
    }

    if (state == 5) {
        if (positiveResponse) {
            sendCommand("RCPT TO:<" + toAddress + ">\r\n");
            state = 6;
        } else {
            emit mailSent(false, response);
        }
        responseBuffer.clear();
        return;
    }

    if (state == 6) {
        if (positiveResponse) {
            sendCommand("DATA\r\n");
            state = 7;
        } else {
            emit mailSent(false, response);
        }
        responseBuffer.clear();
        return;
    }

    if (state == 7) {
        if (positiveResponse) {
            // Build email with headers
            QString email = QString("From: %1\r\n").arg(fromAddress) +
                            QString("To: %1\r\n").arg(toAddress) +
                            QString("Subject: %1\r\n").arg(mailSubject) +
                            QString("Date: %1\r\n").arg(QDateTime::currentDateTime().toString("ddd, dd MMM yyyy HH:mm:ss +0000")) +
                            "MIME-Version: 1.0\r\n" +
                            "Content-Type: text/plain; charset=UTF-8\r\n" +
                            "Content-Transfer-Encoding: 7bit\r\n\r\n" +
                            mailBody + "\r\n.\r\n";
            sendCommand(email);
            state = 8;
        } else {
            emit mailSent(false, response);
        }
        responseBuffer.clear();
        return;
    }

    if (state == 8) {
        if (positiveResponse) {
            sendCommand("QUIT\r\n");
            state = 9;
        } else {
            emit mailSent(false, response);
        }
        responseBuffer.clear();
        return;
    }

    if (state == 9) {
        if (!mailSentEmitted) {
            mailSentEmitted = true;
            emit mailSent(true, "Email sent successfully");
        }
        socket->disconnectFromHost();
    }

    responseBuffer.clear();
}

void SmtpClient::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError)
    if (!mailSentEmitted) {
        mailSentEmitted = true;
        qDebug() << "Socket error:" << socket->errorString();
        emit mailSent(false, socket->errorString());
    }
}
