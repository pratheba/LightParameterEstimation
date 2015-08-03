//
//  CameraClass.h
//  LightParamterEstimation
//
//  Created by Pratheba Selvaraju on 8/1/15.
//  Copyright (c) 2015 Pratheba Selvaraju. All rights reserved.
//

#ifndef __LightParamterEstimation__CameraClass__
#define __LightParamterEstimation__CameraClass__

#include <iostream>
#include <opencv2/core/core.hpp>
#include <vtkPLYReader.h>
#include <vector>
#include <cmath>

class CameraClass {
public:
    CameraClass(const cv::Mat& imagePlane_);
    ~CameraClass();
    
    cv::Mat GetCameraIntrinsicMatrix();
    cv::Mat GetCameraExtrinsicMatrix();
    cv::Mat GetProjectionMatrix();
    
    
private:
    
    struct CameraIntrinsic {
        
        CameraIntrinsic(cv::Mat& imagePlane_) {
            imagePlane = imagePlane_;
            focalLength = {35,35};
            sensorWidth = 32;
            fieldOfView = 49.13434;
            principlePoint = {0,0};
            skew = 0;
        }
        
        cv::Mat imagePlane;
        cv::Point2d focalLength;
        cv::Point2d principlePoint;
        double sensorWidth;
        double fieldOfView;
        double skew;
        
        double GetFocalLengthInPixel();
        cv::Mat GetCameraIntrinsicMatrix();
        
    }*CameraIntrinsicObj;
    
    struct CameraExtrinsic {
        
        CameraExtrinsic() {
            positionVector      =   { 1.4600005149841309, 1.9800000190734863, 5.657866477966309 };
            scaleVector         =   {  1.0, 1.0, 1.0 };
            eulerRotationAngles =   {  -0.3157657980918884, 0.02314339205622673, -0.07478136569261551};
        }
        
        cv::Vec3d positionVector;
        cv::Vec3d scaleVector;
        cv::Vec3d eulerRotationAngles;
        
        cv::Mat     rotationMatrix;
        cv::Vec3f   translationMatrix;
        cv::Mat GetRotationMatrixGivenRotationEuler(const cv::Vec3d& eulerRotationAngles);
        cv::Mat GetRotationMatrixGivenRotationEuler();
        
        cv::Mat GetCameraExtrinsicMatrix();
        
    }*CameraExtrinsicObj;
    
    cv::Vec3d GetPositionVectorOfCamera();
    
    cv::Mat GetRotationMatrixGivenRotationEuler(const cv::Vec3d& rotationEuler_);
    cv::Mat GetRotationMatrixGivenLookAtvector(const std::vector<cv::Vec3b>& lookAtVector);
    
    std::vector<cv::Vec3b> lookAtVector;
    cv::Mat imagePlane;
};

#endif /* defined(__LightParamterEstimation__CameraClass__) */
