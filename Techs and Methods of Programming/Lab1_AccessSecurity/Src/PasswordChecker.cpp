#include "PasswordChecker.h"

PasswordChecker::PasswordChecker(QByteArray&& d) //accepts unhexed array (digest)
    : digest_(std::move(d))
{
}

PasswordChecker::PasswordChecker(const QByteArray& d) //accepts unhexed array (digest)
    : digest_(d)
{
}

bool PasswordChecker::Check(const QString& user_pswd) const
{
    QByteArray user_input_hex
        = QCryptographicHash::hash(user_pswd.toUtf8(), QCryptographicHash::Md5);
    return digest_ == user_input_hex;
}