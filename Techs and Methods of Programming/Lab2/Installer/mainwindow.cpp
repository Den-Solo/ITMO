#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Installer * inst)
    : QMainWindow(nullptr)
    , ui(new Ui::MainWindow)
    , inst_(inst)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QLocale curLocale(QLocale("ru_RU"));
    QLocale::setDefault(curLocale);
    ui->setupUi(this);

    // set deault paths
    ui->le_file_path->setText(QString::fromStdWString(inst_->GetPath()));
    ui->te_path->setText(QString::fromStdWString(inst_->GetPath()));

    ui->stackedWidget->setCurrentIndex(0);

    // radio buttons group id
    ui->LimitType->addButton(ui->rb_launches, 0);
    ui->LimitType->addButton(ui->rb_time, 1);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox messageBox(QMessageBox::Question,
                "Прервать установку",
                "Хотите прервать установку",
                QMessageBox::Yes | QMessageBox::No,
                this);
    messageBox.setButtonText(QMessageBox::Yes, tr("Да"));
    messageBox.setButtonText(QMessageBox::No, tr("Нет"));
    auto resBtn = messageBox.exec();

    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
    }
}

void MainWindow::on_pb_cancel_clicked()
{
    this->close();
}

void MainWindow::on_pb_next_clicked()
{
    int cur_idx = ui->stackedWidget->currentIndex();
    int max_idx = ui->stackedWidget->count() - 1;
    if (cur_idx != max_idx )
    {
        ui->stackedWidget->setCurrentIndex(cur_idx + 1);
        ui->pb_back->setEnabled(true);
        if (cur_idx + 1 == max_idx )
            ui->pb_next->setText("Установить");
    }
    else
    {
        inst_->SetPath(ui->le_file_path->text().toStdWString());
        inst_->SetCreateDesktopShortcut(ui->cb_create_desktop_sc->isChecked());
        inst_->SetCreateStartupShortcut(ui->cb_create_startup_sc->isChecked());
        inst_->SetType(static_cast<Installer::ProgLimit>(ui->LimitType->checkedId()));
        if (inst_->Exec())
            QMessageBox::information(this,"Успех","Установлено!");
        else
            QMessageBox::information(this, "Ошибка", "Возникла ошибка!");
        QApplication::quit();
    }
}

void MainWindow::on_pb_back_clicked()
{
    int cur_idx = ui->stackedWidget->currentIndex();
    if (cur_idx != 0)
    {
        ui->stackedWidget->setCurrentIndex(cur_idx - 1);
        ui->pb_next->setText("Далее");
        if (cur_idx - 1 == 0)
            ui->pb_back->setEnabled(false);
    }
}

void MainWindow::on_pb_search_clicked()
{
    QString path = QFileDialog::QFileDialog::getExistingDirectory(0, "Выберите папку", "");
    ui->le_file_path->setText(path);
    ui->te_path->setText(path);
}
