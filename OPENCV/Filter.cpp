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
void Solution::mergeImages(Mat& dst, vector<Mat>& images,int cols,int rows)
{
    assert((int)images.size()>0);
    int imgCount=(int)images.size();
    for (int i = 0; i < imgCount; i++)
        resize(images[i], images[i], Size(cols, rows));
    
    dst.create(rows * imgCount / 2, cols * 2, CV_8UC3);
    
    for (int i = 0; i < imgCount; i++)
        images[i].copyTo(dst(Rect((i % 2) * cols, (i / 2)*rows, images[0].cols, images[0].rows)));
}
Mat Solution::addGuassianNoise(Mat& srcImage)
{
    Mat resultImage = srcImage.clone(); // 克隆一副与源图像尺寸类型一样的图像
    int channels = resultImage.channels();//获取图像的通道
    int nRows = resultImage.rows;    //图像的行数
    int nCols = resultImage.cols*channels;//图像的总列数
    //判断图像的连续性
    if (resultImage.isContinuous())     //判断矩阵是否连续，若连续，我们相当于只需要遍历一个一维数组
    {
        nCols *= nRows;
        nRows = 1;
    }
    //遍历图像中的像素
    for (int i = 0; i < nRows; ++i)
    {
        for (int j = 0; j < nCols; ++j)
        {
            //添加高斯噪声
            int val = resultImage.ptr<uchar>(i)[j] + generateGaussianNoise(2, 0.8) * 32;
            if (val < 0)
                val = 0;
            if (val > 255)
                val = 255;
            resultImage.ptr<uchar>(i)[j] = (uchar)val;
        }
    }
    return resultImage;
}
double Solution::generateGaussianNoise(double mu, double sigma)
{
    
    const double epsilon =std::numeric_limits<double>::min();//返回目标数据类型能表示的最逼近1的正数和1的差的绝对值
    static double z0, z1;
    static bool flag = false;
    flag = !flag;
    //flag为假，构造高斯随机变量X
    if (!flag)
    {
        return z1*sigma + mu;
    }
    double u1, u2;
    //构造随机变量
    do
    {
        u1 = rand()*(1.0 / RAND_MAX);
        u2 = rand()*(1.0 / RAND_MAX);
    } while (u1 <= epsilon);
    //flag为真，构造高斯随机变量X
    z0 = sqrt(-2.0*log(u1))*cos(2 * CV_PI*u2);
    z1 = sqrt(-2.0*log(u1))*sin(2 * CV_PI*u2);
    return z0*sigma + mu;
}
