#include <iostream>
#include <opencv2/highgui.hpp>

int main(int argc, char** argv) {
    cv::Mat hGrad = cv::Mat(256, 256, CV_8U);
    for(int i = 0; i < hGrad.rows; i++) {
        for(int j = 0; j < hGrad.cols; j++) {
            hGrad.at<unsigned char>(j, i) = i;  
        }
    }

    cv::imshow("horizontal gradient", hGrad);


    cv::Mat vGrad = cv::Mat(256, 256, CV_8U);
    for(int i = 0; i < vGrad.rows; i++) {
        for(int j = 0; j < vGrad.cols; j++) {
            vGrad.at<unsigned char>(j, i) = j;  
        }
    }
    cv::imshow("vertical gradient", vGrad);

    cv::Mat chessSmall = cv::Mat(256, 256, CV_8U);
    for(int i = 0; i < chessSmall.rows; i++) {
        for(int j = 0; j < chessSmall.cols; j++) {
            if((i/20)%2 != (j/20)%2) 
                chessSmall.at<unsigned char>(i,j) = 0;
            else
                chessSmall.at<unsigned char>(i,j) = 255;
        }
    }
    cv::imshow("vertical gradient", chessSmall);

    cv::Mat chessBig = cv::Mat(256, 256, CV_8U);
    for(int i = 0; i < chessBig.rows; i++) {
        for(int j = 0; j < chessBig.cols; j++) {
            if((i/50)%2 != (j/50)%2) 
                chessBig.at<unsigned char>(i,j) = 0;
            else
                chessBig.at<unsigned char>(i,j) = 255;
        }
    }
    cv::imshow("vertical gradient", chessBig);
    cv::waitKey(0);

}