/*
 * img_representation.h
 * This source code is completely free.
 * Copyright (C) 2015, Renat Ashirbakiev
 * r.robotman@yandex.ru - Russia->Moscow
*/

#ifndef IMG_REPRESENTATION_H
#define IMG_REPRESENTATION_H

#include <exception>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/gpu/gpu.hpp>

namespace img_repr
{
// interface for a different implementation of the img data
class AbsImgRepr
{
public:
    virtual void readImage (const std::string& path) = 0;
    virtual void saveToFile (const std::string& path) = 0;
    virtual ~AbsImgRepr() {}
};

class OpenCvImgRepr : public AbsImgRepr, public cv::Mat
{
public:
    using cv::Mat::Mat;
    OpenCvImgRepr (const std::string &path);
    void readImage (const std::string &path) override;
    void saveToFile(const std::string &path) override;
};

class QtImgRepr : public AbsImgRepr
{ // QImage
public:
    void readImage (const std::string &path) override;
    void saveToFile(const std::string &path) override;
};

}
#endif // IMG_REPRESENTATION_H
