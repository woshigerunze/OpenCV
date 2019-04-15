//
//  Filter.cpp
//  OPENCV
//
//  Created by 葛润泽 on 2019/4/13.
//  Copyright © 2019 葛润泽. All rights reserved.
//

#include "Filter.hpp"


void Solution::saltNoise(Mat& src,int n)
{
    int i(0);
    int j(0);
    for (int k=0; k<n/2; k++) {
        i = std::rand()%src.cols;
        j = std::rand()%src.rows;
        if (src.type() == CV_8UC1)
        {
            src.at<uchar>(j,i)= 255;
        }
        else if (src.type() == CV_8UC3)
        {
            src.at<cv::Vec3b>(j,i)[0]= 255;
            src.at<cv::Vec3b>(j,i)[1]= 255;
            src.at<cv::Vec3b>(j,i)[2]= 255;
        }
    }
}

void Solution::pepperNoise(Mat& src,int n)
{
    int i(0);
    int j(0);
    for (int k=0; k<n; k++)
    {
        i = std::rand()%src.cols;
        j = std::rand()%src.rows;
        if (src.type() == CV_8UC1)
        {
            src.at<uchar>(j,i)= 0;
        }
        else if (src.type() == CV_8UC3)
        {
            src.at<cv::Vec3b>(j,i)[0]= 0;
            src.at<cv::Vec3b>(j,i)[1]= 0;
            src.at<cv::Vec3b>(j,i)[2]= 0;
        }
    }
}

void Solution::aveFilter(const Mat& src,Mat& dst,int _ksize)
{
    assert(_ksize%2==1);
    int w=_ksize*_ksize;
    _ksize=(_ksize-1)/2;
    for(int i=0;i<src.rows;i++)
        for(int j=0;j<src.cols;j++)
        {
            if((i-_ksize)>=0&&(j-_ksize)>=0&&(i+_ksize)<src.rows&&(j+_ksize)<src.cols)
            {
                int startrow(i-_ksize);
                int startcol(j-_ksize);
                int endrow(i+_ksize);
                int endcol(j+_ksize);
                int B=0;
                int G=0;
                int R=0;
                for(int x=startrow;x<=endrow;x++)
                    for(int y=startcol;y<=endcol;y++)
                    {
                        B+=src.at<Vec3b>(x,y)[0];
                        G+=src.at<Vec3b>(x,y)[1];
                        R+=src.at<Vec3b>(x,y)[2];
                    }
                dst.at<Vec3b>(i,j)[0]=B/w;
                dst.at<Vec3b>(i,j)[1]=G/w;
                dst.at<Vec3b>(i,j)[2]=R/w;
            }
            else
            {
                dst.at<Vec3b>(i,j)[0]=src.at<Vec3b>(i,j)[0];
                dst.at<Vec3b>(i,j)[1]=src.at<Vec3b>(i,j)[1];
                dst.at<Vec3b>(i,j)[2]=src.at<Vec3b>(i,j)[2];
            }
        }
}

void Solution::medianFilter(const Mat& src,Mat& dst,int _ksize)
{
    assert(_ksize%2==1);
    _ksize=(_ksize-1)/2;
    for(int i=0;i<src.rows;i++)
        for(int j=0;j<src.cols;j++)
        {
            if((i-_ksize)>=0&&(j-_ksize)>=0&&(i+_ksize)<src.rows&&(j+_ksize)<src.cols)
            {
                int startrow(i-_ksize);
                int startcol(j-_ksize);
                int endrow(i+_ksize);
                int endcol(j+_ksize);
                vector<int> B;
                vector<int> G;
                vector<int> R;
                for(int x=startrow;x<=endrow;x++)
                    for(int y=startcol;y<=endcol;y++)
                    {
                        B.push_back(src.at<Vec3b>(x,y)[0]);
                        G.push_back(src.at<Vec3b>(x,y)[1]);
                        R.push_back(src.at<Vec3b>(x,y)[2]);
                    }
                sort(B.begin(),B.end());
                sort(G.begin(),G.end());
                sort(R.begin(),R.end());
                dst.at<Vec3b>(i,j)[0]=B[B.size()/2];
                dst.at<Vec3b>(i,j)[1]=G[G.size()/2];
                dst.at<Vec3b>(i,j)[2]=R[R.size()/2];
            }
            else
            {
                dst.at<Vec3b>(i,j)[0]=src.at<Vec3b>(i,j)[0];
                dst.at<Vec3b>(i,j)[1]=src.at<Vec3b>(i,j)[1];
                dst.at<Vec3b>(i,j)[2]=src.at<Vec3b>(i,j)[2];
            }
        }
}
void Solution::grayModify(Mat& src)
{
    for_each(src.begin<Vec3b>(),src.end<Vec3b>(),[](auto& it)
             {
                 (it)[0]=((it)[0]*30+(it)[1]*59+(it)[2]*11)/100;
                 (it)[1]=((it)[0]*30+(it)[1]*59+(it)[2]*11)/100;
                 (it)[2]=((it)[0]*30+(it)[1]*59+(it)[2]*11)/100;
             });
}
void Solution::brightOrdarkModify(Mat& src,double ratio)
{
    for_each(src.begin<Vec3b>(),src.end<Vec3b>(),[&](auto& it)
             {
                 if(it[0]*ratio>=255)
                     it[0]=it[0];
                 else it[0]=it[0]*ratio;
                 if(it[1]*ratio>=255)
                     it[1]=it[1];
                 else it[1]=it[1]*ratio;
                 if(it[2]*ratio>=255)
                     it[2]=it[2];
                 else it[2]=it[2]*ratio;
             });
}
void Solution::negative(Mat& src)
{
    for_each(src.begin<Vec3b>(), src.end<Vec3b>(),[](auto& it)
             {
                 it[0]=255-it[0];
                 it[1]=255-it[1];
                 it[2]=255-it[2];
             });
}
Mat Solution::calcGrayHist(const Mat& src)
{
    int grayNum[256]={0};
    for(int i=0;i<src.rows;i++)
        for(int j=0;j<src.cols;j++)
        {
            grayNum[src.at<uchar>(i,j)]+=1;
        }
    Mat res(256,256,CV_8U, Scalar(255));
    int hpt=static_cast<int>(0.9*256);
    double maxVal=0.0;
    for(int i=0;i<256;i++)
    {
        if(grayNum[i]>maxVal)
            maxVal=grayNum[i];
    }
    for(int i=0;i<256;i++)
    {
        int binVal=grayNum[i];
        int intensify=static_cast<int>(binVal*hpt / maxVal);
        line(res, Point(i, 256),Point(i, 256 - intensify),Scalar::all(0));
    }
    return res;
}
