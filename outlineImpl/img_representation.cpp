/*
 * img_provider.cpp
 * This source code is completely free.
 * 2015, Renat Ashirbakiev
 * r.robotman@yandex.ru - Russia->Moscow
 * https://github.com/ren-ashir/ImgAffineTransformation/
*/

#include "img_representation.h"
namespace imgznd
{
// public methods
OpenCvImgRepr::OpenCvImgRepr(const std::string &path) // : cv::Mat {cv::imread(path, 0)}
{
    readImage (path);
}
void OpenCvImgRepr::readImage(const std::string &path)
{
    if (!this->empty()){
        qDebug () << "released";
        this->release();
    }
    cv::Mat::operator =(cv::imread(path));// static_cast<cv::Mat&>(*this) = cv::imread(path);
    if (!this->data)
        throw std::bad_alloc{};
}
void OpenCvImgRepr::saveToFile(const std::string &path)
{
    cv::imwrite(path, *this);
}

const OpenCvImgRepr::CvArray1D OpenCvImgRepr::operator [](int index) const
{
    if (index >= cv::Mat::rows)
        throw std::out_of_range {"cv first index error"};
    return CvArray1D(cv::Mat::ptr<returnType>(index),cv::Mat::cols);
}

OpenCvImgRepr::CvArray1D OpenCvImgRepr::operator [](int index)
{ // get rid of the CvArray1D& in order to use the rvalue of a temprary object
    if (index >= cv::Mat::rows)
        throw std::out_of_range {"cv first index error"};
    return  CvArray1D(cv::Mat::ptr<returnType>(index),cv::Mat::cols);
}

OpenCvImgRepr::CvArray1D::CvArray1D(OpenCvImgRepr::returnType *ptr, int n) : arrayPtr{ptr},sizen{n} {}

OpenCvImgRepr::CvArray1D::CvArray1D(const OpenCvImgRepr::returnType *ptr, int n) : arrayPtr{const_cast<returnType*>(ptr)},sizen{n}{}

OpenCvImgRepr::returnType OpenCvImgRepr::CvArray1D::operator [](int index) const {
    if (index >= sizen)
        throw std::out_of_range {"cv second index error"};
    return arrayPtr[index];
}

OpenCvImgRepr::returnType &OpenCvImgRepr::CvArray1D::operator [](int index) {
    if (index >= sizen)
        throw std::out_of_range {"cv second index error"};
    return arrayPtr[index];
}

void QtImgRepr::readImage(const std::string &path)
{

}

void QtImgRepr::saveToFile(const std::string &path)
{

}


}
