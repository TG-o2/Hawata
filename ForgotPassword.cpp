#include <QTcpSocket>
#include <QSslSocket>

void ForgotPassword::sendEmail(QString to, QString password)
{
    QString from = "yourapp@gmail.com";
    QString appPassword = "your_app_password"; // from Google

    QSslSocket *socket = new QSslSocket(this);

    socket->connectToHostEncrypted("smtp.gmail.com", 465);

    if (!socket->waitForConnected()) {
        qDebug() << "Connection failed";
        return;
    }

    auto send = [&](QString cmd) {
        socket->write(cmd.toUtf8() + "\r\n");
        socket->waitForBytesWritten();
        socket->waitForReadyRead();
        qDebug() << socket->readAll();
    };

    send("EHLO localhost");
    send("AUTH LOGIN");
    send(QString(from.toUtf8().toBase64()));
    send(QString(appPassword.toUtf8().toBase64()));
    send("MAIL FROM:<" + from + ">");
    send("RCPT TO:<" + to + ">");
    send("DATA");

    QString message =
        "Subject: Password Recovery\r\n"
        "\r\n"
        "Your password is: " + password + "\r\n";

    send(message + "\r\n.");
    send("QUIT");

    socket->disconnectFromHost();
}
