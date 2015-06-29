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

void blockSubmatrixOp(imgznd::OpenCvImgRepr &matrix_dst,imgznd::OpenCvImgRepr &matrix_src,int rowStart,int rowEnd,double sinteta,double costeta)
{
    const int ns = matrix_src.rows,
            ms = matrix_src.cols;
    for (int i = rowStart; i < rowEnd; ++i)
    {
        for (int j = 0; j < ms; ++j)
        {
            //rotate relative to the middle
            double x = i - ns / 2.0,
                    y = j - ms / 2.0;
            //calc new coords
            int xn = x * costeta + y * sinteta,
                    yn = -x * sinteta + y * costeta;

            xn += ns / 2.0;
            yn += ms / 2.0;
            if (xn >= 0 && xn < ns && yn >= 0 && yn < ms)
            {
                cv::Vec3b bgrPixel = matrix_src.at<cv::Vec3b>(i, j);
                matrix_dst.at<cv::Vec3b>(xn,yn) = bgrPixel;
            }
        }

    }
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
        blockSubmatrixOp (newImgone,img,0,img.rows,sinteta,costeta);
    }
    catch(...)
    {
        qDebug () << "oopps an one thread rotation fail";
        throw;
    }

    TIMEEND;
    return imgznd::cvMatToQPixmap(newImgone);
}

QPixmap imgznd::DataModel::getMultithreadRoratedQpixmap()
{
    img.readImage(path);
    double angle = 1.0;
    double sinteta = std::sin (angle);
    double costeta = std::cos (angle);
    imgznd::OpenCvImgRepr newImgone(img.size(),img.type());
    qDebug () << "Cur size: " << img.rows << img.cols;
    TIMESTART;
    try{
        const int minblocksize = 25,
                nthreads = (newImgone.rows + minblocksize - 1) / minblocksize,
                hardwarethreads = std::thread::hardware_concurrency(),
                realnthreads = std::min (hardwarethreads == 0 ? 2 : hardwarethreads, nthreads),
                realblocksize = newImgone.rows / realnthreads;
        std::vector<std::thread> threads (realnthreads - 1);
        qDebug () << "block size: " << realblocksize;
        int start = 0;
        for (int i = 0; i < realnthreads - 1; ++i)
        {
            threads[i] = std::thread(blockSubmatrixOp,std::ref(newImgone),std::ref(img),start,start + realblocksize,sinteta,costeta);
            start += realblocksize;
        }
        blockSubmatrixOp (newImgone,img,start,newImgone.rows,sinteta,costeta);
        for (auto &thrd: threads) thrd.join();
        //std::for_each(threads.begin(),threads.end(),mem_fn(&std::thread::join));
    }
    catch(...)
    {
        qDebug () << "oopps multi thread rotation fail";
        throw;
    }
    TIMEEND;
    return imgznd::cvMatToQPixmap(newImgone);
}

double imgznd::DataModel::lastOperationTime()
{
    return lastoptime;
}
