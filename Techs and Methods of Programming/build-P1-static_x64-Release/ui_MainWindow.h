/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *PB_Stop;
    QLineEdit *LE_Pswd;
    QLineEdit *LE_EnterPswd;
    QTextEdit *TE_Dir;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(291, 195);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        PB_Stop = new QPushButton(centralwidget);
        PB_Stop->setObjectName(QString::fromUtf8("PB_Stop"));
        PB_Stop->setGeometry(QRect(100, 90, 80, 21));
        LE_Pswd = new QLineEdit(centralwidget);
        LE_Pswd->setObjectName(QString::fromUtf8("LE_Pswd"));
        LE_Pswd->setGeometry(QRect(30, 50, 231, 21));
        LE_EnterPswd = new QLineEdit(centralwidget);
        LE_EnterPswd->setObjectName(QString::fromUtf8("LE_EnterPswd"));
        LE_EnterPswd->setEnabled(true);
        LE_EnterPswd->setGeometry(QRect(30, 20, 231, 21));
        QFont font;
        font.setPointSize(14);
        LE_EnterPswd->setFont(font);
        LE_EnterPswd->setStyleSheet(QString::fromUtf8("background-color: rgba(255,255,255,0);\n"
"border: 0;"));
        LE_EnterPswd->setAlignment(Qt::AlignCenter);
        LE_EnterPswd->setReadOnly(true);
        TE_Dir = new QTextEdit(centralwidget);
        TE_Dir->setObjectName(QString::fromUtf8("TE_Dir"));
        TE_Dir->setGeometry(QRect(0, 130, 291, 61));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "AccessSuperviser", nullptr));
        PB_Stop->setText(QCoreApplication::translate("MainWindow", "Stop Filtering", nullptr));
#if QT_CONFIG(shortcut)
        PB_Stop->setShortcut(QCoreApplication::translate("MainWindow", "Return", nullptr));
#endif // QT_CONFIG(shortcut)
        LE_EnterPswd->setText(QCoreApplication::translate("MainWindow", "Enter Password", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
