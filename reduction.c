#include <stdio.h>
#include <omp.h>

#define PAD 8

void main()
{
    double start_time = omp_get_wtime();
    double no_of_steps = 100000000;

    double sum = 0.0;

#pragma omp parallel for reduction(+ \
                                   : sum)
    for (int i = 0; i < (int)no_of_steps; i++)
    {
        double x = (double)i / no_of_steps;
        double val = 4.0 / (1.0 + x * x);
        sum += val / no_of_steps;
    }

    printf("Total Area = %f calculated in time = %f\n", sum, omp_get_wtime() - start_time);
}