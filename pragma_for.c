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

    int arr_size = 1000000;
    int a[arr_size], b[arr_size];

    for (int i = 0; i < arr_size; i++)
    {
        a[i] = i + 1;
        b[i] = 2;
    }

#pragma omp parallel for
    for (int i = 0; i < arr_size; i++)
        a[i] = a[i] + b[i];

    // print(a, arr_size);

    double end_time = omp_get_wtime();

    double time = end_time - start_time;

    printf("Run Time = %lf\n", time);

    return 0;
}