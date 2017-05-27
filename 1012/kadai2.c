#include <stdio.h>
#include <math.h>

enum {
    MAX_DEPTH = 10,
};

int count = 0;

long double sqrt_cf_sub(long double);
long double sqrt_cf(long double);

int main(void)
{
    int n = 2;
    printf("root %d = %Lf\n", n, sqrt_cf((long double) n));
    return 0;
}

long double sqrt_cf_sub(long double f)
{
    if (count++ <= MAX_DEPTH) {
        return (f - 1.L) / (2.L + sqrt_cf_sub(f));
    } else {
        count = 0;
        return (long double)sqrt(f) - 1.L;
    }
}

long double sqrt_cf(long double f)
{
    return 1.L + sqrt_cf_sub(f);
}
