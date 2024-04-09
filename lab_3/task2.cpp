#include <iostream>
#include <opencv2/highgui.hpp>

const std::string WINDOW_NAME = "Robocup";

void callBackFunc(int event, int col, int row, int flags, void* userdata);

int main(int argc, char** argv) {
    // Read and show image
    cv::Mat img = cv::imread("robocup.jpg");
    cv::namedWindow(WINDOW_NAME);
    cv::imshow(WINDOW_NAME, img);    

    // Set the mouse call back for window with the image
    cv::setMouseCallback(WINDOW_NAME, callBackFunc, &img);
    cv::waitKey(0);    
    return 0;
}

// Callback function that receives the image as parameter and shows the BGR values of the clicked point
void callBackFunc(int event, int col, int row, int flags, void* userdata) {

    // Execute if mouse is clicked
    if(event == cv::EVENT_LBUTTONDOWN || event == cv::EVENT_RBUTTONDOWN) {
        // Read image from userdata parameter
        cv::Mat img = *(cv::Mat*)userdata;

        // Obtain and show pixel values of clicked point
        cv::Vec3b& pressedPoint = img.at<cv::Vec3b>(row, col);
        std::cout<<"B: "<<(int)pressedPoint[0]<<std::endl;
        std::cout<<"G: "<<(int)pressedPoint[1]<<std::endl;
        std::cout<<"R: "<<(int)pressedPoint[2]<<std::endl<<std::endl;
    }
}