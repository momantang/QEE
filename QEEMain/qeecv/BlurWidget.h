#pragma once
#include <QLabel>
#include <QtWidgets>

class BlurWidget : public QWidget
{
	Q_OBJECT

public:
	BlurWidget(QWidget *parent = Q_NULLPTR);
	~BlurWidget();

private:
	QLabel* blurLabel;
};
