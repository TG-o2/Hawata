#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QDialog>

namespace Ui {
class appwindow;
}

class appwindow : public QDialog
{
    Q_OBJECT

public:
    explicit appwindow(QWidget *parent = nullptr);
    ~appwindow();


private:
    Ui::appwindow *ui;
};

#endif // APPWINDOW_H
