#include "camera.h"
#include <qdebug.h>

Camera::Camera(QObject* parent)
{
}

Camera::~Camera()
{
}
BuildInCamera* BuildInCamera::instance = new BuildInCamera;

BuildInCamera* BuildInCamera::getInstance() {
	return instance;
}
void BuildInCamera::initCamera()
{
	//do noting
	videoCapture.open(0,cv:: CAP_DSHOW);
	if (videoCapture.isOpened()) {
		videoCapture.release();
		qDebug() << "摄像头能正常打开";
	}
	else {
		qDebug() << "摄像头故障，请检查";
	}
}

void BuildInCamera::openCamera()
{
	videoCapture.open(0, cv::CAP_DSHOW);
}

void BuildInCamera::closeCamera()
{
	qDebug() << "close build in camera";
	videoCapture.release();
}

void BuildInCamera::takeMat(cv::Mat&mat)
{
	videoCapture >> mat;
}
