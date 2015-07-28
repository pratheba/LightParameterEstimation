//
//  LightParamEstimation.cpp
//  LightParamterEstimation
//
//  Created by Pratheba Selvaraju on 7/26/15.
//  Copyright (c) 2015 Pratheba Selvaraju. All rights reserved.
//

#include "LightParamEstimationClass.h"

LightParamEstimationClass* LightParamEstimationClass::lightParamEstimationClass = nullptr;


LightParamEstimationClass::LightParamEstimationClass():inputImage(cv::Mat()),imageFileClass(nullptr), lightFallOffEstimationClass(nullptr) {
}

LightParamEstimationClass::~LightParamEstimationClass(){
    if (imageFileClass != nullptr) {
        delete imageFileClass;
        imageFileClass = nullptr;
    }
    
    if (lightFallOffEstimationClass != nullptr) {
        delete lightFallOffEstimationClass;
        lightFallOffEstimationClass = nullptr;
    }
}

LightParamEstimationClass* LightParamEstimationClass::GetInstance() {
    if (lightParamEstimationClass == nullptr) {
        lightParamEstimationClass = new LightParamEstimationClass();
    }
    return lightParamEstimationClass;
}

void LightParamEstimationClass::Release() {
    if (lightParamEstimationClass != nullptr) {
        delete lightParamEstimationClass;
        lightParamEstimationClass = nullptr;
    }
}

void LightParamEstimationClass::Initialize(const std::string& inputFileName_) {
    if (inputImage.rows == 0 && inputImage.cols == 0) {
        inputImage = cv::imread(inputFileName_);
        
//        if (inputImage.channels() > 1) {
//            cv::cvtColor(inputImage, inputImage, CV_BGR2GRAY);
//        }
    }
    if (imageFileClass == nullptr) {
        imageFileClass = new ImageFileClass();
    }
    if (lightFallOffEstimationClass == nullptr) {
        lightFallOffEstimationClass = new LightFallOffEstimationClass();
    }
}

void LightParamEstimationClass::GetAlphaOfLight(const std::string& inputFileName_) {
    Initialize(inputFileName_);
    VecOf2dPoints centroids = imageFileClass->GetCentroidOfHighIntensityPixelsinImage(inputFileName_);
    lightFallOffEstimationClass->GetLightFallOffPointsfromCorePoints(inputImage, centroids[0]);
}