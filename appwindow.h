#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QDialog>
#include <QFile>
#include <QFontDatabase>
#include <QDebug>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "docking.h"

namespace Ui {
class appwindow;
}

class appwindow : public QDialog
{
    Q_OBJECT

public:
    explicit appwindow(QWidget *parent = nullptr);
    ~appwindow();

private slots:
    void on_CreateDocking_clicked();

private:
    Ui::appwindow *ui;
    Docking dockingManager;
};

#endif // APPWINDOW_H
