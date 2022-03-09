#include "AOI.h"


AOI::AOI(QObject* parent, QMainWindow* mv)
{
	this->mw = mv;
}

AOI::~AOI()
{
}

void AOI::initUI()
{
	aoiMenu = this->mw->menuBar()->addMenu("&AOI");
	medianBlurAction = new QAction("&Media blur", this->mw);
	aoiMenu->addAction(medianBlurAction);


}
