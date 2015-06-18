#include <QCoreApplication>
#include "img_provider.h"
#include "img_representation.h"
#include <iostream>

using namespace std;
int main(int argc, char *argv[])
{
    try{
        cout << img_provider::getPngLink() << '\n';
        cout << img_provider::getTifLink() << '\n';
        cout << img_provider::getJpgLink() << '\n';
        img_repr::OpenCvImgRepr img(img_provider::getJpgLink());

        //cv::Vec3b intens = img.at<cv::Vec3b>(0,0);
        //cout << "RGB: " << int(intens.val[0]) << " " << int(intens.val[1]) << " " << int(intens.val[2]);
        //// img.oper
        //intens.val[0] = 0;
        //intens.val[1] = 0;
        //intens.val[2] = 0;
       // img.at<double>(0,0) = 0;
        // img.at<cv::Vec3b>(0,0) = intens;
        img.saveToFile("jpgpng.png");
    }
    catch(std::bad_alloc &ba)
    {
        std::cerr << "bad_alloc caught: " << ba.what() << '\n';
    }
    catch(...)
    {
        std::cerr << "Unknown exception\n";
    }
    return 0;
}

/*
 *
 *         //    cv::Mat img2 = cv::imread("/home/s/Desktop/20100813072157.tif");
        //    cout << img2.cols;
        //    cv::imwrite("new.tif",img2);

 */
