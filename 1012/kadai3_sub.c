#include <stdio.h>
#include <math.h>

enum {
    SUFFICIENT_SMALL = 0.0000000001,
};

double function(double x)
{
    return exp(x) + x;
}

double newton(double (*function)(double));

int main(void)
{
    printf("intersection of the x-axis of function(x) is %f\n", newton(function));
    return 0;
}

double newton(double (*function)(double a))
{
    double x = 0.L;
    if (function(x) >= function(x + SUFFICIENT_SMALL)) {
        while (function(x) <= 0.L) {
            x += 1.L;
        }
        return newton_sub(function, x);
    } else {
        while (function(x) <= 0.L) {
            x -= 1.L;
        }
        return newton_sub(function, x);
    }
}
