
#include"Filter.hpp"
using namespace std;
using namespace cv;


int main(int argc, char **argv)
{
    Mat img = imread("/Users/gerunze/Pictures/YXRR.jpg");
    Mat img1(img.size(), img.type());
    Mat img2(img.size(),img.type());
    salt(img, 6000);
    pepper(img, 6000);
    imshow("permitive",img);
    aveFilter(img, img1, 5);
    medianFilter(img, img2, 3);
    imshow("after avefilter",img1);
    imshow("after medianfilter",img2);
    waitKey();
}
