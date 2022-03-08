#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <opencv2/opencv.hpp>

class CameraSettings :public QObject {

};
class Camera:public QObject
{
    Q_OBJECT
public:
    Camera(const QString &camera_kind="build-in");
    ~Camera();
    void open();
    void release();
    void setAutoTrigger(bool isAuto = false);
    void capture(cv::Mat &mat);
    cv::Mat getMat() const { return currentMat; };
    int getInteral()const { return auto_triggertrap_interal; }
signals:
    void triggertrap();//触发拍照信号
private:
    bool isAuto = true;
    cv::Mat currentMat;
    cv::VideoCapture videoCapture;
    int auto_triggertrap_interal = 100;//默认100毫秒间隔触发
    //CameraSettings* cameraSettings=nullptr;
};

#endif // CAMERA_H
