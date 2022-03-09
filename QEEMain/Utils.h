#pragma once
#include <opencv2/opencv.hpp>
#include <qimage.h>
namespace QEE {
	namespace Utils {
		QImage Mat2QImage(const cv::Mat& src,bool isCopy=false);
		cv::Mat QImage2Mat(const QImage& src, bool isCopy=false);
	}
}