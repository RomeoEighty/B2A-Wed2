#include <stdio.h>
#include <stdlib.h>

#define PARAM 1000

typedef struct {
    int a;
    int b;
    int c;
} pythagoras_t;

void quick_sort_sub(int *data, int left, int right);
void quick_sort(int *data, int data_size);

int gcd(int m, int n)
{
    while (1) {
        if (n >= m) {
            int tmp = m;
            m = n;
            n = tmp;
        }
        if (n == 0)
            return 0;
        n = m % n;
    }
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

    for (int m = 1; m * m < PARAM; m++) {
        for (int n = 1; n < m && n * n + m * m < PARAM; n++) {
            if (m % 2 == n % 2)
                continue;
            if (gcd(m, n) > 1)
                continue;

            x[index].a = m * m - n * n;
            x[index].b = 2 * m * n;
            x[index].c = m * m + n * n;

            sort_output(&x[index].a, &x[index].b);
            index++;
        }
    }

    qsort(x, index, sizeof(pythagoras_t), cmp);
    for (int i = 0; i < index; i++)
        printf("%3d^2 + %3d^2 = %3d^2\n", x[i].a, x[i].b, x[i].c);
    return 0;
}
