#include <stdio.h>
#include <math.h>

void eigen(double(*)[2], double*, double*, double*, double*);

int main(void)
{
    double matrix[2][2] = {{1, 5}, {6, 2}};
    double eigenvalue1 = 0., eigenvalue2 = 0.;
    double eigenvector1[2] = {};
    double eigenvector2[2] = {};

    eigen(matrix, &eigenvalue1, eigenvector1, &eigenvalue2, eigenvector2);
    printf("[%f, %f]\n", matrix[0][0], matrix[0][1]);
    printf("[%f, %f]\n", matrix[1][0], matrix[1][1]);
    printf("eigenvalue = %f, eigenvector = (%f, %f)\n", eigenvalue1, eigenvector1[0], eigenvector1[1]);
    printf("eigenvalue = %f, eigenvector = (%f, %f)\n", eigenvalue2, eigenvector2[0], eigenvector2[1]);
    return 0;
}

void eigen(double (*matrix)[2], double *eigenvalue1, double *eigenvector1, double *eigenvalue2, double *eigenvector2)
{
    *eigenvalue1 = 1. / 2. * ( matrix[0][0] + matrix[1][1] + sqrt(matrix[0][0] * matrix[0][0] + matrix[1][1] * matrix[1][1] - 2 * matrix[0][0] * matrix[1][1] + 4 * matrix[1][0] * matrix[0][1]));
    *eigenvalue2 = 1. / 2. * ( matrix[0][0] + matrix[1][1] - sqrt(matrix[0][0] * matrix[0][0] + matrix[1][1] * matrix[1][1] - 2 * matrix[0][0] * matrix[1][1] + 4 * matrix[1][0] * matrix[0][1]));
    eigenvector1[0] = 1. / 2. / matrix[1][0] * ( matrix[0][0] - matrix[1][1] + sqrt(matrix[0][0] * matrix[0][0] + matrix[1][1] * matrix[1][1] - 2 * matrix[0][0] * matrix[1][1] + 4 * matrix[1][0] * matrix[0][1]));
    eigenvector1[1] = 1.;
    eigenvector2[0] = 1. / 2. / matrix[1][0] * ( matrix[0][0] - matrix[1][1] - sqrt(matrix[0][0] * matrix[0][0] + matrix[1][1] * matrix[1][1] - 2 * matrix[0][0] * matrix[1][1] + 4 * matrix[1][0] * matrix[0][1]));
    eigenvector2[1] = 1.;
}
