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
    return imgznd::cvMatToQPixmap(img);
}

QPixmap imgznd::DataModel::getOpenCvRotatedQPixmap()
{
    img.readImage(path);
    TIMEF(imgznd::openCvRotate(img,img,30,1));
    return imgznd::cvMatToQPixmap(img);
}

QPixmap imgznd::DataModel::getOneThreadCpuRotatedQPixmap()
{
    img.readImage(path);
    double angle = 1.0;
    double sinteta = std::sin (angle);
    double costeta = std::cos (angle);
    imgznd::OpenCvImgRepr newImgone(img.size(),img.type());
    qDebug () << "Cur size: " << img.rows << img.cols;
    TIMESTART;
    try{
        for (int i = 0; i < img.rows; ++i){
            for (int j = 0; j < img.cols; ++j)
            {
                double x = i - img.rows / 2.0,
                        y = j - img.cols / 2.0;
                int xn = x * costeta + y * sinteta,
                        yn = -x * sinteta + y * costeta;
                xn = xn + img.rows / 2.0;
                yn = yn + img.cols / 2.0;
                if (xn >= 0 && xn < img.rows && yn >= 0 && yn < img.cols)
                {
                    cv::Vec3b bgrPixel = img.at<cv::Vec3b>(i, j);
                    newImgone.at<cv::Vec3b>(xn,yn) = bgrPixel;
                }
            }
        }
    }
    catch(...)
    {
        qDebug () << "oopps";
    }

    TIMEEND;
    return imgznd::cvMatToQPixmap(newImgone);
}

double imgznd::DataModel::lastOperationTime()
{
    return lastoptime;
}
