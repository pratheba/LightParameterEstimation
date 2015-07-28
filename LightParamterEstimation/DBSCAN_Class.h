//
//  DBSCAN.h
//  LightParamterEstimation
//
//  Created by Pratheba Selvaraju on 7/25/15.
//  Copyright (c) 2015 Pratheba Selvaraju. All rights reserved.
//

#ifndef __LightParamterEstimation__DBSCAN_Class__
#define __LightParamterEstimation__DBSCAN_Class__

#include <iostream>
#include <opencv2/core/core.hpp>
#include <vector>

typedef std::vector<cv::Point2d> VecOf2dPoints;
typedef std::vector<int> VecOfInt;
typedef std::vector<bool> VecOfBool;

class DBSCAN_Class {
public:
    DBSCAN_Class();
    ~DBSCAN_Class();
    
    void ClusterDataPoints(const VecOf2dPoints _data, double _epsilon, int _minPoints);
    std::vector<VecOf2dPoints> GetClusteredPoints();
    void GetCentroidOfClusteredPoints(VecOf2dPoints& centroidPoints);
    
private:
    
    enum POINT_TYPE {
        CLUSTER,
        NOISE
    };
    
    VecOf2dPoints data;
    //std::vector< std::vector <cv::Point2d>> neighbourPoints;
    std::vector<VecOfInt> neighbourPoints;
    VecOfBool isVisited;
    VecOfBool isMemberOfCluster;
    std::vector<POINT_TYPE> dataPointType;
    
    cv::Point2d corePoint;
    //std::vector<cv::Point2d> corePointNeighbours;
    VecOfInt corePointNeighbours;
    std::vector<VecOf2dPoints> clusterPoints;
    double epsilon;
    int minPoints;
    
    
    void Initialize(VecOf2dPoints _data, double _epsilon, int _minPoints);
    void ClusterDataPoints();
    void GetAllNeighbouringPointsWithinRadius();
    VecOf2dPoints GetNeighbouringPoints(cv::Point2d corePoint);
    void ExpandCluster(const int clusterIndex);
    
};
#endif /* defined(__LightParamterEstimation__DBSCAN_Class__) */
