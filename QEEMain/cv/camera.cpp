#include "camera.h"
#include <qdebug.h>


Camera::Camera(const QString& camera_kind)
{
}

Camera::~Camera()
{
	qDebug() << "releas camera";
}

void Camera::open()
{
	qDebug() << "open camera";
	videoCapture.open(0);
	qDebug() << videoCapture.isOpened();
}

void Camera::release()
{
	videoCapture.release();
}

void Camera::setAutoTrigger(bool isAuto)
{
	this->isAuto = isAuto;
}

void Camera::capture(cv::Mat& mat)
{
	qDebug() << "capture mat";
	if (videoCapture.isOpened()) {

		videoCapture >> mat;
	}
}

