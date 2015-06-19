#include "img_algorithm.h"

namespace imgznd
{
void openCvRotate(const imgznd::OpenCvImgRepr &src, imgznd::OpenCvImgRepr &warp_rotate_dst, double angle, double scale)
{
    /// Compute a rotation matrix with respect to the center of the image
    cv::Point center = cv::Point{ src.cols/2.0, src.rows/2.0 };
    cv::Mat rot_mat{ 2, 3, CV_32FC1 };
    rot_mat = cv::getRotationMatrix2D(center, angle, scale );
    cv::warpAffine( src, warp_rotate_dst, rot_mat, src.size() );
}

}
