
#include"Filter.hpp"
using namespace std;
using namespace cv;
int main(int argc, char **argv)
{
    Mat lhs=imread("/Users/gerunze/Pictures/timg.jpeg");
    Mat rhs=imread("/Users/gerunze/Pictures/timg1.jpeg");
    resize(lhs,lhs,rhs.size());
    auto p=make_shared<Solution>();
    p->negative(lhs);
    imshow("test", lhs);
    waitKey();
}
