/*
 * img_representation.h
 * This source code is completely free.
 * Copyright (C) 2015, Renat Ashirbakiev
 * r.robotman@yandex.ru - Russia->Moscow
*/

#include "img_algorithm.h"

namespace imgznd
{
void openCvRotate(const imgznd::OpenCvImgRepr &src, imgznd::OpenCvImgRepr &warp_rotate_dst, double angle, double scale)
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
void openCvResizeBorder(imgznd::OpenCvImgRepr &src,double dx,double dy)
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

void openCvZoom(OpenCvImgRepr &src, double scale)
{
    cv::Size sz = src.size();
    sz.height *= scale;
    sz.width *= scale;
    cv::resize(src,src,sz,cv::INTER_LANCZOS4);
}


}
