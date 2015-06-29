/*
 * img_provider.cpp
 * This source code is completely free.
 * 2015, Renat Ashirbakiev
 * r.robotman@yandex.ru - Russia->Moscow
 * https://github.com/ren-ashir/ImgAffineTransformation/
*/
#ifndef IMG_ALGORITHM_H
#define IMG_ALGORITHM_H

#include <QImage>
#include <QPixmap>
#include <QDebug>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"
#include <iterator>
#include <functional>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>
#include <cuda_runtime.h>
#include "img_representation.h"

namespace imgznd
{
//OpenCV lib
void algoOpenCvRotate (const OpenCvImgRepr &src,OpenCvImgRepr &warp_rotate_dst,double angle = -90,double scale = 1.0);
void algoOpenCvResizeBorder(OpenCvImgRepr &src,double dx,double dy);
void algoOpenCvZoom(OpenCvImgRepr &src,double scale = 1.0);

//cuda's function
extern "C" cudaError_t cuda_main();
float* algoCudaGetRow(int row);
void algoCudaRotate();

//cpu, multithreading
QPixmap algoOneThreadCpuRotateQPixmap(const OpenCvImgRepr &img,double angle = -90);
QPixmap algoMultiThreadRorateQpixmap(const OpenCvImgRepr &img,double angle = -90);


/*
   Functions to convert between OpenCV's cv::Mat and Qt's QImage and QPixmap.
   Andy Maloney
   23 November 2013
   http://asmaloney.com/2013/11/code/converting-between-cvmat-and-qimage-or-qpixmap
 */
 QImage  algoCvMatToQImage( const cv::Mat &inMat );
 QPixmap algoCvMatToQPixmap( const cv::Mat &inMat );

 //math algo
 double algoDeg2Rad(double deg);
}

#endif // IMG_ALGORITHM_H
//backstage code

//template<typename T>
//void algoRotatePoint1thread(T *x, T *y, double angle, int n)
//{
//    static T sinteta = std::sin (angle);
//    static T costeta = std::cos (angle);
//    T xn,yn;
//    for (int i = 0; i < n; ++i)
//    {
//        xn = x[i] * costeta + y[i] * sinteta;
//        yn = -x[i] * sinteta + y[i] * costeta;
//        x[i] = xn;
//        y[i] = yn;
//    }
//}
//template<typename T>
//void algoRotatePointMultithread(T *x, T *y, double angle, int n)
//{
//    using cuint = unsigned int const;
//    cuint min_per_thread = 100,
//            max_threads = (n + min_per_thread - 1) / min_per_thread, // получить максимальное число потоков
//            hardware_threads = std::thread::hardware_concurrency(),
//            num_threads = std::min (hardware_threads == 0 ? 2 : hardware_threads,max_threads), // не запускать потоков больше, чем есть на машине
//            block_size = n / num_threads;
//    std::vector<std::thread> threads(num_threads - 1);
//    //std::cout << "block size: " << block_size << '\n';
//    //std::cout << "num thread: " << num_threads << '\n';
//    for (auto &cur_thread: threads){
//        cur_thread = std::thread(algoRotatePoint1thread<T>,x,y,angle,int(block_size));
//        std::advance(x,block_size);
//        std::advance(y,block_size);
//        n -= block_size;
//    }
//    algoRotatePoint1thread (x,y,angle,n);
//    std::for_each(threads.begin(),threads.end(),mem_fn(&std::thread::join)); // дождаться завершения всех потоков
//}
