#pragma once

#include <QObject>
#include <opencv2/opencv.hpp>
class Camera : public QObject
{
	Q_OBJECT

public:
	Camera(QObject *parent=nullptr);
	~Camera();
	 void initCamera(){};
	 void openCamera(){};
	 void trigged(){};
	 void closeCamera(){};
	 cv::Mat takeMat(){};
	
};
class BuildInCamera :public Camera {
	Q_OBJECT
public:
	BuildInCamera(QObject* parent = nullptr);
};
class MindVisionCamera :public Camera {
	Q_OBJECT
public:
	MindVisionCamera(QObject* parent = nullptr);

};
class CameraFactory {
public:
	Camera* instance(QString name) {
		if (name == "build-in") {
			return  static_cast<Camera*> (new BuildInCamera);
		}
		else if (name == "MindVision") {
			return static_cast<Camera*>(new MindVisionCamera);
		}
	}
};
