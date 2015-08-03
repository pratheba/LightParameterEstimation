//
//  ReprojectionClass.h
//  LightParamterEstimation
//
//  Created by Pratheba Selvaraju on 8/1/15.
//  Copyright (c) 2015 Pratheba Selvaraju. All rights reserved.
//

#ifndef __LightParamterEstimation__ReprojectionClass__
#define __LightParamterEstimation__ReprojectionClass__

#include <iostream>
#include "CameraClass.h"

class ReprojectionClass {
public:
    ReprojectionClass();
    ~ReprojectionClass();
    
    void ReprojectImagePixelsTo3DGeometry(const cv::Mat& imagePlane);
    
private:
    CameraClass* cameraClass;
    
    cv::Mat cameraIntrinsic;
    cv::Mat cameraRotation;
    cv::Point3d cameraCenter;
    
    void Intialize(const cv::Mat& imagePlane_);
    
};

#endif /* defined(__LightParamterEstimation__ReprojectionClass__) */
