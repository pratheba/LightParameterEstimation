//
//  ImageFile.h
//  LightParamterEstimation
//
//  Created by Pratheba Selvaraju on 7/21/15.
//  Copyright (c) 2015 Pratheba Selvaraju. All rights reserved.
//

#ifndef __LightParamterEstimation__ImageFile__
#define __LightParamterEstimation__ImageFile__

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>


#include "jpeglib.h"


class ImageFile {
public:
    ImageFile();
    ~ImageFile(){}
    
    void ReadImageFile(const std::string& inputImageFileName);
    void WriteImageFile(const std::string& outputImageFileName);
    void PlotHistogramOfImageIntensity();
    
private:
    
    struct jpeg_decompress_struct imageInfo;
    struct jpeg_error_mgr jpegErr;
    struct jpeg_compress_struct outputImageInfo;
    
    FILE* inputFile;
    int imageWidth;
    int imageHeight;
    int row_stride;
    int channels;
    int n_samples;
    
    //int** histogramPixelCount;
    //int** histogramPixelsIndex;
    
    std::vector< int >histogramPixelCount;
    std::vector< int >numberOfPixelsInEachBin;
    std::vector< int >histogramPixelsIndex;
    
    
    unsigned long imageDataSize;
    unsigned char *imageData;

    JSAMPARRAY imageDataArray;
    JSAMPROW imageDataRow;
};


#endif /* defined(__LightParamterEstimation__ImageFile__) */
