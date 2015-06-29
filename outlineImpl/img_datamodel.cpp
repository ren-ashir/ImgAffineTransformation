/*
 * img_provider.cpp
 * This source code is completely free.
 * 2015, Renat Ashirbakiev
 * r.robotman@yandex.ru - Russia->Moscow
 * https://github.com/ren-ashir/ImgAffineTransformation/
*/

#include <chrono>
#include "img_datamodel.h"


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

QPixmap imgznd::DataModel::getOpenCvRotatedQPixmap()
{ //  imgznd::algoOpenCvZoom(img,2);
    img.readImage(path);
    double angle = -38.0;
    TIMEF(imgznd::algoOpenCvRotate(img,img,angle,1));
    return imgznd::algoCvMatToQPixmap(img);
}

QPixmap imgznd::DataModel::getOneThreadCpuRotatedQPixmap()
{ // todo: add a time RAII class
    img.readImage(path);
    double angle = 37.0;
    raiiTimeMeasure tm(lastoptime);
    return imgznd::algoOneThreadCpuRotateQPixmap(img,angle);
}

QPixmap imgznd::DataModel::getMultithreadRoratedQpixmap()
{ // todo: add a time RAII class
    img.readImage(path);
    double angle = 35.0;
    raiiTimeMeasure tm(lastoptime);
    return imgznd::algoMultiThreadRorateQpixmap(img,angle);
}

double imgznd::DataModel::lastOperationTime()
{
    return lastoptime;
}

void imgznd::DataModel::saveButtonPushed()
{
    img.saveToFile("output.jpg");
}
