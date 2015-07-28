//
//  main.cpp
//  LightParamterEstimation
//
//  Created by Pratheba Selvaraju on 7/21/15.
//  Copyright (c) 2015 Pratheba Selvaraju. All rights reserved.
//

#include <iostream>
#include <numeric>
#include "LightParamEstimationClass.h"

int main(int argc, const char * argv[]) {
    
    std::string inputFileName = "/Users/prathebaselvaraju/4-Projects/LightParamterEstimation/output.png";
    LightParamEstimationClass* lightParamEstimationClass = LightParamEstimationClass::GetInstance();
    
    lightParamEstimationClass->GetAlphaOfLight(inputFileName);    
    lightParamEstimationClass->Release();
    
    return 0;
}
