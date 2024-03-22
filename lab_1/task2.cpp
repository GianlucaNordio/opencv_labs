#include <iostream>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "ImageFilters.hpp"

cv::Mat histogramImage(cv::Mat& src, int buckets);

int main(int argc, char** argv) {
    // ----------- GARDEN -------------

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

    // Remove cables from garden
    cv::Mat gardenNoCables =  maxFilter(grsGarden, 5);
    cv::imshow("Garden image without cables", gardenNoCables);
    cv::waitKey(0);
    
    // ----------- LENA -------------
    // Read input image
    cv::Mat lenaOriginal;
    cv::Mat lenaCorrupted;
    lenaOriginal = cv::imread("imgs/Lena_original.png");
    lenaCorrupted = cv::imread("imgs/Lena_corrupted.png");
    if (lenaOriginal.data == NULL || lenaCorrupted.data == NULL) {
        std::cerr<<"Image name not valid"<<std::endl;
        return -1;
    }
    cv::cvtColor(lenaCorrupted, lenaCorrupted, cv::COLOR_RGB2GRAY);
    cv::cvtColor(lenaOriginal, lenaOriginal, cv::COLOR_RGB2GRAY);

    cv::imshow("Lena - original", lenaOriginal);

    cv::Mat lenaSideBySide;
    cv::Mat lenaFixed;

    // Max filter
    lenaFixed = maxFilter(lenaCorrupted, 3);
    cv::hconcat(lenaCorrupted, lenaFixed, lenaSideBySide);
    cv::imshow("Lena side by side - max filter", lenaSideBySide);

    // Min filter
    lenaFixed = minFilter(lenaCorrupted, 3);
    cv::hconcat(lenaCorrupted, lenaFixed, lenaSideBySide);
    cv::imshow("Lena side by side - min filter", lenaSideBySide);

    // Median filter
    lenaFixed = medianFilter(lenaCorrupted, 5);
    cv::hconcat(lenaCorrupted, lenaFixed, lenaSideBySide);
    cv::imshow("Lena side by side - median filter", lenaSideBySide);

    // Gaussian filter
    lenaFixed = gaussianFilter(lenaCorrupted, 9);
    cv::hconcat(lenaCorrupted, lenaFixed, lenaSideBySide);
    cv::imshow("Lena side by side - gaussian filter", lenaSideBySide);
    

    cv::waitKey(0);



    // ----------- ASTRONAUT -------------
    // Read input image
    cv::Mat astronautOriginal;
    cv::Mat astronautCorrupted;
    astronautOriginal = cv::imread("imgs/Astronaut_original.png");
    astronautCorrupted = cv::imread("imgs/Astronaut_salt_pepper.png");
    if (astronautOriginal.data == NULL || astronautCorrupted.data == NULL) {
        std::cerr<<"Image name not valid"<<std::endl;
        return -1;
    }
    cv::cvtColor(astronautCorrupted, astronautCorrupted, cv::COLOR_RGB2GRAY);
    cv::cvtColor(astronautOriginal, astronautOriginal, cv::COLOR_RGB2GRAY);

    cv::imshow("Astronaut - original", astronautOriginal);

    cv::Mat astronautSideBySide;
    cv::Mat astronautFixed;

    // Max filter
    astronautFixed = maxFilter(astronautCorrupted, 3);
    cv::hconcat(astronautCorrupted, astronautFixed, astronautSideBySide);
    cv::imshow("Astronaut side by side - max filter", astronautSideBySide);

    // Min filter
    astronautFixed = minFilter(astronautCorrupted, 3);
    cv::hconcat(astronautCorrupted, astronautFixed, astronautSideBySide);
    cv::imshow("Astronaut side by side - min filter", astronautSideBySide);

    // Median filter
    astronautFixed = medianFilter(astronautCorrupted, 5);
    cv::hconcat(astronautCorrupted, astronautFixed, astronautSideBySide);
    cv::imshow("Astronaut side by side - median filter", astronautSideBySide);

    // Gaussian filter
    astronautFixed = gaussianFilter(astronautCorrupted, 9);
    cv::hconcat(astronautCorrupted, astronautFixed, astronautSideBySide);
    cv::imshow("Astronaut side by side - gaussian filter", astronautSideBySide);


    cv::waitKey(0);

    // ----------- HISTOGRAM -------------
    cv::imshow("Garden initial histogram", histogramImage(grsGarden, 256));
    cv::Mat grsEqualizedGarden;
    cv::equalizeHist(grsGarden, grsEqualizedGarden);
    cv::imshow("Garden equalized histogram - 256 buckets",histogramImage(grsEqualizedGarden, 256));
     cv::imshow("Garden equalized histogram - 128 buckets",histogramImage(grsEqualizedGarden, 128));
    cv::waitKey(0);

    return 0;
}


cv::Mat histogramImage(cv::Mat& src, int buckets) {
    // creation of the histogram
    cv::Mat hist;
    float range[] = { 0, 255 };
    const float* histRange[] = { range };
    int histSize = buckets;
    cv::Mat vec[] = {src};
    int channels[] = {0};
    cv::calcHist(&vec[0], 1, channels, cv::Mat(), hist, 1, &histSize, histRange, true, false);
         
    // creation of the image to display the histogram
    // source of the code: https://docs.opencv.org/3.4/d8/dbc/tutorial_histogram_calculation.html
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double) hist_w/histSize);
    cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar( 0,0,0));
    cv::normalize(hist, hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
    for(int i = 1; i < histSize; i++) {
        line(histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ),
        cv::Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),
        cv::Scalar( 255, 0, 0), 2, 8, 0 );
    }
    return histImage;
}