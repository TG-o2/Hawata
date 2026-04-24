#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QSettings>

class Arduino;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool isAutoLoginTriggered() const;
    bool rfidBusy = false;
private slots:
    void on_logo_linkActivated(const QString &link);
    void on_Exit_clicked();
    void on_Sign_in_clicked();
    void on_forgot_password_linkActivated(const QString &link);

private:
    Ui::MainWindow *ui;
    Arduino *arduino;
    bool m_autoLoginTriggered = false;

    void openAppWindow(int userId, const QString &role);
};

#endif // MAINWINDOW_H
