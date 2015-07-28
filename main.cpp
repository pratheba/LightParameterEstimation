//
//  main.cpp
//  LightParamterEstimation
//
//  Created by Pratheba Selvaraju on 7/21/15.
//  Copyright (c) 2015 Pratheba Selvaraju. All rights reserved.
//

#include <iostream>
#include "ImageFile.h"
#include <opencv2/video/video.hpp>

int main(int argc, const char * argv[]) {
    ImageFile* imageFile = new ImageFile();
    imageFile->ReadImageFile("/Users/prathebaselvaraju/4-Projects/LightParamterEstimation/lightonplane-withtorus.jpeg");
    
    imageFile->PlotHistogramOfImageIntensity();
    imageFile->WriteImageFile("/Users/prathebaselvaraju/4-Projects/LightParamterEstimation/output.jpeg");
    
    delete imageFile;
    return 0;
}
