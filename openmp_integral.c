#include <stdio.h>
#include <omp.h>

#define PAD 8

double step_size = 0.001;

void main()
{
    double start_time = omp_get_wtime();
    double total_threads = 30;
    omp_set_num_threads(total_threads);
    double area = 0.0;
    printf("Total Threads : %f\n", total_threads);
    double sum[(int)total_threads][PAD];
#pragma omp parallel
    {
        double thread_number = omp_get_thread_num();
        double a = thread_number / total_threads;
        double b = (thread_number + 1) / total_threads;

        sum[(int)thread_number][0] = 0.0;

        // printf("Calculating integral between %f and %f\n", a, b);
        for (double i = a; i < b; i += step_size)
        {
            double val = 4.0 / (1 + i * i);
            sum[(int)thread_number][0] += val * step_size;
        }
    }
    double end_time = omp_get_wtime();

    for (int i = 0; i < total_threads; i++)
        area += sum[i][0];
    printf("Total Area = %f calculated in time = %f\n", area, end_time - start_time);
}