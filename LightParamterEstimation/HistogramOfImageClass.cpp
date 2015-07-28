//
//  HistogramOfImage.cpp
//  LightParamterEstimation
//
//  Created by Pratheba Selvaraju on 7/24/15.
//  Copyright (c) 2015 Pratheba Selvaraju. All rights reserved.
//

#include "HistogramOfImageClass.h"

HistogramOfImageClass::HistogramOfImageClass() :maxIntensity(DBL_MIN), minIntensity(DBL_MAX) {
    
}

void HistogramOfImageClass::initialize(const cv::Mat& _inputImage) {
    
    if(_inputImage.channels() > 1) {
        cv::cvtColor(_inputImage, inputImage, CV_BGR2GRAY);
        numOfChannels = inputImage.channels();
    }
    else {
        inputImage = _inputImage;
        numOfChannels = _inputImage.channels();
    }
    
    numOfBins = 256;
    
    // Uncomment if using with 3-Bit Channel
    
    /*
         histogram               =   std::vector<cv::Mat>(numOfChannels);
         histogramcanvas         =   std::vector<cv::Mat>(numOfChannels);
         pixelsOfHistogramBin    =   std::vector<std::vector<std::vector<cv::Point2d>>>(numOfChannels);
         pixelsOfMaxIntensity    =   std::vector<cv::Point2d>();
         
         for (int channel = 0; channel < numOfChannels; channel++) {
         histogram[channel]       =   cv::Mat(1, numOfBins, CV_8UC(channel),cv::Scalar::all(0));
         histogramcanvas[channel] =   cv::Mat(numOfBins, numOfBins, CV_8U, cv::Scalar(255));
         pixelsOfHistogramBin[channel]    =   std::vector<std::vector<cv::Point2d>>(256, std::vector<cv::Point2d>());
         }
     */
    
    histogram           =   VecOfInt(256,0);
    histogramcanvas     =   cv::Mat(numOfBins + 10 , numOfBins + 10, CV_8U, cv::Scalar::all(255));
    pixelsOfHistogramBin    =   std::vector<VecOf2dPoints>(256, VecOf2dPoints());
    pixelsOfMaxIntensity    =   VecOf2dPoints();
}

HistogramOfImageClass::~HistogramOfImageClass() {
    
}

void HistogramOfImageClass::GetMaxAndMinPixelIntensities(double& maxIntensity_, double& minIntensity_) {
    maxIntensity_ = maxIntensity;
    minIntensity_ = minIntensity;
}

VecOf2dPoints HistogramOfImageClass::GetAllPixelswithinMaxIntensityRange() {
    VecOf2dPoints pixelsWithMaxIntensityRange;
    pixelsWithMaxIntensityRange.clear();
    
    for (int intensity = maxIntensity; intensity > minIntensity; --intensity) {
        pixelsWithMaxIntensityRange.insert(pixelsWithMaxIntensityRange.end(), pixelsOfHistogramBin.at(intensity).begin(), pixelsOfHistogramBin.at(intensity).end());
        
        // remove the hardcoded value and use the
        // 1. imageSize
        // 2. Histogram -> get local maxima of pixels and find the intensity of each to evaluate how big the illumination is out
        //                  of the whole image. This way we get a fair idea of how many pixel counts we can have
        // to evaluate the amount of pixels.
        
        if (pixelsWithMaxIntensityRange.size() > 1000) {
            break;
        }
    }
    return pixelsWithMaxIntensityRange;
}

VecOfInt HistogramOfImageClass::GetHistogramOfImage(const cv::Mat& _inputImage) {
   
    initialize(_inputImage);
    int numOfRows = inputImage.rows;
    int numOfCols = inputImage.cols;
    
    if(numOfRows ==0 && numOfCols == 0) {
        std::cout << "Image not valid" << std::endl;
        return cv::Mat();
    }
    
    if (numOfChannels == 1) {
        for(int row =   0; row < numOfRows; row++) {
            for (int col = 0; col < numOfCols; col++) {
           
                int intensityValue = (int)inputImage.at<uchar>(row,col);
                histogram.at(intensityValue) += 1;
                
                //std::cout << "histogram at = " << intensityValue << " = " << histogram.at(intensityValue) << std::endl;
                if (pixelsOfHistogramBin.at(intensityValue).size() == 0) {
                    pixelsOfHistogramBin.at(intensityValue).clear();
                }
                pixelsOfHistogramBin.at(intensityValue).insert(pixelsOfHistogramBin.at(intensityValue).end(), cv::Point2d(row,col));
                
                // Get the max and min value of the pixel intensity
                if(maxIntensity < intensityValue)
                    maxIntensity = intensityValue;
                if (minIntensity > intensityValue)
                    minIntensity = intensityValue;
            }
        }
    }
    
    return histogram;
}

void HistogramOfImageClass::DisplayHistogramOfImage() {
    
    int maxPixel = INT_MIN;
    int minPixel = INT_MAX;
    
    if(numOfChannels == 1) {
        for(int row = 0 ; row < numOfBins ; row++) {
            int pixelsAtIntensity = histogram.at(row);
            
            if (maxPixel < pixelsAtIntensity)
                maxPixel = pixelsAtIntensity;
            if (minPixel > pixelsAtIntensity) {
                minPixel = pixelsAtIntensity;
            }
        }
    }
    
    //int highestPoint = static_cast<int>(0.9 * (numOfBins-1));
    int differenceBetweenMaxAndMin = maxPixel - minPixel;
    
    if(numOfChannels == 1) {
        for(int row = 0 ; row < numOfBins ; row++) {
            int pixelsAtIntensity = histogram.at(row);
            if (pixelsAtIntensity == 0) {
                pixelsAtIntensity = 1;
            }
            
            cv::line(histogramcanvas, cv::Point(row,numOfBins-1), cv::Point(row,  ((0.9 * (numOfBins-1) * (pixelsAtIntensity - minPixel)/differenceBetweenMaxAndMin))), cv::Scalar::all(0));
        }
    }
    
//    cv::line(histogramcanvas, cv::Point(10, 10), cv::Point(10, 40), cv::Scalar::all(0));
//    cv::line(histogramcanvas, cv::Point(20, 10), cv::Point(20, 20), cv::Scalar::all(0));

    //
//    std::cout << "histogram at 54 =" << histogram.at(255)  << std::endl;
//    cv::line(histogramcanvas, cv::Point(200,numOfBins-1), cv::Point(200,(0.9 * (numOfBins-1) * (histogram.at(255) - minPixel)/differenceBetweenMaxAndMin)), cv::Scalar::all(0));
    
    cv::namedWindow( "Histogram window", cv::WINDOW_AUTOSIZE );
    cv::imshow("Histogram window", histogramcanvas);
    cv::waitKey(0);
    return;
}
