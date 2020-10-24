#include "TblParser.h"

const QString TblParser::tbl_file_name_ = "template.tbl";
QRegularExpression TblParser::pattern_finder_ = QRegularExpression("(.*[*|?|\[].*)");

TblParser::Result TblParser::Process()
{
    Result res {};

    if (!QFile::exists(tbl_file_name_))
        throw std::runtime_error(tbl_file_name_.toStdString() + " doesn't exist");

    QFile file_(tbl_file_name_);
    if (!file_.open(QIODevice::ReadOnly)) {
        throw std::runtime_error(tbl_file_name_.toStdString() + " locked");
    }

    QTextStream in(&file_);
    { // read pswd
        QByteArray hex_pswd;
        in >> hex_pswd;
        res.pswd_hash = QByteArray::fromHex(hex_pswd);
    }

    { // read file names and patterns
        QString tmp;
        while (!in.atEnd()) {
            in >> tmp;
            if (tmp.size() && tmp[0] != '#') {
                if (tmp.contains(pattern_finder_)) {
                    res.pattern_file_names.push_back(tmp.toStdWString());
                } else {
                    res.file_names.push_back(tmp.toStdWString());
                }
            }
        }
    }
    return res;
}
