//
//  ReprojectionClass.cpp
//  LightParamterEstimation
//
//  Created by Pratheba Selvaraju on 8/1/15.
//  Copyright (c) 2015 Pratheba Selvaraju. All rights reserved.
//

#include "ReprojectionClass.h"

ReprojectionClass::ReprojectionClass():cameraClass(nullptr) {
    
}

ReprojectionClass::~ReprojectionClass() {
    if (cameraClass != nullptr) {
        delete cameraClass;
        cameraClass = nullptr;
    }
}

void ReprojectionClass::Intialize(const cv::Mat& imagePlane_) {
    if (cameraClass == nullptr) {
        cameraClass = new CameraClass(imagePlane_);
    }
}

void ReprojectionClass::ReprojectImagePixelsTo3DGeometry(const cv::Mat& imagePlane_) {
    
    cv::Mat CamExtrinsic = cameraClass->GetCameraExtrinsicMatrix();
    cv::Mat CamIntrinsic = cameraClass->GetCameraIntrinsicMatrix();
    cv::Mat ProjectionMatrix = cameraClass->GetProjectionMatrix();

    
    cv::Mat homPoint(3,1,CV_8UC1);
    

    for (int row = 0; row < imagePlane_.rows; ++row) {
        for (int col = 0; col < imagePlane_.cols; ++col) {
            homPoint.at<uchar>(0,0) = row;
            homPoint.at<uchar>(1,0) = col;
            homPoint.at<uchar>(2,0) = 1;
            cv::Mat projPoint = ProjectionMatrix.inv() * homPoint;
        }
    }
    
    // P = KR[I|-C]
    
}