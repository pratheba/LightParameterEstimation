
#include "ImageFileClass.h"


ImageFileClass::ImageFileClass():imageFile(nullptr),
                    histogramOfImageClass(nullptr),
                    histogramOfImage(nullptr),
                    dbScanClass(nullptr),
                    clusteredPoints(std::vector<VecOf2dPoints>()) {
}

ImageFileClass::~ImageFileClass() {
    if (imageFile != nullptr) {
        delete imageFile;
        imageFile = nullptr;
    }
    
    if (histogramOfImageClass != nullptr) {
        delete histogramOfImageClass;
        histogramOfImageClass = nullptr;
    }
    
    if (histogramOfImage != nullptr) {
        delete histogramOfImage;
        histogramOfImage = nullptr;
    }
    
    if (dbScanClass != nullptr) {
        delete dbScanClass;
        dbScanClass = nullptr;
    }
    
    for (int index = 0; index < clusteredPoints.size(); ++index) {
        clusteredPoints[index].clear();
    }
}

void ImageFileClass::Initialize(const std::string &inputImageFileName_) {
    if (imageFile == nullptr) {
        imageFile = new cv::Mat();
    }
    if (histogramOfImageClass == nullptr) {
        histogramOfImageClass = new HistogramOfImageClass();
    }
    if (histogramOfImage == nullptr) {
        histogramOfImage = new VecOfInt();
    }
    if (dbScanClass == nullptr) {
        dbScanClass = new DBSCAN_Class();
    }
}

void ImageFileClass::ReadImageFile(const std::string &inputImageFileName_) {

    *imageFile = cv::imread(inputImageFileName_, CV_LOAD_IMAGE_COLOR);
    //imageFile = cv::imread(inputImageFileName, CV_LOAD_IMAGE_GRAYSCALE);
    
    if(!(*imageFile).data )
    {
        std::cout <<  "Could not open or find the image" << std::endl ;
        delete imageFile;
        imageFile = nullptr;
    }
    return;
}

VecOf2dPoints ImageFileClass::GetCentroidOfHighIntensityPixelsinImage(const std::string &inputImageFileName_) {
    
    Initialize(inputImageFileName_);
    ReadImageFile(inputImageFileName_);
    
    VecOf2dPoints centroidPoints = VecOf2dPoints();
    
    if (imageFile == nullptr) {
        std::cout << "No Image file found. Please initialize and call the function again" << std::endl;
        return centroidPoints;
    }
    
    *histogramOfImage = histogramOfImageClass->GetHistogramOfImage(*imageFile);
    VecOf2dPoints pixelsOfMaxIntensities = histogramOfImageClass->GetAllPixelswithinMaxIntensityRange();
    
    dbScanClass->ClusterDataPoints(pixelsOfMaxIntensities, 4, 20);
    clusteredPoints = dbScanClass->GetClusteredPoints();
    dbScanClass->GetCentroidOfClusteredPoints(centroidPoints);
    
    return centroidPoints;
    
    
    //histogramOfImageClass->DisplayHistogramOfImage();
    
}


