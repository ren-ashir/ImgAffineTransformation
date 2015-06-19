#include <QCoreApplication>
#include "img_provider.h"
#include "img_representation.h"
#include "img_algorithm.h"
#include <iostream>

using namespace std;
using namespace imgznd;
int main(int argc, char *argv[])
{
    try{


        OpenCvImgRepr img(getJpgLink()),imgOut;
        openCvRotate(img,imgOut,100,5);
        imgOut.saveToFile("rotate90.png");
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
