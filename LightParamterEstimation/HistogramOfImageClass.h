//
//  HistogramOfImage.h
//  LightParamterEstimation
//
//  Created by Pratheba Selvaraju on 7/24/15.
//  Copyright (c) 2015 Pratheba Selvaraju. All rights reserved.
//

#ifndef __LightParamterEstimation__HistogramOfImageClass__
#define __LightParamterEstimation__HistogramOfImageClass__

#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

typedef std::vector<cv::Point2d> VecOf2dPoints;
typedef std::vector<cv::Mat> VecOfMat;
typedef std::vector<int> VecOfInt;

class HistogramOfImageClass {
    
public:
    HistogramOfImageClass();
    ~HistogramOfImageClass();
    
    VecOfInt        GetHistogramOfImage(const cv::Mat& inputImage);
    void            GetMaxAndMinPixelIntensities(double& maxIntensity, double& minIntensity);
    void            DisplayHistogramOfImage();
    VecOf2dPoints   GetAllPixelswithinMaxIntensityRange();
    
    
private:
    cv::Mat inputImage;
    
    /*** Uncomment and Use if dealing with image of 3-channels ****/
    /*
    VecOfMat histogram;
    std::vector<std::vector< VecOf2dPoints>> pixelsOfHistogramBin;
    VecOfMat        histogramcanvas;
    VecOf2dPoints   pixelsOfMaxIntensity;
     */
    
    VecOfInt                        histogram;
    cv::Mat                         histogramcanvas;
    VecOf2dPoints                   pixelsOfMaxIntensity;
    std::vector< VecOf2dPoints >    pixelsOfHistogramBin;
    
    int numOfBins;
    int numOfChannels;
    
    double maxIntensity;
    double minIntensity;
    
    void initialize(const cv::Mat& inputImage);
};

#endif /* defined(__LightParamterEstimation__HistogramOfImageClass__) */
