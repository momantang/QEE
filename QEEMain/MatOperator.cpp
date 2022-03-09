#include "MatOperator.h"

cv::Mat MatOperator::calculateLightPattern(cv::Mat& img)
{
    cv::Mat pattern;
    cv::blur(img,pattern,cv::Size(img.cols/3,img.rows/3));
    return pattern;
}

Mat MatOperator::removeLight(Mat img, Mat pattern, int method)
{
    Mat aux;
    if (method == 1) {
        Mat img32, pattern32;
        img.convertTo(img32, CV_32F);
        pattern.convertTo(pattern32, CV_32F);
        aux = 1 - (img32 / pattern32);
        aux.convertTo(aux, CV_8U, 255);
    }
    else {
        aux = pattern - img;
    }
    return aux;
}
