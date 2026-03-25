#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
private slots:
    void on_logo_linkActivated(const QString &link);

    void on_Exit_clicked();
    void on_create_acc_linkActivated(const QString &link);

    void on_Sign_in_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
