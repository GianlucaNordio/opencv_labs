#include <iostream>
#include <opencv2/highgui.hpp>

int main(int argc, char** argv) {
    // Read and show image
    cv::Mat img = cv::imread("robocup.jpg");
    cv::imshow("Robocup", img);
    cv::waitKey(0);
    return 0;
}