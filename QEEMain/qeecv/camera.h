#pragma once

#include <QObject>
#include <qstring.h>
#include <opencv2/opencv.hpp>
class Camera : public QObject
{
	Q_OBJECT

public:
	~Camera();
	Camera(QObject* parent = nullptr);
	virtual void initCamera() {};
	virtual void openCamera() {};
	virtual void closeCamera() {};
	virtual void takeMat(cv::Mat &mat) {  };
signals:
	void trigged();
protected:
private:
	int interval;//拍照间隔
	bool isAutoTrig=false;//是否自动拍照

};


class BuildInCamera :public Camera {
	Q_OBJECT
public:	
	void initCamera();
	void openCamera() ;
	void closeCamera() ;
	void  takeMat(cv::Mat& mat) ;
private:
	static BuildInCamera* instance;
	cv::VideoCapture videoCapture;
	BuildInCamera(QObject* parent = nullptr) :Camera(parent) {};
public:
	static BuildInCamera* getInstance();
};

/*
class MindVisionCamera :public Camera {
	Q_OBJECT

private:
	static MindVisionCamera* instance1;
	MindVisionCamera(QObject* parent = nullptr) :Camera(parent) {};
public:
	static MindVisionCamera* getInstance() {
		return instance1;
	};
};
*/

class CameraFactory {
public:
	static Camera* instance(QString name) {
		if (name == "build-in") {
			return  static_cast<Camera*> (BuildInCamera::getInstance());
		}
		//else if (name == "MindVision") {
		//	return static_cast<Camera*>(MindVisionCamera::getInstance());
		//}
		return nullptr;
	}
};
