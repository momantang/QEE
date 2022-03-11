#pragma once

#include <QNetworkCookieJar>
#include <QNetworkAccessManager>
#include <QSettings>

#include <QColor>

class CookieJar :public QNetworkCookieJar {
	static constexpr auto CookiesSeparator = "\n";
public:
private:
	void fromString(const QString& cookies);
};

class Settings : public QObject
{
	Q_OBJECT

public:
	Settings(QObject *parent);
	~Settings();
};
