#pragma once

#include "WinRegistry.h"
#include <QDialog>
#include <QMessageBox>
#include <QProcess>

namespace Ui {
class BuyOrRemoveDialog;
}

class BuyOrRemoveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BuyOrRemoveDialog(QWidget *parent = nullptr);
    ~BuyOrRemoveDialog();

private slots:
    void on_pb_buy_pro_clicked();

    void on_pb_uninstall_clicked();

private:
    Ui::BuyOrRemoveDialog *ui;
    const HKEY base_key_ = HKEY_CURRENT_USER;
    const wchar_t reg_uninst_path_[95] = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{AB048DC3-DD4C-4107-8484-31024DEF506E}_is1";
    const wchar_t reg_uninst_key_name_[16] = L"UninstallString";
};

