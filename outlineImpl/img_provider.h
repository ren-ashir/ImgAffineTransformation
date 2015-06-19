/*
 * img_provider.h
 * This source code is completely free.
 * Copyright (C) 2015, Renat Ashirbakiev
 * r.robotman@yandex.ru - Russia->Moscow
*/

#ifndef IMG_PROVIDER_H
#define IMG_PROVIDER_H

#include <string>
#include <memory>
#include "make_unique.h"
#define IMG_PATH ImgPaths::instance()

namespace imgznd
{

class Abs_ImageUri;
// Interface of the img_provider space
std::string getImgLink(const std::unique_ptr<Abs_ImageUri> &img_link);
std::string getPngLink();
std::string getTifLink();
std::string getJpgLink();

class ImgPaths
{ // singleton for paths
public:
    static const ImgPaths &instance ();
    std::string pathToImgFolder() const;
private:
    ImgPaths (){}
    ImgPaths (const ImgPaths&){}
    ImgPaths& operator= (const ImgPaths&) {}
    ~ImgPaths () {}
};

// The hierarchy class for a img specification
/*
It is expected that instances of hierarchy class will be able to get a path by more complicated way.
Now (15.06.2015) for the one invoke of getPngLink, getTifLink,... functions a creation of the instance is required.
*/
class Abs_ImageUri
{
public:
    virtual std::string getAnyUri() const = 0;
    virtual ~Abs_ImageUri () {}
};
class Png_ImgUri : public Abs_ImageUri
{
public:
    std::string getAnyUri() const override;
};
class Tif_ImgUri : public Abs_ImageUri
{
public:
    std::string getAnyUri() const override;
};

class Jpg_ImgUri : public Abs_ImageUri
{
public:
    std::string getAnyUri() const override;
};
}
#endif // IMG_PROVIDER_H
