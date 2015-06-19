#ifndef IMG_ALGORITHM_H
#define IMG_ALGORITHM_H

#include "img_representation.h"

namespace imgznd
{
void openCvRotate (const OpenCvImgRepr &src,OpenCvImgRepr &warp_rotate_dst,double angle = -90,double scale = 1.0);

}

#endif // IMG_ALGORITHM_H
