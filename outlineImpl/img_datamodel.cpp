/*
 * img_provider.cpp
 * This source code is completely free.
 * 2015, Renat Ashirbakiev
 * r.robotman@yandex.ru - Russia->Moscow
 * https://github.com/ren-ashir/ImgAffineTransformation/
*/

#include <chrono>
#include "img_datamodel.h"
#include <cuda_runtime.h>

imgznd::DataModel::DataModel() : lastoptime{0.0}
{
    path = imgznd::getJpgLink(); // default
    img.readImage(path);
}

void imgznd::DataModel::setPath(const std::string &p)
{
    path = p;
}

std::string imgznd::DataModel::getPath() const
{
    return path;
}

void imgznd::DataModel::onLoadButtonClicked()
{
    img.readImage(path);
}

QPixmap imgznd::DataModel::getStrightforwardQPixmap()
{
    TIMEF(img.readImage(path));
    return imgznd::algoCvMatToQPixmap(img);
}

QPixmap imgznd::DataModel::getOpenCvRotatedQPixmap(double deg)
{ //  imgznd::algoOpenCvZoom(img,2);
    img.readImage(path);
    //double angle = deg;
    TIMEF(imgznd::algoOpenCvRotate(img,img,-deg,1));
    return imgznd::algoCvMatToQPixmap(img);
}

QPixmap imgznd::DataModel::getOneThreadCpuRotatedQPixmap(double deg)
{ // todo: add a time RAII class
    img.readImage(path);
   // double angle = 37.0;
    raiiTimeMeasure tm(lastoptime);
    return imgznd::algoOneThreadCpuRotateQPixmap(img,deg);
}

QPixmap imgznd::DataModel::getMultithreadRoratedQpixmap(double deg)
{ // todo: add a time RAII class
    img.readImage(path);
   // double angle = 35.0;
    raiiTimeMeasure tm(lastoptime);
    return imgznd::algoMultiThreadRorateQpixmap(img,deg);
}

QPixmap imgznd::DataModel::getCUDARotatedPixmap(double deg)
{
    raiiTimeMeasure tm(lastoptime);
    try{
        qDebug() << "CUDA start\n";
        cudaError_t cuerr = imgznd::algoCuda_main();
        if (cuerr != cudaSuccess)
            qDebug() << "CUDA Error: " << cudaGetErrorString( cuerr ) << endl;
        qDebug() << "CUDA end\n";
    }
    catch(...)
    {
        qDebug() << "CUDA error\n";
    }
    qDebug() << "CUDA OK";
    return QPixmap();
}

double imgznd::DataModel::lastOperationTime()
{
    return lastoptime;
}

void imgznd::DataModel::saveButtonPushed()
{
    img.saveToFile("output.jpg");
}
