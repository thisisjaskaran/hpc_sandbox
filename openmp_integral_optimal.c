#include <stdio.h>
#include <omp.h>

#define PAD 8

void main()
{
    double start_time = omp_get_wtime();
    double no_of_steps = 100000000;
    double total_threads = 2;
    omp_set_num_threads(total_threads);
    double area = 0.0;
    printf("Total Threads : %f\n", total_threads);
    double sum[(int)total_threads][PAD];

#pragma omp parallel
    {
        double id = omp_get_thread_num();
        sum[(int)id][0] = 0.0;
        for (int i = id; i < (int)no_of_steps; i += (int)total_threads)
        {
            double x = (double)i / no_of_steps;
            double val = 4.0 / (1.0 + x * x);
            sum[(int)id][0] += val / no_of_steps;
        }
    }
    double end_time = omp_get_wtime();

    for (int i = 0; i < total_threads; i++)
        area += sum[i][0];
    printf("Total Area = %f calculated in time = %f\n", area, end_time - start_time);
}