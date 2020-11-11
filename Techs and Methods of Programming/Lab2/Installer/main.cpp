#include "mainwindow.h"
#include "installer.h"

#include <QApplication>

static QVector<QString> keys = {"-Silent","/Silent","-S","/S"};

int main(int argc, char *argv[])
{
    Installer inst;
    if (argc > 1 && keys.contains(argv[1]))
    {
        inst.Exec();
    }
    else{
        QApplication a(argc, argv);
        MainWindow w(&inst);
        w.show();
        return a.exec();
    }

}
