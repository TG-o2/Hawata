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
    void on_edit_Docking_clicked();
    void on_delete_docking_clicked();
    void on_tabdocking_cellDoubleClicked(int row, int column);
    void on_tabdocking_cellClicked(int row, int column);
    void on_clear_docking_clicked();

private:
    Ui::appwindow *ui;
    Docking dockingManager;
    int selectedDockingId = -1;
    void loadDockingTable();
};

#endif // APPWINDOW_H
