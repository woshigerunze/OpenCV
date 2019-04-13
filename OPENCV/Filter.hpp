//
//  Filter.hpp
//  OPENCV
//
//  Created by 葛润泽 on 2019/4/13.
//  Copyright © 2019 葛润泽. All rights reserved.
//

#ifndef Filter_hpp
#define Filter_hpp

#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>        // 核心组件
#include<opencv2/highgui/highgui.hpp>  // GUI
#include<opencv2/imgproc/imgproc.hpp>  // 图像处理
#include<iostream>
#include<vector>
using namespace cv;
using namespace std;
void salt(Mat& src,int n);//盐噪声
void pepper(Mat& src,int n);//椒噪声
void aveFilter(const Mat& src,Mat& dst,int _kize);//均值滤波
void medianFilter(const Mat& src,Mat& dst,int _ksize);//均值滤波
#endif /* Filter_hpp */
