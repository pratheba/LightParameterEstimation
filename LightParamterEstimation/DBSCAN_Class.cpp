//
//  DBSCAN.cpp
//  LightParamterEstimation
//
//  Created by Pratheba Selvaraju on 7/25/15.
//  Copyright (c) 2015 Pratheba Selvaraju. All rights reserved.
//

#include "DBSCAN_Class.h"

DBSCAN_Class::DBSCAN_Class():data(VecOf2dPoints()),
                neighbourPoints(std::vector<VecOfInt>()),
                isVisited(VecOfBool()),
                isMemberOfCluster(VecOfBool()),
                dataPointType(std::vector<POINT_TYPE>()),
                corePoint(cv::Point2d(-1,-1)),
                corePointNeighbours(VecOfInt()),
                clusterPoints(std::vector<VecOf2dPoints>()),
                epsilon(0.0), minPoints(0) {
    
}

DBSCAN_Class::~DBSCAN_Class() {
    
}

void DBSCAN_Class::Initialize(const VecOf2dPoints _data, double _epsilon, int _minPoints) {
    data        =   _data;
    epsilon     =   _epsilon;
    minPoints   =   _minPoints;
    
    size_t dataSize =   data.size();
    neighbourPoints =   std::vector<VecOfInt>(dataSize, VecOfInt());
    isVisited       =   VecOfBool(dataSize, false);
    isMemberOfCluster   =   VecOfBool(dataSize, false);
    dataPointType   =   std::vector<POINT_TYPE>(dataSize, CLUSTER);
}

void DBSCAN_Class::GetAllNeighbouringPointsWithinRadius() {
    for (int refPoint = 0; refPoint < (int)data.size(); refPoint++) {
        for(int currPoint = 0; currPoint < refPoint; currPoint++) {
            double distance = sqrt(pow(data[refPoint].x - data[currPoint].x, 2) +
                                   pow(data[refPoint].y - data[currPoint].y, 2));
            
            // Include intensity difference
            //if ((distance <= epsilon)  && (intensityDifference <= 5))

            if (distance <= epsilon) {
                neighbourPoints[currPoint].push_back(refPoint);
                neighbourPoints[refPoint].push_back(currPoint);
            }
        }
    }
}

void DBSCAN_Class::GetCentroidOfClusteredPoints(VecOf2dPoints& centroidPoints) {
    if (clusterPoints.size() == 0) {
        return;
    }
    centroidPoints.clear();
    
    int sumx = 0, sumy = 0;
    for (int cluster = 0; cluster < clusterPoints.size(); ++cluster) {
        for (int index = 0; index < clusterPoints[cluster].size(); index++) {
            sumx += clusterPoints[cluster][index].x;
            sumy += clusterPoints[cluster][index].y;
        }
        cv::Point2d centroid = cv::Point2d(sumy/clusterPoints[cluster].size(), sumx/clusterPoints[cluster].size());
        centroidPoints.push_back(centroid);
    }
}

std::vector<VecOf2dPoints> DBSCAN_Class::GetClusteredPoints() {
    return clusterPoints;
}

void DBSCAN_Class::ClusterDataPoints(const VecOf2dPoints _data, double _epsilon, int _minPoints) {
    Initialize(_data, _epsilon, _minPoints);
    GetAllNeighbouringPointsWithinRadius();
    ClusterDataPoints();
    
    std::cout << "clustered" << std::endl;
}

void DBSCAN_Class::ClusterDataPoints() {
    
    int clusterIndex = 0;
    
    for (int index = 0; index < data.size(); ++index) {
        if (isVisited[index]) {
            continue;
        }
        isVisited[index] = true;
        corePoint = data[index];
        corePointNeighbours = neighbourPoints.at(index);
        
        if(corePointNeighbours.size() < minPoints)
            dataPointType[index] = NOISE;
        else {
            std::vector<cv::Point2d> cluster;
            cluster.push_back(corePoint);
            clusterPoints.push_back(cluster);

            ExpandCluster(clusterIndex);
            clusterIndex++;
        }
    }
}

void DBSCAN_Class::ExpandCluster(const int clusterIndex) {
    
    int neighbourPointSize = (int)corePointNeighbours.size();
    for (int index = 0; index < neighbourPointSize; ++index) {
        
        if (!isVisited[corePointNeighbours[index]]) {
            isVisited[corePointNeighbours[index]] = true;
            
            std::vector<int> _neighbourPoints = neighbourPoints.at(corePointNeighbours[index]);
            if (corePointNeighbours.size() >= minPoints) {
                corePointNeighbours.insert(corePointNeighbours.end(), _neighbourPoints.begin(), _neighbourPoints.end());
                neighbourPointSize = (int)corePointNeighbours.size();
            }
        }
        
        if (!isMemberOfCluster[corePointNeighbours[index]] && (dataPointType[corePointNeighbours[index]] != NOISE)) {
            isMemberOfCluster[corePointNeighbours[index]] = true;
            clusterPoints[clusterIndex].push_back(data[corePointNeighbours[index]]);
        }
    }
}

