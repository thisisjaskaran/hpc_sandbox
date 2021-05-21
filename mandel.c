#include <stdio.h>
#include <omp.h>
#define NPOINTS 1000
#define MXITR 10000

struct d_complex
{
    double r;
    double i;
};

struct d_complex c;
int numoutside = 0;

void testpoint(struct d_complex c)
{
    struct d_complex z;
    int iter;
    double temp;

    // z.r = c.r;
    // z.i = c.i;
    z = c;
    for (iter = 0; iter < MXITR; iter++)
    {
        temp = (z.r * z.r) - (z.i * z.i) + c.r;
        z.i = z.r * z.i * 2 + c.i;
        z.r = temp;
        if ((z.r * z.r + z.i * z.i) > 4.0)
        {
#pragma omp atomic //needs to be protected using atomic since some other thread might start numoutside++ on a thread which was midway that
            numoutside++;
            break;
        }
    }
}

int main()
{
    int i, j;
    double area, error, eps = 1.0e-5;
#pragma omp parallel for default(none) private(c, j) firstprivate(eps)
    for (i = 0; i < NPOINTS; i++) //the loop index of i (since it is the ine pragma omp for is applied to) is implicitly made private
    {
        for (j = 0; j < NPOINTS; j++) //but the above policy does not apply to j
        {
            c.r = -2.0 + 2.5 * (double)(i) / (double)(NPOINTS) + eps;
            c.i = 1.125 * (double)(j) / (double)(NPOINTS) + eps;
            testpoint(c);
        }
    }
    area = 2.0 * 2.5 * 1.125 * (double)(NPOINTS * NPOINTS - numoutside) / (double)(NPOINTS * NPOINTS);
    error = area / (double)NPOINTS;
    printf("Area = %lf, Error = %lf\n", area, error);
}