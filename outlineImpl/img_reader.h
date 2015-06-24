/*
 * img_provider.cpp
 * This source code is completely free.
 * 2015, Renat Ashirbakiev
 * r.robotman@yandex.ru - Russia->Moscow
*/

#ifndef IMG_READER_H
#define IMG_READER_H

#include <QFile>
#include <memory>
#include <string>
#include <QDebug>
#include <QImage>

class ImgReader
{
    std::shared_ptr<QFile> file;
    std::shared_ptr<QImage> image;
public:
    ImgReader (const std::string &fileName);
    void testfSaveImage (const QString &outFileName);

};

#endif // IMG_READER_H
