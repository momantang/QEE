#pragma once

#include <QObject>
#include <QtWidgets>
class AOI : public QObject
{
	Q_OBJECT

public:
	AOI(QObject* parent, QMainWindow* mv);
	~AOI();
	void initUI();
private:
	QMainWindow* mw;
	QMenu* aoiMenu;
	QAction* medianBlurAction;
};
