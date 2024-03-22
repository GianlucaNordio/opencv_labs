#include <iostream>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


int main(int argc, char** argv) {
    // Read input image
    cv::Mat garden;
    garden = cv::imread("imgs/Garden.jpg");
    if (garden.data == NULL) {
        std::cerr<<"Image name not valid"<<std::endl;
        return -1;
    }
    cv::imshow("Original image", garden);
    cv::waitKey(0);
    

    // Produce and show greyscale image
    cv::Mat grsGarden;
    cv::cvtColor(garden, grsGarden, cv::COLOR_RGB2GRAY);
    cv::imshow("Greyscale image", grsGarden);
    cv::imwrite("imgs/Garden_greyscale.jpg", grsGarden);
    cv::waitKey(0);

    return 0;
}