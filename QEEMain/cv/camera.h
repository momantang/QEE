#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <opencv2/opencv.hpp>
class Camera:public QObject
{
    Q_OBJECT
public:

    Camera(const QString &camera_kind=NULL);
};

#endif // CAMERA_H
