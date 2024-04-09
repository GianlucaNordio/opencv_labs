#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

const std::string WINDOW_NAME = "Robocup";
const std::string THRESHOLD_WINDOW_NAME = "THRESHOLD";
const int KERNEL_SIDE = 9;
const int THRESHOLD = 20;


void callBackFunc(int event, int col, int row, int flags, void* userdata);

int main(int argc, char** argv) {
    // Read input image
    cv::Mat img = cv::imread("robocup.jpg");

    // Pass to Hue Saturation Value coding
    cv::cvtColor(img, img, cv::COLOR_BGR2HSV);

    //Show the image coding HSV as BGR
    cv::namedWindow(WINDOW_NAME);
    cv::imshow(WINDOW_NAME, img);    
    
    // Set mouse callback
    cv::setMouseCallback(WINDOW_NAME, callBackFunc, &img);

    cv::waitKey(0);
    return 0;
}

void callBackFunc(int event, int col, int row, int flags, void* userdata) {
    if(event == cv::EVENT_LBUTTONDOWN || event == cv::EVENT_RBUTTONDOWN ) {
        cv::Mat img = *(cv::Mat*)userdata;

        // Show pressed point values
        cv::Vec3b& pressedPoint = img.at<cv::Vec3b>(row, col);

        std::cout<<"ACTUAL VALUE"<<std::endl;
        std::cout<<"H: "<<(int)pressedPoint[0]<<std::endl;
        std::cout<<"S: "<<(int)pressedPoint[1]<<std::endl;
        std::cout<<"V: "<<(int)pressedPoint[2]<<std::endl;

        // Compute the average BGR values of the points around the clicked one
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

        // Show the averages
        std::cout<<"AVERAGE"<<std::endl;
        std::cout<<"H: "<<avg[0]<<std::endl;
        std::cout<<"S: "<<avg[1]<<std::endl;
        std::cout<<"V: "<<avg[2]<<std::endl<<std::endl;

        // Create the mask putting white pixel if the values are inside a threshold, black otherwise
        cv::Mat mask(img.rows, img.cols, CV_8U);
        for(int r = 0; r < img.rows; r++) {
            for(int c = 0; c < img.cols; c++) {
                cv::Vec3b& point = img.at<cv::Vec3b>(r, c);
                if(std::abs((int)point[0] - avg[0]) < THRESHOLD && std::abs((int)point[1] - avg[1]) < THRESHOLD && std::abs((int)point[2] - avg[2]) < THRESHOLD) {
                    mask.at<unsigned char>(r, c) = 255;
                }
                else {
                    mask.at<unsigned char>(r, c) = 0;
                }
            }
        }

        // Show mask image
        cv::imshow(THRESHOLD_WINDOW_NAME, mask);
        cv::waitKey(0);
    }
}