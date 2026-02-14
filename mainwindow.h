#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QFile>
#include <QFontDatabase>
#include <QDebug>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();  // <-- declared, so you must define it

public slots:
    //opens a new window :
    void openSignupPage();
private slots:
    void on_logo_linkActivated(const QString &link);

    void on_Exit_clicked();
    void on_create_acc_linkActivated(const QString &link);
    void on_Create_clicked();

    void on_Sign_in_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
