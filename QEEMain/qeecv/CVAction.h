#pragma once

#include <QObject>

class CVAction : public QObject
{
	Q_OBJECT

public:
	CVAction(QObject *parent);
	~CVAction();
};
