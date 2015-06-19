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
//        openCvResizeBorder(img,100,100);
//        openCvRotate(img,imgOut,30,1);
//        imgOut.saveToFile("rotate-3.png");

        openCvZoom (img,9.0);
        img.saveToFile("filek.png");
    }
    catch(std::out_of_range &orn)
    {
        std::cerr << "out of range: " << orn.what() << "\n";
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
