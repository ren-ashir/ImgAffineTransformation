
/*
 * img_provider.cpp
 * This source code is completely free.
 * 2015, Renat Ashirbakiev
 * r.robotman@yandex.ru - Russia->Moscow
 * https://github.com/ren-ashir/ImgAffineTransformation/
*/

#ifndef IMG_DATAMODEL_H
#define IMG_DATAMODEL_H

#include "img_includs.h"



namespace imgznd{
/*
 * Class interaction of business logic and GUI
 */
class raiiTimeMeasure
{
public:
    raiiTimeMeasure (double &time) : lastoptime{time}
    {
       t0 = std::chrono::high_resolution_clock::now();
    }
    ~raiiTimeMeasure ()
    {
        t1 = std::chrono::high_resolution_clock::now();
        lastoptime = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();
    }
private:
   double &lastoptime;
   std::chrono::high_resolution_clock::time_point t0,t1;
};

class DataModel
{
#define TIMESTART auto t0 = std::chrono::high_resolution_clock::now()
#define TIMEEND auto t1 = std::chrono::high_resolution_clock::now(); lastoptime = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count()
#define TIMEF(x) TIMESTART; x; TIMEEND
    double lastoptime;
    imgznd::OpenCvImgRepr img;
    std::string path;
public:
    DataModel();
    void setPath(const std::string &p);
    std::string getPath() const;
    void onLoadButtonClicked();
    QPixmap getStrightforwardQPixmap();
    QPixmap getOpenCvRotatedQPixmap();
    QPixmap getOneThreadCpuRotatedQPixmap();
    QPixmap getMultithreadRoratedQpixmap();
    double lastOperationTime();
};
}
#endif // IMG_DATAMODEL_H
