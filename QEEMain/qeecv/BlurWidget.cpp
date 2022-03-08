#include "BlurWidget.h"
#include "qdebug.h"

BlurWidget::BlurWidget(QWidget *parent)
	: QWidget(parent)
{
	QVBoxLayout* mainLayout = new QVBoxLayout;
	QHBoxLayout* eqblurLayout = new QHBoxLayout;
	QSlider* eq_size_width_slider = new QSlider(this);
	eq_size_width_slider->setMinimum(1);
	eq_size_width_slider->setMaximum(20);
	eq_size_width_slider->setSingleStep(2);
	eq_size_width_slider->setPageStep(2);
	eq_size_width_slider->setTickPosition(QSlider::TicksAbove);
	eq_size_width_slider->setOrientation(Qt::Horizontal);
	connect(eq_size_width_slider, &QSlider::valueChanged, this, [this](int value) {
		qDebug() << value;
		});
	eqblurLayout->addWidget(new QLabel("卷积核Width："));
	eqblurLayout->addWidget(eq_size_width_slider);
	QHBoxLayout* boxblurLayout = new QHBoxLayout;
	QHBoxLayout* guassblurLayout = new QHBoxLayout;
	QHBoxLayout* medianblurLayout = new QHBoxLayout;
	QHBoxLayout* bilateralLayout = new QHBoxLayout;
	mainLayout->addLayout(eqblurLayout);
	mainLayout->addLayout(boxblurLayout);
	mainLayout->addLayout(guassblurLayout);
	mainLayout->addLayout(medianblurLayout);
	mainLayout->addLayout(bilateralLayout);
	this->setLayout(mainLayout);
}

BlurWidget::~BlurWidget()
{
}
