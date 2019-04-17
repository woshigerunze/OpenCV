
#include"Filter.hpp"
using namespace std;
using namespace cv;
int main(int argc, char **argv)
{
    Mat lhs=imread("/Users/gerunze/Pictures/timg.jpeg");
    Mat rhs=imread("/Users/gerunze/Pictures/timg1.jpeg");
    resize(lhs,lhs,Size(400,300));
    resize(rhs,rhs,Size(400,300));
    auto p=make_shared<Solution>();
    imshow("1",lhs);
    lhs=p->addGuassianNoise(lhs);
    imshow("2",lhs);
    waitKey();
}
