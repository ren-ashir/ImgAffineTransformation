/*
 * img_provider.cpp
 * This source code is completely free.
 * 2015, Renat Ashirbakiev
 * r.robotman@yandex.ru - Russia->Moscow
 * https://github.com/ren-ashir/ImgAffineTransformation/
*/

#include "img_reader.h"

ImgReader::ImgReader(const std::string &fileName) :   file{std::make_shared<QFile>(fileName.c_str())}
{
    if (!file->open(QFile::ReadOnly))
    {
        qDebug ("Could not open file");
        qDebug() << file->errorString();
        qDebug () << file->fileName();
    } else {
        qDebug () << file->fileName() << " opened";
        qint64 size = file->size();
        const unsigned char *mmf = file->map(0,size);
        int h = 50,
                w = 50;
        //QImage()
        image = std::make_shared<QImage>(mmf,w,h,QImage::Format_RGBX8888);
    }
}

void ImgReader::testfSaveImage(const QString &outFileName)
{
    if (image->isNull())
        return;
    image->save(outFileName,"JPEG");
    // if (image->)
}
