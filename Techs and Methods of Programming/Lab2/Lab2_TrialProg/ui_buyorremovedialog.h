/********************************************************************************
** Form generated from reading UI file 'buyorremovedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUYORREMOVEDIALOG_H
#define UI_BUYORREMOVEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_BuyOrRemoveDialog
{
public:
    QLineEdit *le_title_1;
    QLineEdit *le_title_2;
    QPushButton *pb_buy_pro;
    QPushButton *pb_uninstall;

    void setupUi(QDialog *BuyOrRemoveDialog)
    {
        if (BuyOrRemoveDialog->objectName().isEmpty())
            BuyOrRemoveDialog->setObjectName(QString::fromUtf8("BuyOrRemoveDialog"));
        BuyOrRemoveDialog->resize(284, 179);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(BuyOrRemoveDialog->sizePolicy().hasHeightForWidth());
        BuyOrRemoveDialog->setSizePolicy(sizePolicy);
        le_title_1 = new QLineEdit(BuyOrRemoveDialog);
        le_title_1->setObjectName(QString::fromUtf8("le_title_1"));
        le_title_1->setEnabled(false);
        le_title_1->setGeometry(QRect(30, 30, 241, 31));
        QFont font;
        font.setPointSize(14);
        le_title_1->setFont(font);
        le_title_1->setStyleSheet(QString::fromUtf8("color: black;\n"
"background-color: rgba(0,0,0,0);\n"
"border: 0px;"));
        le_title_2 = new QLineEdit(BuyOrRemoveDialog);
        le_title_2->setObjectName(QString::fromUtf8("le_title_2"));
        le_title_2->setEnabled(false);
        le_title_2->setGeometry(QRect(50, 70, 211, 31));
        le_title_2->setFont(font);
        le_title_2->setStyleSheet(QString::fromUtf8("color: black;\n"
"background-color: rgba(0,0,0,0);\n"
"border: 0px;"));
        pb_buy_pro = new QPushButton(BuyOrRemoveDialog);
        pb_buy_pro->setObjectName(QString::fromUtf8("pb_buy_pro"));
        pb_buy_pro->setGeometry(QRect(20, 130, 111, 23));
        pb_uninstall = new QPushButton(BuyOrRemoveDialog);
        pb_uninstall->setObjectName(QString::fromUtf8("pb_uninstall"));
        pb_uninstall->setGeometry(QRect(150, 130, 111, 23));

        retranslateUi(BuyOrRemoveDialog);

        QMetaObject::connectSlotsByName(BuyOrRemoveDialog);
    } // setupUi

    void retranslateUi(QDialog *BuyOrRemoveDialog)
    {
        BuyOrRemoveDialog->setWindowTitle(QCoreApplication::translate("BuyOrRemoveDialog", "Dialog", nullptr));
        le_title_1->setText(QCoreApplication::translate("BuyOrRemoveDialog", "Trial-\320\262\320\265\321\200\321\201\320\270\321\217 \320\267\320\260\320\272\320\276\320\275\321\207\320\270\320\273\320\260\321\201\321\214", nullptr));
        le_title_2->setText(QCoreApplication::translate("BuyOrRemoveDialog", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \320\264\320\265\320\271\321\201\321\202\320\262\320\270\320\265...", nullptr));
        pb_buy_pro->setText(QCoreApplication::translate("BuyOrRemoveDialog", "\320\232\321\203\320\277\320\270\321\202\321\214 Pro", nullptr));
        pb_uninstall->setText(QCoreApplication::translate("BuyOrRemoveDialog", "\320\224\320\265\320\270\320\275\321\201\321\202\320\260\320\273\320\273\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BuyOrRemoveDialog: public Ui_BuyOrRemoveDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUYORREMOVEDIALOG_H
