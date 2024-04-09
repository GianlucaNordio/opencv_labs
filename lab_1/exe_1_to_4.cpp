#include <iostream>
#include <list>
#include <sstream>
#include <opencv2/highgui.hpp>

void parseInput(std::list<std::string>& words, int argc, char** argv);

int main(int argc, char** argv) {
    cv::Mat img;
    if(argc < 2) {
        std::cout<<"Insert the name of an image!"<<std::endl;
        return -1;   
    }

    std::list<std::string> imgsName = {};
    parseInput(imgsName, argc, argv);

    int count = 0;
    for (auto iter : imgsName) {
        
        // imread and check
        img = cv::imread(iter);
        if (img.data == NULL) {
            std::cout<<"Image name not valid"<<std::endl;
            return -1;
        }

        // producing custom name
        std::ostringstream o;
        o << "Example" << ++count;
        std::string windowName = o.str();
        
        // create window
        cv::namedWindow(windowName);
        cv::imshow(windowName, img);
    }
    char waitKeyValue = cv::waitKey(0);

    // from now on for simplicity only the last image read is used
    std::cout << "Image channels: " << img.channels() << std::endl;
    std::cout << "You pressed: " << waitKeyValue << std::endl;

    std::vector<cv::Mat> channels;
    if(img.channels() != 3) {
        std::cout<<"Your image does not have 3 channels!" << std::endl <<"It has " << channels.size() << "channels!" <<std::endl;
    }

    // if we show only one channel we get greyscale because we have only one channel!
    cv::split(img, channels);
    cv::namedWindow("Single channel");
    cv::imshow("Single channel", channels[1]); 
    
    // opencv uses GBR
    channels[1].setTo(cv::Scalar(0));
    channels[0].setTo(cv::Scalar(0));
    

    // we see the specific color we are using only by using merge because we now consider an BGR image
    cv::merge(channels, img);
    cv::namedWindow("Merged");
    cv::imshow("Merged", img);
    cv::waitKey(0);
    
    return 0;
}

void parseInput(std::list<std::string>& words, int argc, char** argv) {
    for(int i = 1; i < argc; i++) {
        std::string temp(argv[i]);
        words.push_back(temp);
    }
}