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

    int a[999999];

#pragma omp parallel
#pragma omp for schedule(static, 111111)
    for (int i = 0; i < 999999; i++)
    {
        a[i] = i;
        a[i] = i * i;
        a[i] = i * i * i;
    }

    double end_time = omp_get_wtime();

    print(a, 999999);

    double time = end_time - start_time;

    printf("Run Time = %lf\n", time);

    return 0;
}