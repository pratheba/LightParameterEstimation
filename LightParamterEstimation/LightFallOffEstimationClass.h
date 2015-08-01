//
//  LightFallOffEstimationClass.h
//  LightParamterEstimation
//
//  Created by Pratheba Selvaraju on 7/27/15.
//  Copyright (c) 2015 Pratheba Selvaraju. All rights reserved.
//

#ifndef __LightParamterEstimation__LightFallOffEstimationClass__
#define __LightParamterEstimation__LightFallOffEstimationClass__

#include <iostream>
#include "UtilityClass.h"

class LightFallOffEstimationClass {
public:
    LightFallOffEstimationClass();
    ~LightFallOffEstimationClass();
    
    void GetLightFallOffPointsfromCorePoints(const cv::Mat& inputImage_, const cv::Point2d& corePoint_);
private:
    
    VecOf2dPoints   fallOffPoints;
    cv::Mat*        inputImage;
    cv::Point2d*    corePoint;
    int             imageWidth;
    int             imageHeight;
    
    UtilityClass* utilityClass;
    
    void Initialize(const cv::Mat& inputImage_, const cv::Point2d& corePoint_);
};

#endif /* defined(__LightParamterEstimation__LightFallOffEstimationClass__) */
