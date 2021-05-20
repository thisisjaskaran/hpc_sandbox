#include <stdio.h>
#include <omp.h>

void main()
{
    double start_time = omp_get_wtime();
    double no_of_steps = 100000;
    double total_threads = 3;
    omp_set_num_threads(total_threads);
    printf("Total Threads : %f\n", total_threads);
    double sum = 0.0;

#pragma omp parallel
    {
        double id = omp_get_thread_num();
        total_threads = omp_get_num_threads();
        double val = 0.0;

        for (int i = id; i < (int)no_of_steps; i += (int)total_threads)
        {
            double x = (double)i / no_of_steps;
            val += 4.0 / (1.0 + x * x);
        }
#pragma omp critical
        sum += val / no_of_steps;
    }
    double end_time = omp_get_wtime();

    printf("Total Area = %f calculated in time = %f\n", sum, end_time - start_time);
}