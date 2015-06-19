/*
 * img_representation.h
 * This source code is completely free.
 * Copyright (C) 2015, Renat Ashirbakiev
 * r.robotman@yandex.ru - Russia->Moscow
*/

#ifndef IMG_ALGORITHM_H
#define IMG_ALGORITHM_H

#include "img_representation.h"

namespace imgznd
{
void openCvRotate (const OpenCvImgRepr &src,OpenCvImgRepr &warp_rotate_dst,double angle = -90,double scale = 1.0);
void openCvResizeBorder(OpenCvImgRepr &src,double dx,double dy);
void openCvZoom(OpenCvImgRepr &src,double scale = 1.0);

//cuda's function
float* cudaGetRow(int row);
void cudaRotate();
}

#endif // IMG_ALGORITHM_H
