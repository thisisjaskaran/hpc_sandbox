#include <stdio.h>
#include <omp.h>

void print(int a[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", a[i]);
    printf("\n");
}
int main()
{
    double start_time = omp_get_wtime();

    int size = 999999;
    int a[size];

// #pragma omp parallel for
#pragma omp parallel for schedule(static, 111111)
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 10; j++)
            a[i] = i + j;
    }

    // double end_time = omp_get_wtime();

    // print(a, size);

    // double time = end_time - start_time;

    printf("Run Time = %lf\n", omp_get_wtime() - start_time);

    return 0;
}