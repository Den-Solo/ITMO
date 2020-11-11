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
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *p1_path;
    QLineEdit *le_title_folder;
    QLineEdit *le_file_path;
    QLineEdit *le_title_path;
    QPushButton *pb_search;
    QWidget *p2_addons;
    QLineEdit *le_add_choice;
    QCheckBox *cb_create_desktop_sc;
    QLineEdit *le_title_type;
    QRadioButton *rb_launches;
    QRadioButton *rb_time;
    QCheckBox *cb_create_startup_sc;
    QWidget *p3_install;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QTextEdit *te_path;
    QGroupBox *gb_bottom;
    QPushButton *pb_cancel;
    QPushButton *pb_next;
    QPushButton *pb_back;
    QButtonGroup *LimitType;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(453, 342);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 451, 261));
        p1_path = new QWidget();
        p1_path->setObjectName(QString::fromUtf8("p1_path"));
        le_title_folder = new QLineEdit(p1_path);
        le_title_folder->setObjectName(QString::fromUtf8("le_title_folder"));
        le_title_folder->setEnabled(false);
        le_title_folder->setGeometry(QRect(30, 20, 181, 20));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        le_title_folder->setFont(font);
        le_title_folder->setStyleSheet(QString::fromUtf8("border: 0px;\n"
"background-color: rgba(0,0,0,0);\n"
"color:black;"));
        le_file_path = new QLineEdit(p1_path);
        le_file_path->setObjectName(QString::fromUtf8("le_file_path"));
        le_file_path->setGeometry(QRect(30, 80, 391, 20));
        le_title_path = new QLineEdit(p1_path);
        le_title_path->setObjectName(QString::fromUtf8("le_title_path"));
        le_title_path->setEnabled(false);
        le_title_path->setGeometry(QRect(30, 50, 113, 20));
        le_title_path->setStyleSheet(QString::fromUtf8("border: 0px;\n"
"background-color: rgba(0,0,0,0);\n"
"color:black;"));
        pb_search = new QPushButton(p1_path);
        pb_search->setObjectName(QString::fromUtf8("pb_search"));
        pb_search->setGeometry(QRect(350, 110, 71, 21));
        stackedWidget->addWidget(p1_path);
        p2_addons = new QWidget();
        p2_addons->setObjectName(QString::fromUtf8("p2_addons"));
        le_add_choice = new QLineEdit(p2_addons);
        le_add_choice->setObjectName(QString::fromUtf8("le_add_choice"));
        le_add_choice->setEnabled(false);
        le_add_choice->setGeometry(QRect(20, 150, 221, 20));
        le_add_choice->setFont(font);
        le_add_choice->setStyleSheet(QString::fromUtf8("border: 0px;\n"
"background-color: rgba(0,0,0,0);\n"
"color:black;"));
        cb_create_desktop_sc = new QCheckBox(p2_addons);
        cb_create_desktop_sc->setObjectName(QString::fromUtf8("cb_create_desktop_sc"));
        cb_create_desktop_sc->setGeometry(QRect(20, 200, 201, 17));
        le_title_type = new QLineEdit(p2_addons);
        le_title_type->setObjectName(QString::fromUtf8("le_title_type"));
        le_title_type->setEnabled(false);
        le_title_type->setGeometry(QRect(20, 20, 113, 20));
        le_title_type->setFont(font);
        le_title_type->setStyleSheet(QString::fromUtf8("border: 0px;\n"
"background-color: rgba(0,0,0,0);\n"
"color:black;"));
        rb_launches = new QRadioButton(p2_addons);
        LimitType = new QButtonGroup(MainWindow);
        LimitType->setObjectName(QString::fromUtf8("LimitType"));
        LimitType->addButton(rb_launches);
        rb_launches->setObjectName(QString::fromUtf8("rb_launches"));
        rb_launches->setGeometry(QRect(20, 60, 191, 17));
        rb_launches->setChecked(true);
        rb_time = new QRadioButton(p2_addons);
        LimitType->addButton(rb_time);
        rb_time->setObjectName(QString::fromUtf8("rb_time"));
        rb_time->setGeometry(QRect(20, 90, 181, 17));
        rb_time->setChecked(false);
        cb_create_startup_sc = new QCheckBox(p2_addons);
        cb_create_startup_sc->setObjectName(QString::fromUtf8("cb_create_startup_sc"));
        cb_create_startup_sc->setGeometry(QRect(20, 230, 191, 17));
        stackedWidget->addWidget(p2_addons);
        p3_install = new QWidget();
        p3_install->setObjectName(QString::fromUtf8("p3_install"));
        lineEdit = new QLineEdit(p3_install);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setEnabled(false);
        lineEdit->setGeometry(QRect(30, 30, 151, 20));
        lineEdit->setFont(font);
        lineEdit->setStyleSheet(QString::fromUtf8("border: 0px;\n"
"background-color: rgba(0,0,0,0);\n"
"color:black;"));
        lineEdit_2 = new QLineEdit(p3_install);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setEnabled(false);
        lineEdit_2->setGeometry(QRect(30, 70, 113, 20));
        lineEdit_2->setStyleSheet(QString::fromUtf8("border: 0px;\n"
"background-color: rgba(0,0,0,0);\n"
"color:black;"));
        te_path = new QTextEdit(p3_install);
        te_path->setObjectName(QString::fromUtf8("te_path"));
        te_path->setGeometry(QRect(30, 100, 391, 151));
        stackedWidget->addWidget(p3_install);
        gb_bottom = new QGroupBox(centralwidget);
        gb_bottom->setObjectName(QString::fromUtf8("gb_bottom"));
        gb_bottom->setGeometry(QRect(-10, 280, 471, 71));
        gb_bottom->setStyleSheet(QString::fromUtf8("background-color: gray;"));
        pb_cancel = new QPushButton(gb_bottom);
        pb_cancel->setObjectName(QString::fromUtf8("pb_cancel"));
        pb_cancel->setGeometry(QRect(360, 20, 75, 23));
        pb_cancel->setStyleSheet(QString::fromUtf8("background-color:white;"));
        pb_next = new QPushButton(gb_bottom);
        pb_next->setObjectName(QString::fromUtf8("pb_next"));
        pb_next->setGeometry(QRect(280, 20, 75, 23));
        pb_next->setStyleSheet(QString::fromUtf8("background-color:white;"));
        pb_back = new QPushButton(gb_bottom);
        pb_back->setObjectName(QString::fromUtf8("pb_back"));
        pb_back->setEnabled(false);
        pb_back->setGeometry(QRect(200, 20, 75, 23));
        pb_back->setStyleSheet(QString::fromUtf8("background-color:white;"));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MyInstaller", nullptr));
        le_title_folder->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\320\276\321\200 \320\277\320\260\320\277\320\272\320\270 \321\203\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\270", nullptr));
        le_file_path->setText(QCoreApplication::translate("MainWindow", "C:\\Users\\User\\AppData\\Local\\Programs\\TrialProg", nullptr));
        le_title_path->setText(QCoreApplication::translate("MainWindow", "\320\237\321\203\321\202\321\214:", nullptr));
        pb_search->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\320\267\320\276\321\200", nullptr));
        le_add_choice->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \320\264\320\276\320\277\320\276\320\273\320\275\320\270\321\202\320\265\320\273\321\214\320\275\321\213\320\265 \320\267\320\260\320\264\320\260\321\207\320\270:", nullptr));
        cb_create_desktop_sc->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\267\320\275\320\260\321\207\320\276\320\272 \320\275\320\260 \321\200\320\260\320\261\320\276\321\207\320\265\320\274 \321\201\321\202\320\276\320\273\320\265", nullptr));
        le_title_type->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \320\262\320\265\321\200\321\201\320\270\321\216:", nullptr));
        rb_launches->setText(QCoreApplication::translate("MainWindow", "\320\236\320\263\321\200\320\260\320\275\320\270\321\207\320\265\320\275\320\270\320\265 \320\277\320\276 \321\207\320\270\321\201\320\273\321\203 \320\267\320\260\320\277\321\203\321\201\320\272\320\276\320\262", nullptr));
        rb_time->setText(QCoreApplication::translate("MainWindow", "\320\236\320\263\321\200\320\260\320\275\320\270\321\207\320\265\320\275\320\270\320\265 \320\277\320\276 \320\262\321\200\320\265\320\274\320\265\320\275\320\270", nullptr));
        cb_create_startup_sc->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \321\217\321\200\320\273\321\213\320\272 \320\262 \320\274\320\265\320\275\321\216 \320\277\321\203\321\201\320\272", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "\320\222\321\201\320\265 \320\263\320\276\321\202\320\276\320\262\320\276 \320\272 \321\203\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\265", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("MainWindow", "\320\237\321\203\321\202\321\214:", nullptr));
        gb_bottom->setTitle(QString());
        pb_cancel->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
#if QT_CONFIG(shortcut)
        pb_cancel->setShortcut(QCoreApplication::translate("MainWindow", "Del", nullptr));
#endif // QT_CONFIG(shortcut)
        pb_next->setText(QCoreApplication::translate("MainWindow", "\320\224\320\260\320\273\320\265\320\265", nullptr));
#if QT_CONFIG(shortcut)
        pb_next->setShortcut(QCoreApplication::translate("MainWindow", "Right", nullptr));
#endif // QT_CONFIG(shortcut)
        pb_back->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\260\320\264", nullptr));
#if QT_CONFIG(shortcut)
        pb_back->setShortcut(QCoreApplication::translate("MainWindow", "Left", nullptr));
#endif // QT_CONFIG(shortcut)
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
