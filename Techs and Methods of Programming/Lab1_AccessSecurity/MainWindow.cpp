#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(const PasswordChecker& p)
    : ui(new Ui::MainWindow)
    , pswd_ck(p)
{
    ui->setupUi(this);
    ui->TE_Dir->setText(QDir::currentPath());
    ui->LE_Pswd->setFocus();
    setWindowFlags(Qt::Window
        | Qt::WindowMinimizeButtonHint
        | Qt::WindowMaximizeButtonHint
        | Qt::MSWindowsFixedSizeDialogHint);
}

MainWindow::~MainWindow(){
    delete ui;
}

bool MainWindow::CheckPswd() {
    QString user_input = ui->LE_Pswd->text();
    ui->LE_Pswd->setText("");
    ui->LE_Pswd->setFocus();
    if (pswd_ck.Check(user_input)) {
        return true;
    }
    QMessageBox alert(QMessageBox::Warning, "Alert", "Wrong Password", QMessageBox::StandardButton::Ok);
    alert.exec();
    return false;
}

void MainWindow::on_PB_Stop_clicked(){
    if (CheckPswd()) {
        PostQuitMessage(0);
    }
}

void MainWindow::closeEvent(QCloseEvent * event) {
    event->ignore();
}
