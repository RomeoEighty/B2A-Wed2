#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void stats(int, double *, double *, double *);

int main(int argc, char *argv[])
{
    double *data = (double *) malloc(sizeof(double) * (argc - 1));
    double mean = 0.;
    double variance = 0.;

    if (argc == 1) {
        printf("value is not inputted\n");
        return 0;
    }

    for (int i = 0; i < argc - 1; i++) {
        data[i] = atof(argv[i + 1]);
    }

    stats(argc - 1, data, &mean, &variance);

    if (argc != 0) {
        printf("mean = %f, variance = %f\n", mean, variance);
    }

    free(data);
}

void stats(int N, double *data, double *mean, double *variance)
{
    double sum = 0.;
    double variance_tmp = 0.;

    for (int i = 0; i < N; i++) {
        sum += data[i];
    }

    *mean = sum / N;

    for (int i = 0; i < N; i++) {
        variance_tmp += (data[i] - *mean) * (data[i] - *mean);
    }

    *variance = sqrt(variance_tmp / N);
}
