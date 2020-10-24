#pragma once

#include <QByteArray>
#include <QString>
#include <QCryptographicHash>

class PasswordChecker
{

	const QByteArray digest_;	  //md5 hash

public:
	explicit PasswordChecker(QByteArray&& d);
	explicit PasswordChecker(const QByteArray& d);
	~PasswordChecker() = default;

	bool Check(const QString& user_pswd) const;
};
