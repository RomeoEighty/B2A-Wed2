#include <stdio.h>

long double legendre(int n, long double x)
{
    if (n == 0) {
        return 1.0L;
    } else if (n == 1) {
        return x;
    } else {
        return ((2.0L * (long double)n - 1.0L) * x * legendre(n - 1, x) - ((long double)n - 1) * legendre(n - 2, x)) / (long double)n;
    }
}

int main(void)
{
    int n1 = 16;
    int n2 = 32;
    long double x1 = 0.5L;
    long double x2 = 0.7L;
    printf("P_%d(%Lf) = %Lf, P_%d(%Lf) = %Lf\n", n1, x1, legendre(n1, x1), n2, x2, legendre(n2, x2));
    return 0;
}
