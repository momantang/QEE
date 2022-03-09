#include "Utils.h"
#include <map>
QImage::Format fromMat(const cv::Mat& src) {
	switch (src.type())
	{
	case CV_8UC1:
		return QImage::Format_Grayscale8;
	case CV_8UC3:
		return QImage::Format_BGR888;
	default:
		return QImage::Format_Invalid;
	}
}

QImage marref(const cv::Mat& src, QImage::Format format) {
	return QImage(src.data, src.cols, src.rows, src.cols * src.channels(), format);
}
QImage QEE::Utils::Mat2QImage(const cv::Mat& src, bool isCopy)
{
	if (!src.empty()) {
		auto type = src.type();
		auto format =fromMat(src);
		if (format != QImage::Format_Invalid) {
			QImage q= QImage(src.data, src.cols, src.rows, src.cols * src.channels(), format);
			return isCopy ? QImage(src.data, src.cols, src.rows, src.cols * src.channels(), format).copy():QImage(src.data, src.cols, src.rows, src.cols * src.channels(), format);
		}
	}
	return QImage();
}

cv::Mat QEE::Utils::QImage2Mat(const QImage& src, bool isCopy)
{
	return cv::Mat();
}
