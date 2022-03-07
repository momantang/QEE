#ifndef UTILS_H
#define UTILS_H
#include <QImage>
#include <opencv2/opencv.hpp>
namespace Utils {
    void Mat2QImage(const cv::Mat& source ,QImage& output);
    void QImage2Mat(const QImage& source,cv::Mat& output);
    void  fitResize(const cv::Mat& source,cv::Mat & output,int width=200);
}



#endif // UTILS_H
