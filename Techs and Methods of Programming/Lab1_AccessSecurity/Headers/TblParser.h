#pragma once

#include <QFile>
#include <QRegularExpression>
#include <QString>
#include <QTextStream>
#include <stdexcept>
#include <string>
#include <vector>

class TblParser 
{

public:
    struct Result 
    {
        QByteArray pswd_hash; // unhexed from string pswd MD5 (4 int)
        std::vector<std::wstring> file_names;
        std::vector<std::wstring> pattern_file_names;
    };

private:
    static const QString tbl_file_name_;
    static QRegularExpression pattern_finder_;

public:
    static Result Process();
};
