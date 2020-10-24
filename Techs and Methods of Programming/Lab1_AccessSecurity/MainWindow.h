#pragma once

#include <QCloseEvent>
#include <QDir>
#include <QMainWindow>
#include <QMessageBox>
#include <Windows.h>

#include "PasswordChecker.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow 
{
    Q_OBJECT

public:
    MainWindow(const PasswordChecker& p);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;
private slots:
    void on_PB_Stop_clicked();

private:
    bool CheckPswd();

private:
    Ui::MainWindow* ui;
    const PasswordChecker& pswd_ck;
};
