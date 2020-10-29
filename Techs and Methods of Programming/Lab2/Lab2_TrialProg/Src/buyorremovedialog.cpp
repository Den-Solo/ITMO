#include "buyorremovedialog.h"
#include "ui_buyorremovedialog.h"

BuyOrRemoveDialog::BuyOrRemoveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BuyOrRemoveDialog)
{
    ui->setupUi(this);
}

BuyOrRemoveDialog::~BuyOrRemoveDialog()
{
    delete ui;
}

void BuyOrRemoveDialog::on_pb_buy_pro_clicked()
{
    QMessageBox::information(this,"Внимание", "Эту функцию не требовалось реализовать");
    close();
}

void BuyOrRemoveDialog::on_pb_uninstall_clicked()
{
    QString uninstall_path = QString::fromStdWString(WinReg::GetWString(base_key_,reg_uninst_path_,reg_uninst_key_name_));
    if (uninstall_path != "-1")
    {
        QProcess qproc;
        qproc.startDetached(uninstall_path);
    }
    close();
}
