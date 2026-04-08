#include "emailsender.h"
#include <QSslSocket>
#include <QDebug>

EmailSender::EmailSender() {}

bool EmailSender::sendEmail(const QString &to, const QString &subject, const QString &body)
{
    QString from = "tguesmi14@gmail.com";
    QString appPassword = "jvsgfkcxksorludo";

    QSslSocket socket;
    socket.connectToHostEncrypted("smtp.gmail.com", 465);

    if (!socket.waitForConnected()) {
        qDebug() << "Connection failed";
        return false;
    }

    auto send = [&](QString cmd) {
        socket.write(cmd.toUtf8() + "\r\n");
        socket.waitForBytesWritten();
        socket.waitForReadyRead();
        qDebug() << socket.readAll();
    };

    send("EHLO localhost");
    send("AUTH LOGIN");
    send(QString(from.toUtf8().toBase64()));
    send(QString(appPassword.toUtf8().toBase64()));
    send("MAIL FROM:<" + from + ">");
    send("RCPT TO:<" + to + ">");
    send("DATA");

    QString message =
        "Subject: " + subject + "\r\n"
                                "\r\n" +
        body + "\r\n";

    send(message + "\r\n.");
    send("QUIT");

    socket.disconnectFromHost();

    return true;
}
