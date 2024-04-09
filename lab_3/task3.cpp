#include <iostream>
#include <opencv2/highgui.hpp>

const std::string WINDOW_NAME = "Robocup";
const int KERNEL_SIDE = 9;

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

void callBackFunc(int event, int col, int row, int flags, void* userdata) {
    if(event == cv::EVENT_LBUTTONDOWN || event == cv::EVENT_RBUTTONDOWN ) {
        // Read input image
        cv::Mat img = *(cv::Mat*)userdata;

        // Show the clicked point value
        cv::Vec3b& pressedPoint = img.at<cv::Vec3b>(row, col);

        std::cout<<"ACTUAL VALUE"<<std::endl;
        std::cout<<"B: "<<(int)pressedPoint[0]<<std::endl;
        std::cout<<"G: "<<(int)pressedPoint[1]<<std::endl;
        std::cout<<"R: "<<(int)pressedPoint[2]<<std::endl;

        // Compute the average of the 9x9 square arond the clicked point
        std::vector<int> avg(3);
        int kernelHalfSide = (KERNEL_SIDE - 1) / 2; 
        for(int ch = 0; ch < 3; ch++) {
            int count = 0;
            for(int c = -kernelHalfSide; c <= kernelHalfSide; c++) {
                for(int r = -kernelHalfSide; r <= kernelHalfSide; r++) {
                    if(row + r >= 0 && row + r <= img.rows && col + c >= 0 && col + c <= img.cols) {
                        count++;
                        avg[ch] += img.at<cv::Vec3b>(row + r, col + c)[ch];
                    }
                }
            }
            avg[ch] /= count;
        }

        // Show the compute average based on considered channel
        std::cout<<"AVERAGE VALUE"<<std::endl;
        std::cout<<"B: "<<avg[0]<<std::endl;
        std::cout<<"G: "<<avg[1]<<std::endl;
        std::cout<<"R: "<<avg[2]<<std::endl<<std::endl;
    }
}