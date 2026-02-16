/********************************************************************************
** Form generated from reading UI file 'createacc.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEACC_H
#define UI_CREATEACC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CreateAcc
{
public:
    QLabel *label_2;
    QPushButton *signup;
    QLabel *label_5;
    QLineEdit *lastNameEdit;
    QLineEdit *passwordEdit;
    QLabel *logo;
    QLineEdit *emailEdit;
    QLabel *label_6;
    QLabel *label_3;
    QPushButton *cancel;
    QLabel *label_4;
    QComboBox *role_option;
    QLabel *label;
    QLineEdit *firstNameEdit;
    QFrame *backgroundFrame;
    QFrame *backgroundFrame1;

    void setupUi(QDialog *CreateAcc)
    {
        if (CreateAcc->objectName().isEmpty())
            CreateAcc->setObjectName("CreateAcc");
        CreateAcc->resize(691, 748);
        label_2 = new QLabel(CreateAcc);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(200, 130, 111, 20));
        signup = new QPushButton(CreateAcc);
        signup->setObjectName("signup");
<<<<<<< Updated upstream
        signup->setGeometry(QRect(220, 690, 93, 29));
=======
        signup->setGeometry(QRect(200, 520, 93, 29));
>>>>>>> Stashed changes
        label_5 = new QLabel(CreateAcc);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(200, 340, 111, 20));
        lastNameEdit = new QLineEdit(CreateAcc);
        lastNameEdit->setObjectName("lastNameEdit");
        lastNameEdit->setGeometry(QRect(200, 230, 251, 31));
        passwordEdit = new QLineEdit(CreateAcc);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setGeometry(QRect(200, 370, 251, 31));
        logo = new QLabel(CreateAcc);
        logo->setObjectName("logo");
<<<<<<< Updated upstream
        logo->setGeometry(QRect(170, 460, 321, 211));
=======
        logo->setGeometry(QRect(390, 420, 61, 51));
>>>>>>> Stashed changes
        logo->setStyleSheet(QString::fromUtf8(""));
        emailEdit = new QLineEdit(CreateAcc);
        emailEdit->setObjectName("emailEdit");
        emailEdit->setGeometry(QRect(200, 300, 251, 31));
        label_6 = new QLabel(CreateAcc);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(280, 420, 111, 20));
        label_3 = new QLabel(CreateAcc);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(200, 200, 111, 20));
        cancel = new QPushButton(CreateAcc);
        cancel->setObjectName("cancel");
<<<<<<< Updated upstream
        cancel->setGeometry(QRect(330, 690, 93, 29));
=======
        cancel->setGeometry(QRect(350, 520, 93, 29));
>>>>>>> Stashed changes
        label_4 = new QLabel(CreateAcc);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(200, 270, 111, 20));
        role_option = new QComboBox(CreateAcc);
        role_option->addItem(QString());
        role_option->addItem(QString());
        role_option->addItem(QString());
        role_option->setObjectName("role_option");
        role_option->setGeometry(QRect(200, 450, 151, 41));
        label = new QLabel(CreateAcc);
        label->setObjectName("label");
        label->setGeometry(QRect(150, 0, 371, 61));
        label->setStyleSheet(QString::fromUtf8("font-family: \"Behove\";\n"
"font-size: 33px;\n"
"    font-weight: bold;\n"
"    color: #0a4c73;"));
        firstNameEdit = new QLineEdit(CreateAcc);
        firstNameEdit->setObjectName("firstNameEdit");
        firstNameEdit->setGeometry(QRect(200, 160, 251, 31));
        backgroundFrame = new QFrame(CreateAcc);
        backgroundFrame->setObjectName("backgroundFrame");
        backgroundFrame->setGeometry(QRect(530, -10, 231, 771));
        backgroundFrame->setFrameShape(QFrame::Shape::StyledPanel);
        backgroundFrame->setFrameShadow(QFrame::Shadow::Raised);
        backgroundFrame1 = new QFrame(CreateAcc);
        backgroundFrame1->setObjectName("backgroundFrame1");
        backgroundFrame1->setGeometry(QRect(-10, -10, 151, 791));
        backgroundFrame1->setFrameShape(QFrame::Shape::StyledPanel);
        backgroundFrame1->setFrameShadow(QFrame::Shadow::Raised);

        retranslateUi(CreateAcc);

        QMetaObject::connectSlotsByName(CreateAcc);
    } // setupUi

    void retranslateUi(QDialog *CreateAcc)
    {
        CreateAcc->setWindowTitle(QCoreApplication::translate("CreateAcc", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("CreateAcc", "First Name:", nullptr));
        signup->setText(QCoreApplication::translate("CreateAcc", "Create", nullptr));
        signup->setProperty("style", QVariant(QCoreApplication::translate("CreateAcc", "success", nullptr)));
        label_5->setText(QCoreApplication::translate("CreateAcc", "Password", nullptr));
        logo->setText(QCoreApplication::translate("CreateAcc", "Picture", nullptr));
        label_6->setText(QCoreApplication::translate("CreateAcc", "Choose Role", nullptr));
        label_3->setText(QCoreApplication::translate("CreateAcc", "Last Name:", nullptr));
        cancel->setText(QCoreApplication::translate("CreateAcc", "Cancel", nullptr));
        cancel->setProperty("style", QVariant(QString()));
        label_4->setText(QCoreApplication::translate("CreateAcc", "Email", nullptr));
        role_option->setItemText(0, QCoreApplication::translate("CreateAcc", "Admin", nullptr));
        role_option->setItemText(1, QCoreApplication::translate("CreateAcc", "Manager", nullptr));
        role_option->setItemText(2, QCoreApplication::translate("CreateAcc", "Employee", nullptr));

        label->setText(QCoreApplication::translate("CreateAcc", "Create an Account!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateAcc: public Ui_CreateAcc {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEACC_H
