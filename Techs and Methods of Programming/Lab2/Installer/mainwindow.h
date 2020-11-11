#include "installer.h"

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTextCodec>
#include <QLocale>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define APP_NAME "Trial Program"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Installer * inst);
    ~MainWindow();

private:
    void closeEvent(QCloseEvent *e) override;

private slots:
    void on_pb_cancel_clicked();

    void on_pb_next_clicked();

    void on_pb_back_clicked();

    void on_pb_search_clicked();

private:
    Ui::MainWindow *ui;
    Installer* inst_{nullptr};
};

