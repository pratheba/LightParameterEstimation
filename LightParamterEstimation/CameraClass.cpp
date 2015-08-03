//
//  CameraClass.cpp
//  LightParamterEstimation
//
//  Created by Pratheba Selvaraju on 8/1/15.
//  Copyright (c) 2015 Pratheba Selvaraju. All rights reserved.
//

#include "CameraClass.h"



CameraClass::CameraClass(const cv::Mat& imagePlane_) {
    imagePlane = imagePlane_;
    CameraExtrinsicObj = new CameraExtrinsic();
    CameraIntrinsicObj = new CameraIntrinsic(imagePlane);
}

CameraClass::~CameraClass() {
    if (CameraExtrinsicObj != nullptr) {
        delete CameraExtrinsicObj;
        CameraExtrinsicObj = nullptr;
    }
    
    if (CameraIntrinsicObj != nullptr) {
        delete CameraIntrinsicObj;
        CameraIntrinsicObj = nullptr;
    }
}


cv::Vec3d CameraClass::GetPositionVectorOfCamera() {
    return CameraExtrinsicObj->positionVector;
}

cv::Mat CameraClass::GetRotationMatrixGivenRotationEuler(const cv::Vec3d& rotationEuler_) {
    return CameraExtrinsicObj->GetRotationMatrixGivenRotationEuler(rotationEuler_);
}

cv::Mat CameraClass::GetCameraIntrinsicMatrix() {
    return CameraIntrinsicObj->GetCameraIntrinsicMatrix();
}

cv::Mat CameraClass::GetCameraExtrinsicMatrix() {
    return CameraExtrinsicObj->GetCameraExtrinsicMatrix();
}

cv::Mat CameraClass::GetProjectionMatrix() {
    return CameraIntrinsicObj->GetCameraIntrinsicMatrix() * CameraExtrinsicObj->GetCameraExtrinsicMatrix();
}

cv::Mat CameraClass::CameraExtrinsic::GetRotationMatrixGivenRotationEuler(const cv::Vec3d& rotationEuler_) {
    
    CameraExtrinsic::eulerRotationAngles = rotationEuler_;
    return GetRotationMatrixGivenRotationEuler();
}

cv::Mat CameraClass::CameraExtrinsic::GetRotationMatrixGivenRotationEuler() {
    double CosTheta = cv::cos(eulerRotationAngles[0]);
    double SinTheta = cv::sin(eulerRotationAngles[0]);
    double RotZVector[] = {CosTheta, -SinTheta, 0, SinTheta, CosTheta, 0, 0, 0, 1};
    cv::Mat RotZ = cv::Mat(3,3,CV_8UC1,RotZVector);
    
    CosTheta = cv::cos(eulerRotationAngles[1]);
    SinTheta = cv::sin(eulerRotationAngles[1]);
    double RotYVector[] = {CosTheta, 0, SinTheta, 0, 1, 0 , -SinTheta, 0, CosTheta};
    cv::Mat RotY = cv::Mat(3,3,CV_8UC1, RotYVector);
    
    CosTheta = cv::cos(eulerRotationAngles[2]);
    SinTheta = cv::sin(eulerRotationAngles[2]);
    double RotXVector[] = {1,0,0,0,CosTheta, -SinTheta, 0, SinTheta, CosTheta};
    cv::Mat RotX = cv::Mat(3,3,CV_8UC1, RotXVector);
    
    rotationMatrix = RotZ * RotY * RotX;
    return rotationMatrix;
}

cv::Mat CameraClass::CameraExtrinsic::GetCameraExtrinsicMatrix() {
    cv::Mat camExtrinsics(3,4,CV_8UC1,cv::Scalar::all(0));
    cv::Mat rotationMatrix = GetRotationMatrixGivenRotationEuler();
    
    cv::Mat V = -1 * rotationMatrix * cv::Mat(positionVector, false);
    cv::Mat lastColumn(3,1,CV_8UC1,cv::Scalar::all(0));// = -1 * rotationMatrix .*  positionVector;
    V.copyTo(lastColumn);
    
    cv::vector<cv::Mat> matrices = { rotationMatrix, lastColumn };
    hconcat( matrices, camExtrinsics);
    
    return camExtrinsics;
    
}


cv::Mat CameraClass::CameraIntrinsic::GetCameraIntrinsicMatrix() {
    cv::Mat camIntrinsic;
    camIntrinsic.zeros(3,3,CV_8UC1);
    double focal_pixel = GetFocalLengthInPixel();
    
    camIntrinsic.at<uchar>(0,0) = focal_pixel;
    camIntrinsic.at<uchar>(1,1) = focal_pixel;
    camIntrinsic.at<uchar>(0,2) = imagePlane.rows/2;
    camIntrinsic.at<uchar>(1,2) = imagePlane.cols/2;
    camIntrinsic.at<uchar>(2,2) = 1;
    
    return camIntrinsic;
}

double CameraClass::CameraIntrinsic::GetFocalLengthInPixel() {
    
    // tan(theta/2) = (d/2*f)
    // f = d*0.5/(tan(theta*0.5)
    
    double focal_pixel = 0;
    if(sensorWidth != 0)
        focal_pixel = (focalLength.x / sensorWidth) * imagePlane.rows;
        else if(fieldOfView != 0)
            focal_pixel = (imagePlane.rows * 0.5)/(tan(fieldOfView*0.5)* (M_PI/360));
            return focal_pixel;
}


/*** MUST DO *** - Later ****/

//cv::Mat CameraClass::GetRotationMatrixGivenLookAtvector(const std::vector<cv::Vec3b>& lookAtVector) {
//    
//    cv::Vec3d positionVector = lookAtVector.at(0);
//    cv::Vec3d directionVector = lookAtVector.at(1);
//    cv::Vec3d UpVector = lookAtVector.at(2);
//    
//    cv::Vec3d XAxis, YAxis, ZAxis;
//    cv::normalize(directionVector, ZAxis);
//    cv::normalize(ZAxis.cross(UpVector), XAxis);
//    YAxis = XAxis.cross(ZAxis);
//    
//    return cv::Mat();
//}