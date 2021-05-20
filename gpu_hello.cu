#include<stdio.h>
#include<cuda.h>

// this is the kernel
// this is the function that actually runs on the GPU
__global__ void dkernel()
{
    printf("Hello World.\n");
}

int main()
{
    // kernel launch, use 1 thread
    dkernel<<<1,1>>>();
    // synchronize CPU and GPU
    cudaDeviceSynchronize();
    return 0;
}
