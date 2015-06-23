/*
 * img_representation.h
 * This source code is completely free.
 * Copyright (C) 2015, Renat Ashirbakiev
 * r.robotman@yandex.ru - Russia->Moscow
*/

#ifndef IMG_ALGORITHM_H
#define IMG_ALGORITHM_H

#include <iterator>
#include <functional>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>
#include "img_representation.h"

namespace imgznd
{
void openCvRotate (const OpenCvImgRepr &src,OpenCvImgRepr &warp_rotate_dst,double angle = -90,double scale = 1.0);
void openCvResizeBorder(OpenCvImgRepr &src,double dx,double dy);
void openCvZoom(OpenCvImgRepr &src,double scale = 1.0);

//cuda's function
float* cudaGetRow(int row);
void cudaRotate();

//cpu, multithreading
template<typename T>
//void rotatePoint1thread(T *x, T *y, double angle, int n)
void rotatePoint1thread(T *x, T *y, double angle, int n)
{
    T sinteta = std::sin (angle);
    T costeta = std::cos (angle);
    T xn,yn;
    for (int i = 0; i < n; ++i)
    {
        xn = x[i] * costeta + y[i] * sinteta;
        yn = -x[i] * sinteta + y[i] * costeta;
        x[i] = xn;
        y[i] = yn;
    }
}
template<typename T>
void rotatePointMultithread(T *x, T *y, double angle, int n)
{
    using cuint = unsigned int const;
    cuint min_per_thread = 25,
            max_threads = (n + min_per_thread - 1) / min_per_thread, // получить максимальное число потоков
            hardware_threads = std::thread::hardware_concurrency(),
            num_threads = std::min (hardware_threads == 0 ? 2 : hardware_threads,max_threads), // не запускать потоков больше, чем есть на машине
            block_size = n / num_threads;
    std::vector<std::thread> threads(num_threads - 1);
    std::cout << "block size: " << block_size << '\n';
    std::cout << "num thread: " << num_threads << '\n';
    for (auto &cur_thread: threads){
        cur_thread = std::thread(rotatePoint1thread<T>,x,y,angle,int(block_size));
        std::advance(x,block_size);
        std::advance(y,block_size);
        n -= block_size;
    }
    rotatePoint1thread (x,y,angle,n);
    std::for_each(threads.begin(),threads.end(),mem_fn(&std::thread::join)); // дождаться завершения всех потоков
}
}

#endif // IMG_ALGORITHM_H
