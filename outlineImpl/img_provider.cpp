/*
 * img_provider.cpp
 * This source code is completely free.
 * 2015, Renat Ashirbakiev
 * r.robotman@yandex.ru - Russia->Moscow
*/

#include "img_provider.h"

namespace imgznd
{
//interface
std::string getImgLink(const std::unique_ptr<Abs_ImageUri>  &img_link)
{
    return img_link->getAnyUri();
}
std::string getPngLink()
{
    return getImgLink (make_unique<Png_ImgUri>()); //std::unique_ptr<Abs_ImageUri>(new Png_ImgUri));
}
std::string getTifLink()
{
    return getImgLink (make_unique<Tif_ImgUri>()); //std::unique_ptr<Abs_ImageUri>(new Tif_ImgUri));
}
std::string getJpgLink()
{
    return getImgLink (make_unique<Jpg_ImgUri>());
}
//public methods
std::string Png_ImgUri::getAnyUri() const
{
    return IMG_PATH.pathToImgFolder() + "3.png";
}
std::string Tif_ImgUri::getAnyUri() const
{
    return IMG_PATH.pathToImgFolder() + "20100813072157.tif";
}
std::string Jpg_ImgUri::getAnyUri() const
{
     return IMG_PATH.pathToImgFolder() + "768_1.jpg";
}
const ImgPaths &ImgPaths::instance()
{
    static ImgPaths singleInstance;
    return singleInstance;
}
std::string ImgPaths::pathToImgFolder() const
{
    return "/home/s/Desktop/";
}

//private methods
}





