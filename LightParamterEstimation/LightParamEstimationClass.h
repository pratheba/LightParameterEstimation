//
//  LightParamEstimation.h
//  LightParamterEstimation
//
//  Created by Pratheba Selvaraju on 7/26/15.
//  Copyright (c) 2015 Pratheba Selvaraju. All rights reserved.
//

#ifndef __LightParamterEstimation__LightParamEstimation__
#define __LightParamterEstimation__LightParamEstimation__

#include <iostream>
#include "ImageFileClass.h"
#include "LightFallOffEstimationClass.h"


class LightParamEstimationClass {
public:
    //static LightParamEstimationClass* GetInstance(const std::string& inputFileName_);
    static LightParamEstimationClass* GetInstance();
    void        Release();
    
    //void GetAlphaOfLight();
    void GetAlphaOfLight(const std::string& inputFileName_);
    
private:
    static LightParamEstimationClass* lightParamEstimationClass;
    LightParamEstimationClass();
    ~LightParamEstimationClass();
    
    cv::Mat inputImage;
    ImageFileClass* imageFileClass;
    LightFallOffEstimationClass* lightFallOffEstimationClass;
    
    
    void Initialize(const std::string& inputFileName_);
    
    
};

#endif /* defined(__LightParamterEstimation__LightParamEstimation__) */
