//
//  UtilityClass.h
//  LightParamterEstimation
//
//  Created by Pratheba Selvaraju on 7/28/15.
//  Copyright (c) 2015 Pratheba Selvaraju. All rights reserved.
//

#ifndef LightParamterEstimation_UtilityClass_h
#define LightParamterEstimation_UtilityClass_h

#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

typedef std::vector<cv::Point2d> VecOf2dPoints;

class UtilityClass {
    
public:
    UtilityClass(const cv::Mat& inputImage_):inputImage(inputImage_) {
        
        if (inputImage.channels() > 1) {
            cv::cvtColor(inputImage, inputImage, CV_BGR2GRAY);
        }
        imageWidth = inputImage_.cols;
        imageHeight = inputImage_.rows;
    }
    
    ~UtilityClass() {}
    
    
    VecOf2dPoints GetWindowAroundPoint(const cv::Point2d& corePoint_, const int& windowSize_);
    void GetAveragePixelIntensityAroundaPoint(const cv::Point2d& corePoint_, const int& windowSize_, double& pixelIntensity_);
    
    
private:
    cv::Mat inputImage;
    int imageWidth;
    int imageHeight;
    int windowRadius;
};


#endif
