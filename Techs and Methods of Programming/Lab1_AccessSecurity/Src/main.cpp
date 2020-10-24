#include "EnvironmentSetter.h"
#include "MainWindow.h"
#include "PasswordChecker.h"
#include "TblParser.h"
#include "filter.h"

#include <QApplication>
#include <QMessageBox>
#include <QString>

#include <cstring>
#include <stdexcept>
#include <string>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    try {
        EnvironmentSetter env(argc, argv);
        TblParser::Result data = TblParser::Process();
        data.file_names.push_back(L"template.tbl");
        if (argc > 0)
            data.file_names
                .push_back(QString(argv[0])
                .split('\\').back().toStdWString()); // file.exe
        PasswordChecker pc(std::move(data.pswd_hash));
        Filter filter(
            std::move(data.file_names),
            std::move(data.pattern_file_names),
            env.GetPSID());
        MainWindow w(pc);
        w.show();
        return a.exec();
    } catch (std::runtime_error& e) {
        if (e.what() != std::string("VALID_EXIT"))
            MessageSender::ShowBlockMsg(L"Critical Error",
                QString(e.what()).toStdWString());
        return -1;
    }
}
