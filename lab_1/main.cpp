#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

#include "ImageFilters.hpp"

int main(int argc, char** argv) {
    cv::Mat img;
    if(argc == 1) {
        std::cerr<<"You need to insert the name of an image";
        return -1;
    }
    
    img = cv::imread(argv[1]);
    if (img.data == NULL) {
        std::cerr<<"Image name not valid"<<std::endl;
        return -1;
    }
    cv::imshow("Original image", img);
    

    // Produce and show greyscale image
    cv::Mat grsImg;
    cv::cvtColor(img, grsImg, cv::COLOR_RGB2GRAY);
    cv::imshow("Greyscale image", grsImg);
    cv::imwrite("Garden_greyscale.jpg", grsImg);

    
    histogramShower(grsImg);
    cv::Mat grsEqualizedImg;
    cv::equalizeHist(grsImg, grsEqualizedImg);
    histogramShower(grsEqualizedImg);

    cv::Mat filteredImg1 = medianFilter(grsImg, 5);
    cv::imshow("Filtered image", filteredImg1);
    cv::waitKey(0);
}