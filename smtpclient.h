#ifndef SMTPCLIENT_H
#define SMTPCLIENT_H

#include <QObject>
#include <QSslSocket>
#include <QString>
#include <QByteArray>

class SmtpClient : public QObject
{
    Q_OBJECT
public:
    explicit SmtpClient(const QString &host, int port, QObject *parent = nullptr);

    void setUsername(const QString &username);
    void setPassword(const QString &password);
    void sendMail(const QString &from, const QString &to,
                  const QString &subject, const QString &body);

signals:
    void mailSent(bool success, const QString &error);

private slots:
    void onConnected();
    void onReadyRead();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);

private:
    QSslSocket *socket;
    QString host;
    int port;
    QString username;
    QString password;
    bool waitingForResponse;
    QString responseBuffer;
    int state;

    QString fromAddress;
    QString toAddress;
    QString mailSubject;
    QString mailBody;

    void sendCommand(const QString &cmd);
    void processResponse();
    QString base64Encode(const QString &str);

    bool mailSentEmitted;
};

#endif // SMTPCLIENT_H
