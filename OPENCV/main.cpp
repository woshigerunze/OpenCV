
#include"Filter.hpp"
using namespace std;
using namespace cv;
int main(int argc, char **argv)
{
    Mat lhs=imread("/Users/gerunze/Pictures/timg.jpeg");
    Mat rhs=imread("/Users/gerunze/Pictures/timg1.jpeg");
    resize(lhs,lhs,Size(600,400));
    auto p=make_shared<Solution>();
    p->grayModify(lhs);
    imshow("gray", lhs);
    waitKey();
}
