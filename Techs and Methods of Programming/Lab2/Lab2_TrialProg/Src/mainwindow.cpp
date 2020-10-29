#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow()
    : ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete BOR_dialog_;
}

void MainWindow::on_pb_submit_clicked()
{
    QString surname = ui->le_surname->text();
    QString name = ui->le_name->text();
    if (!surname.size() || !name.size())
    {
        QMessageBox::warning(this,"Внимание","Все поля необходимо заполнить");
        return;
    }
    acc_manager_.SetCurrentUser(surname.toStdWString(),name.toStdWString());

    if (!acc_manager_.IsOver())
    {
        QString answer;
        if (acc_manager_.IsNewUser())
            answer += "Вы новый пользователь!\n";
        else
            answer += "У нас есть данные о Вас!\n";
        answer += QString::fromStdWString(acc_manager_.GetMsg());
        QMessageBox::information(this,"Внимание",answer);
    }
    else
    {
        BOR_dialog_ = new BuyOrRemoveDialog();
        BOR_dialog_->exec();
    }
    QApplication::quit();
}

