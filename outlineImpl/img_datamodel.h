
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
class DataModel
{
    imgznd::OpenCvImgRepr img;
    std::string path;
public:
    DataModel();
    void setPath(const std::string &p);
    std::string getPath() const;
    void onLoadButtonClicked();
    QPixmap getQPixmap();
};
}
#endif // IMG_DATAMODEL_H
