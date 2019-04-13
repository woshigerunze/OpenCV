//
//  Filter.cpp
//  OPENCV
//
//  Created by 葛润泽 on 2019/4/13.
//  Copyright © 2019 葛润泽. All rights reserved.
//

#include "Filter.hpp"
void salt(Mat& src,int n)
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

void pepper(Mat& src,int n)
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

void aveFilter(const Mat& src,Mat& dst,int size)
{
    assert(size%2==1);
    int w=size*size;
    size=(size-1)/2;
    for(int i=0;i<src.rows;i++)
        for(int j=0;j<src.cols;j++)
        {
            if((i-size)>=0&&(j-size)>=0&&(i+size)<src.rows&&(j+size)<src.cols)
            {
                int startrow(i-size);
                int startcol(j-size);
                int endrow(i+size);
                int endcol(j+size);
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

void medianFilter(const Mat& src,Mat& dst,int size)
{
    assert(size%2==1);
    size=(size-1)/2;
    for(int i=0;i<src.rows;i++)
        for(int j=0;j<src.cols;j++)
        {
            if((i-size)>=0&&(j-size)>=0&&(i+size)<src.rows&&(j+size)<src.cols)
            {
                int startrow(i-size);
                int startcol(j-size);
                int endrow(i+size);
                int endcol(j+size);
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
