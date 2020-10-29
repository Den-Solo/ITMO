#pragma once

#include <QMainWindow>
#include <QMessageBox>

#include <accountmanager.h>
#include <buyorremovedialog.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private slots:
    void on_pb_submit_clicked();

private:
    Ui::MainWindow *ui;
    BuyOrRemoveDialog *BOR_dialog_ { nullptr }; // buy or remove dialog
    AccountManager acc_manager_;
};
