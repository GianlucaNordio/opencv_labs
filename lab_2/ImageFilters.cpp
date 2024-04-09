#include "ImageFilters.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <algorithm>




cv::Mat maxFilter(cv::Mat& src, int kernelSize) {
    
    // check if kernel is odd
    if(kernelSize % 2 == 0) {
        std::cerr<<"Kernel must be odd!"<<std::endl;
        return cv::Mat();
    }
    
    cv::Mat result(src.rows, src.cols, src.type());

    // move thorugh the image
    for(int c = 0; c < src.cols; c++) {
        for(int r = 0; r < src.rows; r++) {

            // find the max inside the kernel
            unsigned char max = src.at<unsigned char>(r, c);
            int halfKernel = (kernelSize - 1) / 2;
            for(int deltaRow = -halfKernel; deltaRow <= halfKernel ;deltaRow++) {
                for(int deltaCol = -halfKernel; deltaCol <= halfKernel ;deltaCol++) {

                    // modify value if higher than max and if the position is inside the bounds of image
                    if((r + deltaRow >= 0 && r + deltaRow < result.rows) && (c + deltaCol >= 0 && c + deltaCol < result.cols))
                        max = std::max(max, src.at<unsigned char>(r + deltaRow, c + deltaCol));
                }
            }

            result.at<unsigned char>(r, c) = max;
        }
    }
    return result; 
}


cv::Mat minFilter(cv::Mat& src, int kernelSize) {
    
    // check if kernel is odd
    if(kernelSize % 2 == 0) {
        std::cerr<<"Kernel must be odd!"<<std::endl;
        return cv::Mat();
    }
    
    cv::Mat result(src.rows, src.cols, src.type());

    // move thorugh the image
    for(int c = 0; c < src.cols; c++) {
        for(int r = 0; r < src.rows; r++) {

            // find the min inside the kernel
            unsigned char min = src.at<unsigned char>(r, c);
            int halfKernel = (kernelSize - 1) / 2;
            for(int deltaRow = -halfKernel; deltaRow <= halfKernel ;deltaRow++) {
                for(int deltaCol = -halfKernel; deltaCol <= halfKernel ;deltaCol++) {
                    
                    // modify value if lower than min and if the position is inside the bounds of image
                    if((r + deltaRow >= 0 && r + deltaRow < result.rows) && (c + deltaCol >= 0 && c + deltaCol < result.cols))
                        min = std::min(min, src.at<unsigned char>(r + deltaRow, c + deltaCol));
                }
            }

            result.at<unsigned char>(r, c) = min;
        }
    }
    return result; 
}

cv::Mat medianFilter(cv::Mat& src, int kernelSize) {
    
    // check if kernel is odd
    if(kernelSize % 2 == 0) {
        std::cerr<<"Kernel must be odd!"<<std::endl;
        return cv::Mat();
    }
    
    cv::Mat result(src.rows, src.cols, src.type());

    // move thorugh the image
    for(int c = 0; c < src.cols; c++) {
        for(int r = 0; r < src.rows; r++) {
            std::vector<unsigned char> elements; // dynamic vector used because number of elems can change
            int halfKernel = (kernelSize - 1) / 2;
            for(int deltaRow = -halfKernel; deltaRow <= halfKernel ;deltaRow++) {
                for(int deltaCol = -halfKernel; deltaCol <= halfKernel ;deltaCol++) {
                    // modify value if lower than min and if the position is inside the bounds of image
                    if((r + deltaRow >= 0 && r + deltaRow < result.rows) && (c + deltaCol >= 0 && c + deltaCol < result.cols))
                        elements.push_back(src.at<unsigned char>(r + deltaRow, c + deltaCol));
                }
            }
            std::sort(elements.begin(), elements.end());
            if(elements.size() % 2 == 0)
                result.at<unsigned char>(r, c) = (elements[elements.size() / 2 - 1] +  elements[elements.size() / 2 ])/2;  
            else
                result.at<unsigned char>(r, c) = elements[elements.size() / 2];
        }
    }
    return result; 
}



cv::Mat gaussianFilter(cv::Mat& src, int kernelSize) {
    cv::Mat dst(src.rows, src.cols, src.type());
    if(kernelSize % 2 == 0) {
        std::cerr<<"Kernel must be odd!"<<std::endl;
        return cv::Mat();
    }
    cv::GaussianBlur(src, dst, cv::Size(kernelSize, kernelSize), 0);
    return dst;
}
