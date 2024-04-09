#include <iostream>
#include <opencv2/highgui.hpp>

const std::string WINDOW_NAME = "Robocup";
const std::string THRESHOLD_WINDOW_NAME = "THRESHOLD";
const int KERNEL_SIDE = 9;
const int THRESHOLD = 40;

void callBackFunc(int event, int col, int row, int flags, void* userdata);

int main(int argc, char** argv) {
    // Read and show image
    cv::Mat img = cv::imread("robocup.jpg");
    cv::namedWindow(WINDOW_NAME);
    cv::imshow(WINDOW_NAME, img);    

    // Set mouse callback
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

        // Create the mask image
        cv::Mat mask(img.rows, img.cols, CV_8U);

        // Go through the original image and set the pixel of the mask image based on a threshold
        for(int r = 0; r < img.rows; r++) {
            for(int c = 0; c < img.cols; c++) {
                cv::Vec3b& point = img.at<cv::Vec3b>(r, c);

                // Put white pixel if point RGB value are inside the threshold, black otherwise
                if(std::abs((int)point[0] - avg[0]) < THRESHOLD && std::abs((int)point[1] - avg[1]) < THRESHOLD && std::abs((int)point[2] - avg[2]) < THRESHOLD) {
                    mask.at<unsigned char>(r, c) = 255;
                }
                else {
                    mask.at<unsigned char>(r, c) = 0;
                }
            }
        }

        //Show mask image
        cv::imshow(THRESHOLD_WINDOW_NAME, mask);
        cv::waitKey(0);
    }
}