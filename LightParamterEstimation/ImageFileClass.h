//
//  ImageFile.h
//  LightParamterEstimation
//
//  Created by Pratheba Selvaraju on 7/21/15.
//  Copyright (c) 2015 Pratheba Selvaraju. All rights reserved.
//

#ifndef __LightParamterEstimation__ImageFileClass__
#define __LightParamterEstimation__ImageFileClass__

#include <iostream>
#include "HistogramOfImageClass.h"
#include "DBSCAN_Class.h"


class ImageFileClass {
public:
    ImageFileClass();
    ~ImageFileClass();
    
    VecOf2dPoints GetCentroidOfHighIntensityPixelsinImage(const std::string& inputFileName_);
    
private:
    cv::Mat*                imageFile;
    VecOfInt*               histogramOfImage;
    HistogramOfImageClass*  histogramOfImageClass;
    DBSCAN_Class*           dbScanClass;
    
    std::vector<VecOf2dPoints>           clusteredPoints;
    
    void Initialize(const std::string& inputImageFileName);
    void ReadImageFile(const std::string& inputImageFileName);
    void WriteImageFile(const std::string& outputImageFileName);
    
};


#endif /* defined(__LightParamterEstimation__ImageFileClass__) */
