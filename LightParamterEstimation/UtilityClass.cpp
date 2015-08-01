//
//  UtilityClass.cpp
//  LightParamterEstimation
//
//  Created by Pratheba Selvaraju on 7/29/15.
//  Copyright (c) 2015 Pratheba Selvaraju. All rights reserved.
//

#include "UtilityClass.h"


void UtilityClass::GetAveragePixelIntensityAroundaPoint(const cv::Point2d& corePoint_, const int& windowSize_, double& pixelIntensity_) {
    VecOf2dPoints pixelsAroundCorePoint = GetWindowAroundPoint(corePoint_, windowSize_);
    
    pixelIntensity_ = 0;
    
    if (pixelsAroundCorePoint.size() > 0) {
        for (int index = 0; index < pixelsAroundCorePoint.size(); ++index) {
            pixelIntensity_ += inputImage.at<uchar>(pixelsAroundCorePoint[index]);
        }
    }
    pixelIntensity_ += inputImage.at<uchar>(corePoint_);
    pixelIntensity_ /= (windowSize_ * windowSize_);
}


VecOf2dPoints UtilityClass::GetWindowAroundPoint(const cv::Point2d& corePoint, const int& windowSize_) {
    windowRadius = int(windowSize_/2);
    VecOf2dPoints pixelsAroundCorePoint;

    pixelsAroundCorePoint.clear();

    for(int row = -windowRadius; row <= windowRadius; ++row) {
        for (int col = -windowRadius; col <= windowRadius; ++col) {

            cv::Point2d currPoint = cv::Point2d(corePoint.x + row, corePoint.y + col);
            if ((currPoint.x < 0) || (currPoint.x > imageWidth)
            || (currPoint.y < 0) || (currPoint.y > imageHeight)
                || (row == 0 && col == 0)){
                continue;
            }
            pixelsAroundCorePoint.push_back(currPoint);
        }
    }

    return pixelsAroundCorePoint;
}