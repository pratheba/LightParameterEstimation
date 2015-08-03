//
//  main.cpp
//  LightParamterEstimation
//
//  Created by Pratheba Selvaraju on 7/21/15.
//  Copyright (c) 2015 Pratheba Selvaraju. All rights reserved.
//

#include <iostream>
#include <numeric>
//#include <vtkPolyData.h>
//#include <vtkPLYReader.h>
//#include <vtkSmartPointer.h>
//#include <vtkPolyDataMapper.h>
//#include <vtkActor.h>
//#include <vtkRenderWindow.h>
//#include <vtkRenderer.h>
//#include <vtkRenderWindowInteractor.h>

#include "LightParamEstimationClass.h"

int main(int argc, const char * argv[]) {
    
    std::string inputFileName = "/Users/prathebaselvaraju/4-Projects/LightParamterEstimation/light-final-1.png";
    LightParamEstimationClass* lightParamEstimationClass = LightParamEstimationClass::GetInstance();
    
    lightParamEstimationClass->GetAlphaOfLight(inputFileName);    
    lightParamEstimationClass->Release();
    
    return 0;
}
