#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>


// Change window name for high threshold and low threshold
const std::string WINDOW_NAME = "Street Scene";
const std::string TRACKBAR_LOW_THRESHOLD = "Low Threshold";
const std::string TRACKBAR_HIGH_THRESHOLD = "High Threshold";
const std::string WINDOW_NAME_CANNY = "Canny";

int lowThreshold;
int highThreshold;

static void lowThresholdTrackbar( int, void* );
static void highThresholdTrackbar( int, void* );
static void update( void* );

int main() {
    cv::Mat src = cv::imread("street_scene.png");
    cv::imshow(WINDOW_NAME, src);

    if( src.empty() ) { 
        std::cout << "Error loading src" << std::endl; 
        return -1; 
    }

    int maxValue = 1000;
    cv::createTrackbar(TRACKBAR_LOW_THRESHOLD, WINDOW_NAME, NULL, maxValue, lowThresholdTrackbar, &src );
    cv::createTrackbar(TRACKBAR_HIGH_THRESHOLD, WINDOW_NAME, NULL, maxValue, highThresholdTrackbar, &src );
    cv::waitKey(0);
}

static void lowThresholdTrackbar(int value, void* input) {
    lowThreshold = value;
    update(input);
}


static void highThresholdTrackbar(int value, void* input) {
    highThreshold = value;
    update(input);
}

static void update( void* input) {
    cv::Mat src = *((cv::Mat*)input);
    cv::Mat edges;
    cv::Canny(src, edges, lowThreshold, highThreshold);
    cv::imshow(WINDOW_NAME_CANNY, edges);
}