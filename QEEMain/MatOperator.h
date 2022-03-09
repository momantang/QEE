#pragma once
#include <opencv2/opencv.hpp>
#include <string>
using cv::Mat;
class MatOperator
{
public:
	static Mat read2Gray(std::string path) { return cv::imread(path, 0); };
	static Mat calculateLightPattern(Mat& img);
	static Mat removeLight(Mat img, Mat pattern, int method);
};

