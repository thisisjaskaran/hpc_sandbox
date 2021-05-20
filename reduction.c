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

    double ave = 0.0;
    int size = 1000;
    double a[size];

    for (int i = 0; i < size; i++)
        a[i] = i;

    printf("Run Time = %lf\n", omp_get_wtime() - start_time);

    return 0;
}