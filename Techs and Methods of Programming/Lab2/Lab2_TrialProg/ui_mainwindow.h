/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *le_surname;
    QLineEdit *le_name;
    QLineEdit *Title;
    QLineEdit *le_surname_title;
    QLineEdit *le_name_title;
    QPushButton *pb_submit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(299, 189);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        le_surname = new QLineEdit(centralwidget);
        le_surname->setObjectName(QString::fromUtf8("le_surname"));
        le_surname->setGeometry(QRect(130, 60, 151, 20));
        le_name = new QLineEdit(centralwidget);
        le_name->setObjectName(QString::fromUtf8("le_name"));
        le_name->setGeometry(QRect(130, 100, 151, 20));
        Title = new QLineEdit(centralwidget);
        Title->setObjectName(QString::fromUtf8("Title"));
        Title->setEnabled(false);
        Title->setGeometry(QRect(20, 10, 261, 31));
        QFont font;
        font.setPointSize(16);
        font.setBold(false);
        font.setWeight(50);
        Title->setFont(font);
        Title->setStyleSheet(QString::fromUtf8("border : 0px;\n"
"background-color: rgba(0,0,0,0);\n"
"color: black;"));
        le_surname_title = new QLineEdit(centralwidget);
        le_surname_title->setObjectName(QString::fromUtf8("le_surname_title"));
        le_surname_title->setEnabled(false);
        le_surname_title->setGeometry(QRect(10, 60, 91, 20));
        le_surname_title->setStyleSheet(QString::fromUtf8("border : 0px;\n"
"background-color: rgba(0,0,0,0);\n"
"color: black;"));
        le_name_title = new QLineEdit(centralwidget);
        le_name_title->setObjectName(QString::fromUtf8("le_name_title"));
        le_name_title->setEnabled(false);
        le_name_title->setGeometry(QRect(10, 100, 91, 20));
        le_name_title->setStyleSheet(QString::fromUtf8("border : 0px;\n"
"background-color: rgba(0,0,0,0);\n"
"color: black;"));
        pb_submit = new QPushButton(centralwidget);
        pb_submit->setObjectName(QString::fromUtf8("pb_submit"));
        pb_submit->setEnabled(true);
        pb_submit->setGeometry(QRect(70, 150, 151, 23));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Title->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\264\320\260\320\275\320\275\321\213\320\265 \320\260\320\272\320\272\320\260\321\203\320\275\321\202\320\260", nullptr));
        le_surname_title->setText(QCoreApplication::translate("MainWindow", "\320\244\320\260\320\274\320\270\320\273\320\270\321\217*", nullptr));
        le_name_title->setText(QCoreApplication::translate("MainWindow", "\320\230\320\274\321\217*", nullptr));
        pb_submit->setText(QCoreApplication::translate("MainWindow", "\320\222\320\276\320\271\321\202\320\270/\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
#if QT_CONFIG(shortcut)
        pb_submit->setShortcut(QCoreApplication::translate("MainWindow", "Return", nullptr));
#endif // QT_CONFIG(shortcut)
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
