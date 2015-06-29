/*
 * img_provider.cpp
 * This source code is completely free.
 * 2015, Renat Ashirbakiev
 * r.robotman@yandex.ru - Russia->Moscow
 * https://github.com/ren-ashir/ImgAffineTransformation/
*/

#include "img_algorithm.h"

namespace imgznd
{
void algoOpenCvRotate(const imgznd::OpenCvImgRepr &src, imgznd::OpenCvImgRepr &warp_rotate_dst, double angle, double scale)
{
    int width = src.cols;
    int height = src.rows;
    cv::Size imgSize = src.size();
    imgSize.width = width;
    imgSize.height = height;
    /// Compute a rotation matrix with respect to the center of the image
    cv::Point center = cv::Point{ width/2, height/2 };
    cv::Mat rot_mat{ 2, 3, CV_32FC1 };
    //rot_mat.
    rot_mat = cv::getRotationMatrix2D(center, angle, scale );
    cv::warpAffine( src, warp_rotate_dst, rot_mat, imgSize ); //,cv::INTER_AREA, cv::BORDER_CONSTANT, cv::Scalar::all(0));
}
void algoOpenCvResizeBorder(imgznd::OpenCvImgRepr &src,double dx,double dy)
{
    cv::Point2f srcTri[3];
    cv::Point2f dstTri[3];
    /// Set your 3 points to calculate the  Affine Transform
    srcTri[0] = cv::Point2f( 0,0 );
    srcTri[1] = cv::Point2f( src.cols - 1, 0 );
    srcTri[2] = cv::Point2f( 0, src.rows - 1 );
    dstTri[0] = cv::Point2f( 0 + dx / 2.0, 0 + dy / 2.0);
    dstTri[1] = cv::Point2f( src.cols - 1 + dx / 2.0, 0 + dy / 2.0);
    dstTri[2] = cv::Point2f( 0 + dx / 2.0, src.rows - 1 + dy / 2.0 );
    /// Get the Affine Transform
    cv::Mat warp_mat( 2, 3, CV_32FC1 );
    warp_mat = cv::getAffineTransform( srcTri, dstTri );
    cv::Size imgSize = src.size();
    imgSize.width += dx;
    imgSize.height += dy;
    cv::warpAffine( src, src, warp_mat, imgSize );
}

/*
   Functions to convert between OpenCV's cv::Mat and Qt's QImage and QPixmap.

   Andy Maloney
   23 November 2013
   http://asmaloney.com/2013/11/code/converting-between-cvmat-and-qimage-or-qpixmap
 */
void algoOpenCvZoom(OpenCvImgRepr &src, double scale)
{
    cv::Size sz = src.size();
    sz.height *= scale;
    sz.width *= scale;
    cv::resize(src,src,sz,cv::INTER_LANCZOS4);
}

QImage algoCvMatToQImage(const cv::Mat &inMat)
{
    switch ( inMat.type() )
    {
    // 8-bit, 4 channel
    case CV_8UC4:
    {
        qDebug () << "8-bit, 4 channel";
        QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );
        return image;
    }
    // 8-bit, 3 channel
    case CV_8UC3:
    {
        qDebug () << "8-bit, 3 channel";
        QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );
        return image.rgbSwapped();
    }
     // 8-bit, 1 channel
    case CV_8UC1:
    {
        static QVector<QRgb>  sColorTable;
        qDebug () << "8-bit, 1 channel";
        // only create our color table once
        if (sColorTable.isEmpty())
        {
            for ( int i = 0; i < 256; ++i )
                sColorTable.push_back( qRgb( i, i, i ) );
        }
        QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8 );
        image.setColorTable( sColorTable );
        return image;
    }
    default:
        qDebug() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
        break;
    }

    return QImage();
}

QPixmap algoCvMatToQPixmap(const cv::Mat &inMat)
{
    return QPixmap::fromImage( algoCvMatToQImage( inMat ) );
}

inline void blockSubmatrixOp(imgznd::OpenCvImgRepr &matrix_dst,const imgznd::OpenCvImgRepr &matrix_src,int rowStart,int rowEnd,double sinteta,double costeta)
{
    const int ns = matrix_src.rows,
            ms = matrix_src.cols;
    double x,y;
    int xn,yn;
    for (int i = rowStart; i < rowEnd; ++i)
    {
        for (int j = 0; j < ms; ++j)
        {
            //rotate relative to the middle
            x = i - ns / 2.0;
            y = j - ms / 2.0;
            //calc new coords
            xn = x * costeta + y * sinteta;
            yn = -x * sinteta + y * costeta;
            xn += ns / 2.0;
            yn += ms / 2.0;
            if (xn >= 0 && xn < ns && yn >= 0 && yn < ms)
                matrix_dst.at<cv::Vec3b>(xn,yn) = matrix_src.at<cv::Vec3b>(i, j);
        }
    }
}

QPixmap algoOneThreadCpuRotateQPixmap(const OpenCvImgRepr &img, double angle)
{
    angle = algoDeg2Rad(angle);
    double sinteta = std::sin (angle);
    double costeta = std::cos (angle);
    imgznd::OpenCvImgRepr newImgone(img.size(),img.type());
    try{
        blockSubmatrixOp (newImgone,img,0,img.rows,sinteta,costeta);
    }
    catch(...)
    {
        qDebug () << "oopps an one thread rotation fail";
        throw;
    }
    return imgznd::algoCvMatToQPixmap(newImgone);
}

QPixmap algoMultiThreadRorateQpixmap(const OpenCvImgRepr &img, double angle)
{
    angle = algoDeg2Rad(angle);
    double sinteta = std::sin (angle);
    double costeta = std::cos (angle);
    imgznd::OpenCvImgRepr newImgone(img.size(),img.type());
    try{
        const int minblocksize = 25,
                nthreads = (newImgone.rows + minblocksize - 1) / minblocksize,
                hardwarethreads = std::thread::hardware_concurrency(),
                realnthreads = std::min (hardwarethreads == 0 ? 2 : hardwarethreads, nthreads),
                realblocksize = newImgone.rows / realnthreads;
        std::vector<std::thread> threads (realnthreads - 1);
        int start = 0;
        for (int i = 0; i < realnthreads - 1; ++i)
        {
            threads[i] = std::thread(blockSubmatrixOp,std::ref(newImgone),std::ref(img),start,start + realblocksize,sinteta,costeta);
            start += realblocksize;
        }
        blockSubmatrixOp (newImgone,img,start,newImgone.rows,sinteta,costeta);
        for (auto &thrd: threads) thrd.join();
    }
    catch(...)
    {
        qDebug () << "oopps multi thread rotation fail";
        throw;
    }
    return imgznd::algoCvMatToQPixmap(newImgone);
}

//math algo
constexpr double pi = acos(-1.0);

double algoDeg2Rad(double deg)
{
    return deg / 180.0 * pi;
}

}
