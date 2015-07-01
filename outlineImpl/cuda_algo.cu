
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/sort.h>
#include <vector_types.h>
#include <cuda_runtime.h>
#include <cuda.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
//#include <QDebug>


#define PI 3.14159265359

using namespace std;

template<class T>
class CudaArray
{
public:
    CudaArray (int n) : dev{nullptr},nBytes{0}
    {
        try{
            nBytes = n * sizeof(T);
            cudaMalloc((void**)&dev,nBytes);
        } catch (...){}
    }
    ~CudaArray ()
    {
        try{
            cudaFree (dev);
        }
        catch(...) {}
    }
    int getnBytes() const
    {
        return nBytes;
    }
    operator T* () const
    {
        return dev;
    }
    CudaArray& operator = (T* rhs) const
    {
        cudaMemcpy (dev,rhs,nBytes,cudaMemcpyHostToDevice);
    }
    void copyToCpu(T *cpu) const
    {
        cudaMemcpy (cpu,dev,nBytes,cudaMemcpyDeviceToHost);
    }
private:
    T *dev;
    int nBytes;
};


__device__ float sinteta;
__device__ float costeta;
__global__ void kernelSetsincos(double teta)
{
    sinteta = sin (teta);
    costeta = cos (teta);
}
// http://habrahabr.ru/post/55461/ (c)
#define BLOCK_DIM 16
__global__ void kernelRotate(unsigned int* inputMatrix, unsigned int* outputMatrix, int width, int height)
{
    int xIndex = blockDim.x * blockIdx.x + threadIdx.x;
    int yIndex = blockDim.y * blockIdx.y + threadIdx.y;

    if ((xIndex < width) && (yIndex < height))
    {
        //Линейный индекс элемента строки исходной матрицы
        int inputIdx = xIndex + width * yIndex;
        //Линейный индекс элемента столбца матрицы-результата
        xIndex -= width / 2.0;
        yIndex -= height / 2.0;
        int nx = xIndex * costeta + yIndex * sinteta,
                ny = -xIndex * sinteta + yIndex * costeta;
        nx += width / 2.0;
        ny += height / 2.0;
        if (nx >= 0 && nx < width && ny >= 0 && ny < height){
            int outputIdx = nx  + width * ny;
            outputMatrix[outputIdx] = inputMatrix[inputIdx];
        }
    }
    //    __shared__ float temp[BLOCK_DIM][BLOCK_DIM];

    //    int xIndex = blockIdx.x * blockDim.x + threadIdx.x;
    //    int yIndex = blockIdx.y * blockDim.y + threadIdx.y;

    //    if ((xIndex < width) && (yIndex < height))
    //    {
    //        // Линейный индекс элемента строки исходной матрицы
    //        int idx = yIndex * width + xIndex;

    //        //Копируем элементы исходной матрицы
    //        temp[threadIdx.y][threadIdx.x] = inputMatrix[idx];
    //    }

    //    //Синхронизируем все нити в блоке
    //    __syncthreads();

    //    xIndex = blockIdx.y * blockDim.y + threadIdx.x;
    //    yIndex = blockIdx.x * blockDim.x + threadIdx.y;

    //    if ((xIndex < width) && (yIndex < height))
    //    {
    //        //        xIndex -= width / 2.0;
    //        //        yIndex -= height / 2.0;

    //        //        float nx = xIndex * costeta + yIndex * sinteta,
    //        //                ny = -xIndex * sinteta + yIndex * costeta;

    //        //        nx += width / 2.0;
    //        //        ny += height / 2.0;
    //        //        //x[i] = xi * costeta + yi * sinteta;
    //        //        //y[i] = -xi * sinteta + yi * costeta;

    //        //        if (nx >= 0 && nx < width && ny >= 0 && ny < height){

    //        //            // Линейный индекс элемента строки исходной матрицы
    //        int idx = yIndex * width + xIndex;

    //        //Копируем элементы исходной матрицы
    //        outputMatrix[idx] = temp[threadIdx.x][threadIdx.y];
    //        // }

    //    }
}
extern "C" void algoCudaRotate(unsigned char *input_output,int step,int rows,int cols,double angle)
{
    cudaMemset(&sinteta,0,sizeof(float));
    cudaMemset(&costeta,0,sizeof(float));
    kernelSetsincos<<<1,1>>> (-angle / 180.0 * PI);
   // std::cerr << "sincos set\n";
    int channels = 3,
            width = cols, //cols * channels,
            height = rows,
            n = width * height,
            bytesn = n * sizeof(int);

   // std::cerr << "step: " << step << " rows: " << rows << " cols: " << cols << '\n';
    unsigned int *data = new unsigned int [n];
    for(int i = 0;i < height; ++i){ // Упаковка bgr в int 4 байта тип
        for(int j = 0;j < width * channels; j += channels){
            unsigned char b = input_output[step * i + j],
                    g = input_output[step * i + j + 1],
                    r = input_output[step * i + j + 2];
            data[i * width + j / channels] = (int(b) << 16) | (int(g) << 8) | int(r);
        }
    }
    //std::cerr << "array read\n";
    CudaArray<unsigned int> inputimg(n),rotatedimg(n);
    inputimg = data;
    //std::cerr << "array copy to device\n";

    dim3 gridSize = dim3(width / BLOCK_DIM, height / BLOCK_DIM, 1);
    dim3 blockSize = dim3(BLOCK_DIM, BLOCK_DIM, 1);
    kernelRotate<<< gridSize, blockSize >>> (inputimg,rotatedimg,width,height);
    //std::cerr << "call kernel\n";

    rotatedimg.copyToCpu(data);
  //  std::fill (input_output,input_output + height * step,0);
   // std::cerr << "returen result to cpu mem\n";
    for(int i = 0;i < height; ++i){ // распаковка
        for(int j = 0;j < width * channels; j += channels){
            unsigned int bgr = data[i * width + j / channels];
            input_output[step * i + j] = (bgr >> 16);
            input_output[step * i + j + 1] = (bgr & (255 << 8)) >> 8;
            input_output[step * i + j + 2] = (bgr & 255);
        }
    }
    cudaFree (&sinteta);
    cudaFree (&costeta);
    delete [] data;

}
extern "C" cudaError_t algoCuda_main()
{
    return cudaGetLastError();
}
/* OpenCV data format

    int limit = 10,
            channel = 3;
    unsigned char *input = img.data;
    for(int i = 0;i < img.rows && limit ;i++){
        for(int j = 0;j < img.cols * channel && limit; j += channel){
           uchar b = input[img.step * i + j] ;
           uchar g = input[img.step * i + j + 1];
           uchar r = input[img.step * i + j + 2];
            qDebug () << b << g << r;
            limit--;
        }
    }

    qDebug () << "next";
    for (int i = 0; i < 10; i++){
        cv::Vec3b intensity = img.at<cv::Vec3b>(0, i);
        uchar b = intensity.val[0];
        uchar g = intensity.val[1];
        uchar r = intensity.val[2];
        qDebug () << b << g << r;
    }

/*
 __global__ void kernCuda(float *Source,float * Destination, int width)
{
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    int i = abs(x*cosf(theta)-y*sinf(theta));
    int j = abs(x*sinf(theta)+y*cosf(theta));

    if(x<width && y<width){
        Destination[j*width+i]=Source[y*width+x];
    }

}
 */
