#include "utils.h"

void Utils::Mat2QImage(const cv::Mat& source ,QImage& output){
    if(source.empty()){
        return ;
    }
    auto type= source.type();
    switch (type) {
    case CV_8UC1:
        break;
    case CV_8UC3:
        output=QImage((const unsigned char*)source.data,source.cols,source.rows,QImage::Format_BGR888);
        break;
    default:
        break;
    }
}
void Utils::QImage2Mat(const QImage& source,cv::Mat& outpu){

}
void  Utils::fitResize(const cv::Mat& source,cv::Mat & output,int width){
    if(source.empty())
        return;
    int fx=width*1.0/source.cols;
   cv::resize(source,output,cv::Size(),fx);

}
