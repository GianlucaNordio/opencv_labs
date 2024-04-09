#ifndef IMAGEFILTERS_HPP
#define IMAGEFILTERS_HPP

#include <opencv2/highgui.hpp>

cv::Mat maxFilter(cv::Mat& src, int kernelSize);
cv::Mat minFilter(cv::Mat& src, int kernelSize);
cv::Mat medianFilter(cv::Mat& src, int kernelSize);
cv::Mat gaussianFilter(cv::Mat& src, int kernelSize);


#endif