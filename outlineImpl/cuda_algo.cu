
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/sort.h>
#include <cuda_runtime.h>
#include <cuda.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>

#define PI 3.14159265359

using namespace std;
//
// Kernel definition
__global__ void VecAdd(float* A, float* B, float* C)
{
    int i = threadIdx.x;
    C[i] = A[i] + B[i];
}
// add
__global__ void sumKernel (float *a,float *b, float *c)
{
    //Global index of thread
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    c[i] = a[i] + b[i];
}
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
cudaError_t sum (float *a,float *b,float*c,int n)
{
    CudaArray<float> aDev(n),bDev(n),cDev(n);
    dim3 threads = dim3(512,1);
    dim3 blocks = dim3(n / threads.x,1);
    aDev = a;
    bDev = b;
    sumKernel<<<blocks, threads>>> (aDev,bDev,cDev);
    cDev.copyToCpu(c);
    return cudaGetLastError();
}
// tranform GPU
// add
__global__ void getTransformed_xy_Kernel (float *x,float *y)
{
    //Global index of thread
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    const float teta = PI / 2.5;
    const float sinteta = sin (teta);
    const float costeta = cos (teta);
    float xi = x[i];
    float yi = y[i];
    x[i] = xi * costeta + yi * sinteta;
    y[i] = -xi * sinteta + yi * costeta;
}
void  transform_xyData_gpu(float *x,float *y,int n)
{
    CudaArray<float> xDev(n),yDev(n);
    float *xn = new float [n],*yn = new float[n];
    dim3 threads = dim3(512,1);
    dim3 blocks = dim3(n / threads.x,1);
    xDev = x;
    yDev = y;
    getTransformed_xy_Kernel <<< blocks, threads >>> (xDev,yDev);
    xDev.copyToCpu(xn);
    yDev.copyToCpu(yn);
    delete [] xn;
    delete [] yn;
}
extern "C" cudaError_t cuda_main()
{
    return cudaGetLastError();
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
