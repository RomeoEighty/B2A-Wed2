/*
 * kadai01
 * XORSHIFT random number generator
 * 540479c
 * Yamaguchi Ryutaro
 */

#include <stdio.h>
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

int main(void)
{
    for (int i = 0; i < 100; i++) {
        printf("%u\n", xorshift());
    }
    for (int i = 0; i < 100; i++) {
        printf("0-10:%d\n", random_integer(11));
    }
    for (int i = 0; i < 100; i++) {
        printf("double:%f\n", random_double());
    }
    for (int i = 0; i < 100; i++) {
        printf("normal:%f\n", random_normal());
    }
}

