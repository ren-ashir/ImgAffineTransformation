/*
 * img_provider.cpp
 * This source code is completely free.
 * 2015, Renat Ashirbakiev
 * r.robotman@yandex.ru - Russia->Moscow
 * https://github.com/ren-ashir/ImgAffineTransformation/
*/


#include "img_datamodel.h"


imgznd::DataModel::DataModel()
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

QPixmap imgznd::DataModel::getQPixmap()
{
    return imgznd::cvMatToQPixmap(img);
}
