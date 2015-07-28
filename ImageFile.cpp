//
//  ImageFile.cpp
//  LightParamterEstimation
//
//  Created by Pratheba Selvaraju on 7/21/15.
//  Copyright (c) 2015 Pratheba Selvaraju. All rights reserved.
//

#include "ImageFile.h"

ImageFile::ImageFile() {
    imageData = nullptr;
    
    imageInfo.err = jpeg_std_error(&jpegErr);
    jpeg_create_decompress(&imageInfo);
    n_samples = 0;
    inputFile = new FILE();
}

void ImageFile::PlotHistogramOfImageIntensity() {
    if (imageData == nullptr) {
        std::cout << "No image data found to plot histogram" << std::endl;
        return;
    }
    
    histogramPixelCount = std::vector<int>(255,0);
    
    for (int row = 0; row < imageHeight; row++) {
        for (int col = 0; col < imageWidth; col++) {
            histogramPixelCount[imageData[row*imageWidth + col*3]]++;
        }
    }
    
    for(int index =100; index < 255; index++)
        std::cout << histogramPixelCount[index] << std::endl;
    
}

void ImageFile::WriteImageFile(const std::string &outputImageFileName) {
    
    outputImageInfo.err = jpeg_std_error(&jpegErr);
    jpeg_create_compress(&outputImageInfo);
    
    FILE* outputFile = fopen(outputImageFileName.c_str(),"wb");
    if(outputFile == NULL) {
        fprintf(stderr, "Cannot open input file %s \n", outputImageFileName.c_str());
        return;
    }
    jpeg_stdio_dest(&outputImageInfo, outputFile);
    
    outputImageInfo.image_width = imageWidth;
    outputImageInfo.image_height = imageHeight;
    outputImageInfo.input_components = channels;
    outputImageInfo.in_color_space = JCS_RGB;
    
    jpeg_set_defaults(&outputImageInfo);
    jpeg_start_compress(&outputImageInfo, TRUE);
    
    row_stride = imageWidth * 3;
    
    while (outputImageInfo.next_scanline < outputImageInfo.image_height) {
        imageDataRow = &imageData[outputImageInfo.next_scanline * row_stride];
        jpeg_write_scanlines(&outputImageInfo, &imageDataRow, 1);
    }
    
    jpeg_finish_compress(&outputImageInfo);
    jpeg_destroy_compress(&outputImageInfo);
    
    std::cout << "finish compressing" << std::endl;
}

void ImageFile::ReadImageFile(const std::string& inputImageFileName) {
    
    inputFile = fopen(inputImageFileName.c_str(),"rb");
    if(inputFile == NULL) {
        fprintf(stderr, "Cannot open input file %s \n", inputImageFileName.c_str());
        return;
    }
    
    jpeg_stdio_src(&imageInfo, inputFile);
    jpeg_read_header(&imageInfo, TRUE);
    jpeg_start_decompress(&imageInfo);
    
    imageWidth = imageInfo.output_width;
    imageHeight = imageInfo.output_height;
    channels = imageInfo.num_components;
    
    imageDataSize = imageWidth * imageHeight * channels;
    row_stride = imageWidth * channels;
    imageData = (unsigned char*)malloc(imageDataSize);
    
    imageDataArray = (JSAMPARRAY)malloc(sizeof(JSAMPROW));
    imageDataArray[0] = (JSAMPROW)malloc(sizeof(JSAMPLE)*row_stride);
    
    int counter = 0;
    while (imageInfo.output_scanline < imageInfo.output_height) {
        jpeg_read_scanlines(&imageInfo, imageDataArray, 1);
        memcpy(imageData+counter, imageDataArray[0], row_stride);
        counter += row_stride;
    }
    
    jpeg_finish_decompress(&imageInfo);
    jpeg_destroy_decompress(&imageInfo);
    
    std::cout << "finished decompressing" << std::endl;
    
}