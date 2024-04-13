#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

const std::string WINDOW_NAME = "Street Scene";
const std::string WINDOW_OUTPUT_IMAGE = "Ouput image";

int parametricIntersect(float r1, float t1, float r2, float t2, int *x, int *y);

int main() {
    cv::Mat src = cv::imread("street_scene.png");
    if( src.empty() ) { 
        std::cout << "Error loading src1 \n"; 
        return -1; 
    }

    cv::Mat copy = src.clone();
    cv::Mat greySrc, blurredSrc, edges;
    std::vector<cv::Vec3f> lines;
    cv::imshow(WINDOW_NAME, src);

    // Color to Grayscale
    cv::cvtColor(src, greySrc, cv::COLOR_BGR2GRAY);

    // Blur image
    cv::GaussianBlur(greySrc, blurredSrc, cv::Size(3, 3), 1);

    // Canny filter
    Canny(blurredSrc, edges, 467, 470);

    // Dilation
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(1, 1));
    cv::dilate(edges, edges, element);
    
    // Hough lines
    HoughLines(edges, lines, 1, CV_PI/180, 150); 

    // Sort the lines by votes
    std::sort(lines.begin(), lines.end(), 
        [](const cv::Vec3f& a, const cv::Vec3f& b) { return a[2] < b[2];});

    // Code to show the two lines with highest number of votes
    /*
    for( size_t i = 0; i < 2; i++ ) {
        float rho = lines[i][0], theta = lines[i][1];
        cv::Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line( copy, pt1, pt2, cv::Scalar(0,0,255), 3, cv::LINE_AA);
    }
    */
    
    std::vector<cv::Point> point(3);

    // Find intersect of two lines
    parametricIntersect(lines[0][0], lines[0][1], lines[1][0], lines[1][1], &point[0].x, &point[0].y);

    // Computation of the intersects with the bottom of the image by using inverse of r = x cosθ + y sinθ
    // with y = src.cols - 1 (y coordinate of pixel at the bottom)
    point[1].y = src.cols - 1;
    point[1].x = (lines[0][0] - point[1].y * sinf(lines[0][1]))/cosf(lines[0][1]);

    point[2].y = src.cols - 1;
    point[2].x = (lines[1][0] - point[2].y* sinf(lines[1][1]))/cosf(lines[1][1]);
    
    std::cout<<point[0].x<<std::endl<<point[0].y<<std::endl;
    cv::fillPoly(copy, point, cv::Scalar( 0, 0, 255 ));

    cv::imshow(WINDOW_OUTPUT_IMAGE, copy);
    cv::waitKey(0);
}


// Code source: https://stackoverflow.com/questions/383480/intersection-of-two-lines-defined-in-rho-theta-parameterization
int parametricIntersect(float r1, float t1, float r2, float t2, int *x, int *y) {
    float ct1 = cosf(t1);     //matrix element a
    float st1 = sinf(t1);     //b
    float ct2 = cosf(t2);     //c
    float st2 = sinf(t2);     //d
    float d = ct1 * st2 - st1 * ct2;        // Determinative (rearranged matrix for inverse)
    if(d != 0.0f) {   
        *x = (int)((st2 * r1 - st1 * r2) / d);
        *y = (int)(( - ct2 * r1 + ct1 * r2) / d);
        return 1;
    } 
    else { // If lines are parallel and will NEVER intersect!
        return 0;
    }
}