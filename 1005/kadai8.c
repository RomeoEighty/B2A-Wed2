#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define PARAM 1000

typedef struct {
    int a;
    int b;
    int c;
} pythagoras_t;

int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

void sort_output(int *a, int *b)
{
    if (*a > *b) {
        int tmp = *b;
        *b = *a;
        *a = tmp;
    }
}

int cmp(const void *p, const void *q)
{
    return ((pythagoras_t*)p) -> c - ((pythagoras_t*)q) -> c;
}

int main(void)
{
    int index = 0;
    pythagoras_t x[PARAM];
    int tmpA, tmpB;

    for (int m = 1; m * m < PARAM; m++) {
        for (int n = 1; n < m && n * n + m * m < PARAM; n++) {
            if (m % 2 == n % 2)
                continue;
            if (gcd(m, n) > 1)
                continue;

            tmpA = m * m - n * n;
            tmpB = 2 * m * n;
            if (gcd(tmpA, tmpB) == 1) {
                x[index].a = tmpA;
                x[index].b = tmpB;
                x[index].c = m * m + n * n;

                sort_output(&x[index].a, &x[index].b);
                index++;
            }
        }
    }

    qsort(x, index, sizeof(pythagoras_t), cmp);
    for (int i = 0; i < index; i++)
        printf("%3d^2 + %3d^2 = %3d^2 ------- %d\n", x[i].a, x[i].b, x[i].c, check(x[i]));
    return 0;
}
