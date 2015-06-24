/*
 * img_provider.cpp
 * This source code is completely free.
 * 2015, Renat Ashirbakiev
 * r.robotman@yandex.ru - Russia->Moscow
*/

#ifndef IMG_REPRESENTATION_H
#define IMG_REPRESENTATION_H

#include <exception>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/gpu/gpu.hpp>

namespace imgznd
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
    OpenCvImgRepr () {}
    void readImage (const std::string &path) override;
    void saveToFile(const std::string &path) override;
    using returnType = uchar;
    class CvArray1D
    { // proxy class - this trick help us [][] operation to be used
    public:
        CvArray1D(returnType* ptr,int n);
        CvArray1D(const returnType* ptr,int n);
        returnType& operator [] (int index);
        const returnType operator [] (int index) const;
    private:
        returnType *arrayPtr;
        int sizen;
    };
    CvArray1D operator [] (int index);
    const CvArray1D operator [] (int index) const;
};

class QtImgRepr : public AbsImgRepr
{ // QImage
public:
    void readImage (const std::string &path) override;
    void saveToFile(const std::string &path) override;
};


}
#endif // IMG_REPRESENTATION_H
