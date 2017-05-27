/*
 * kadai02
 * calculate pi by using Monte Carlo method
 * 540479c
 * Yamaguchi Ryutaro
 */

#include <stdio.h>
#include <limits.h>
#include <math.h>

#define MAX_XORSHIFT 4294967295

unsigned int xorshift(void)
{
    static unsigned int x = 1;
    static unsigned int y = 2;
    static unsigned int z = 3;
    static unsigned int w = 4;
    unsigned int t;
    t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

int random_integer(int m)
{
    return xorshift() % m;
}

double random_double(void)
{
    return xorshift() * 1.0 / MAX_XORSHIFT;
}

double random_normal()
{
    return sqrt(-2*log(random_double())) * cos(2 * M_PI * random_double());
}

int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

double calc_pi()
{
    unsigned int count = 0;
    unsigned int max_count = 1000000000;
    for (unsigned int i = 0; i < max_count; i++) {
        static int j = 0;
        if (max_count >= 100000 && (double)i / max_count > (double)j / 100) {
            printf("\r%d%%", j++);
            fflush(stdout);
        }
        if (gcd(random_integer(100000), random_integer(100000)) == 1) {
            count++;
        }
    }
    return sqrt(1.0 / ((double) count / max_count / 6.0));
}

int main(void)
{
    printf("\n%f\n", calc_pi());
    return 0;
}
