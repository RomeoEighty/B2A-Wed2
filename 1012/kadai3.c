#include <stdio.h>
#include <math.h>

#define    SUFFICIENT_SMALL 0.0000000001

double function(double x)
{
    return exp(x) + x;
}

double dfdx(double x)
{
    return exp(x) + 1;
}

double newton(double);

int main(void)
{
    double x0 = 0.;
    printf("intersection of the x-axis of function(x) is %f\n", newton(x0));
    return 0;
}

double newton(double x)
{
    double x_next = x - function(x) / dfdx(x);
    if (fabs(x - x_next) <= SUFFICIENT_SMALL) {
        return x_next;
    } else {
        return newton(x_next);
    }
}
