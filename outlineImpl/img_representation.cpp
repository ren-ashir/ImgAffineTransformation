/*
 * img_representation.cpp
 * This source code is completely free.
 * Copyright (C) 2015, Renat Ashirbakiev
 * r.robotman@yandex.ru - Russia->Moscow
*/

#include "img_representation.h"
namespace img_repr
{
// public methods
OpenCvImgRepr::OpenCvImgRepr(const std::string &path) // : cv::Mat {cv::imread(path, 0)}
{
    readImage (path);
}
void OpenCvImgRepr::readImage(const std::string &path)
{
    if (!this->empty())
        this->release();
    static_cast<cv::Mat&>(*this) = cv::imread(path);
    if (!this->data)
        throw std::bad_alloc{};
}
void OpenCvImgRepr::saveToFile(const std::string &path)
{
    cv::imwrite(path, *this);
}
void QtImgRepr::readImage(const std::string &path)
{

}
void QtImgRepr::saveToFile(const std::string &path)
{

}

}
