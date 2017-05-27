#include <stdio.h>
#include <math.h>

enum {
    TRIALS = 1000000,
};

int main(void)
{
    long double pi = 0.0L;
    long double sigma = 0.0L;

    for (int i = 1; i < TRIALS; i++)
        sigma += 1.0L / i / i / pow(2.0L, i - 1);
    pi = sqrt(6.0L*(sigma + log(2.0L) * log(2.0L)));

    printf("pi is nearly equal to %Lf\n", pi);

    return 0;
}
