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
template<typename T>
auto _plus(T _src,T _dst)->decltype((_src+_dst))
{
    if(_src+_dst>255)return 255;
    return (_src+_dst);
}
template<typename T>
auto _minus(T _src,T _dst)->decltype(_src-_dst)
{
    if(_src-_dst<0)return 0;
    return _src-_dst;
}
template<typename T>
auto _multi(T _src,T _dst)->decltype((_src*_dst)%256)
{
    return (_src*_dst)%256;
}
template<typename T>
auto _div(T _src,T _dst)->decltype(_src/_dst)
{
    if(_dst==0)return 0;
    return _src/_dst;
}
class Solution
{
public:
    template<typename FuncType>
    Mat operate(const Mat& lhs,const Mat& rhs,FuncType f)//图像的四则运算
    {
        assert(lhs.size()==rhs.size()&&lhs.type()==rhs.type());
        Mat res(lhs.size(),lhs.type());
        auto lhs_begin=lhs.begin<Vec3b>();
        auto rhs_begin=rhs.begin<Vec3b>();
        for_each(res.begin<Vec3b>(),res.end<Vec3b>(),[&](auto& it)
                 {
                    it[0]=f((*lhs_begin)[0],(*rhs_begin)[0]);
                    it[1]=f((*lhs_begin)[1],(*rhs_begin)[1]);
                    it[2]=f((*lhs_begin)[2],(*rhs_begin)[2]);
                    ++lhs_begin;
                    ++rhs_begin;
                 });
         return res;
    }
    void grayModify(Mat& src);//灰度化
    //void thresHold(Mat& src,int threshold);
    void brightOrdarkModify(Mat& src,double ratio);//图像变亮、变暗
    void negative(Mat& src);//图像负片
    //-------------------------------------------------------------------------
    Mat calcGrayHist(const Mat & image);//直方图
    //-------------------------------------------------------------------------
    void saltNoise(Mat& src,int n);//盐噪声
    void pepperNoise(Mat& src,int n);//椒噪声
    void gaussNoise(Mat& src);//高斯噪声
    void aveFilter(const Mat& src,Mat& dst,int _ksize);//均值滤波
    void medianFilter(const Mat& src,Mat& dst,int _ksize);//均值滤波
};
#endif /* Filter_hpp */
