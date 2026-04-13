#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QSettings>

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

public slots:
private slots:
    void on_logo_linkActivated(const QString &link);

    void on_Exit_clicked();

    void on_Sign_in_clicked();

    void on_forgot_password_linkActivated(const QString &link);

private:
    void openAppWindow(int userId, const QString &role);

    Ui::MainWindow *ui;
    bool m_autoLoginTriggered = false;
};

#endif // MAINWINDOW_H
