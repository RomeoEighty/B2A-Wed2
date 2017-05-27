#include <stdio.h>

int compare_cube(const int target, const int root)
{
    return ((root * root * root) > target) - ((root * root * root) < target);
}

int main(void)
{
    int n = 158340421;

    int a = 1000;
    int b = 100;

    while (compare_cube(n, a) != 0 && b >= 1) {
        for (; compare_cube(n, a) > 0; a -= b);
        if (b > 1)
            a += b;
        b /= 10;
    }
    printf("cube root of %d = %d\n", n, a);

    return 0;
}
