#ifndef CREATEACC_H
#define CREATEACC_H

#include <QDialog>

namespace Ui {
class CreateAcc;
}

class CreateAcc : public QDialog
{
    Q_OBJECT

public:
    explicit CreateAcc(QWidget *parent = nullptr);
    ~CreateAcc();

private slots:
    void on_cancel_clicked();
    void on_signup_clicked();

private:
    Ui::CreateAcc *ui;
};

#endif // CREATEACC_H
