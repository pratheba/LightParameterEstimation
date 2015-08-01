//
//  LightFallOffEstimationClass.cpp
//  LightParamterEstimation
//
//  Created by Pratheba Selvaraju on 7/27/15.
//  Copyright (c) 2015 Pratheba Selvaraju. All rights reserved.
//

#include "LightFallOffEstimationClass.h"
#define BLOCKSIZE 5

LightFallOffEstimationClass::LightFallOffEstimationClass():fallOffPoints(VecOf2dPoints()), inputImage(nullptr), corePoint(nullptr),
                    imageWidth(0), imageHeight(0), utilityClass(nullptr){
    
}

LightFallOffEstimationClass::~LightFallOffEstimationClass() {
    if (corePoint != nullptr) {
        delete corePoint;
        corePoint = nullptr;
    }
    
    if (inputImage != nullptr) {
        delete inputImage;
        inputImage = nullptr;
    }
    
    if (utilityClass != nullptr) {
        delete utilityClass;
        utilityClass = nullptr;
    }
    
    fallOffPoints.clear();
    imageWidth = 0;
    imageHeight = 0;
}

void LightFallOffEstimationClass::Initialize(const cv::Mat& inputImage_, const cv::Point2d& corePoint_) {
    
    if (corePoint == nullptr) {
        corePoint = new cv::Point2d();
    }
    
    if (inputImage == nullptr) {
        inputImage = new cv::Mat();
    }
    
    if (utilityClass == nullptr) {
        utilityClass = new UtilityClass(inputImage_);
    }
    
    *corePoint  =   corePoint_;
    *inputImage =   inputImage_;
    if (inputImage->channels() > 1) {
        cv::cvtColor(*inputImage, *inputImage, CV_BGR2GRAY);
    }
    
    imageWidth  =   inputImage_.cols;
    imageHeight =   inputImage_.rows;
}


void LightFallOffEstimationClass::GetLightFallOffPointsfromCorePoints(const cv::Mat& inputImage_, const cv::Point2d& corePoint_) {
    
    cv::Mat refImage = inputImage_;
//    cv::circle(refImage, cv::Point2d(corePoint_.x , corePoint_.y), 4, cv::Scalar(0,0,255), -1);
//    cv::circle(refImage, cv::Point2d(corePoint_.x -10 , corePoint_.y - 10), 4, cv::Scalar(0,255,255), -1);
//    
//    cv::imshow("falloffregion", refImage);
//    cv::waitKey();
    
    Initialize(inputImage_, corePoint_);
    
    cv::Point2d currPoint = *corePoint;
    int block = 1;
    double currBlockIntensity = 0;
    double prevBlockIntensity = 0;
    double currPixelWindowIntensity = 0;
    
    
    // Loop through 0 to 360
    for (int degree = 0; degree < 360; ++degree) {
        currPoint   =   *corePoint;
        block       =   1;
        currBlockIntensity = 0;
       
        std::cout << "*********** degree = " << degree << std::endl;
        while ((currPoint.x >= 0) && (currPoint.x < imageWidth) && (currPoint.y >= 0) && (currPoint.y < imageHeight)) {
            prevBlockIntensity = currBlockIntensity;
            currBlockIntensity = 0;
            
            for (int radius = block; radius <=(block+BLOCKSIZE); ++radius) {
                currPoint = *corePoint + cv::Point2d(radius*cv::cos(degree), radius*cv::sin(degree));
                if ((currPoint.x < 0) || (currPoint.x > imageWidth) || (currPoint.y < 0) || (currPoint.y > imageHeight)) {
                    break;
                }
                currPixelWindowIntensity = 0;
                utilityClass->GetAveragePixelIntensityAroundaPoint(currPoint, 3, currPixelWindowIntensity);
                currBlockIntensity += currPixelWindowIntensity;
                //currBlockIntensity += inputImage->at<uchar>(currPoint.y,currPoint.x);
            }
            currBlockIntensity /= BLOCKSIZE;
            
            double intensityDifference = prevBlockIntensity - currBlockIntensity;
            std::cout << "intensity difference  = " << intensityDifference << std::endl;
            //if ((intensityDifference > 2 && intensityDifference < 5) && (block != 1)) {
            if ((intensityDifference >= 5 && intensityDifference <= 8) && (block != 1)) {
                if ((currPoint.x >= 0) && (currPoint.x < imageWidth) && (currPoint.y >= 0) && (currPoint.y < imageHeight)) {
                    cv::circle(refImage, currPoint, 2, cv::Scalar(0,0,255), -1);
                }
            }
            
            if ((intensityDifference >= 10 && intensityDifference <= 15) && (block != 1)) {
                if ((currPoint.x >= 0) && (currPoint.x < imageWidth) && (currPoint.y >= 0) && (currPoint.y < imageHeight)) {
                    cv::circle(refImage, currPoint, 2, cv::Scalar(0,255,255), -1);
                }
            }
            
            block += BLOCKSIZE;
        }
    }
    
    cv::imwrite("/Users/prathebaselvaraju/4-Projects/LightParamterEstimation/input-output/output-light-final-1.png", refImage);
    cv::imshow("falloffregion", refImage);
    cv::waitKey();
    
    return;
}

