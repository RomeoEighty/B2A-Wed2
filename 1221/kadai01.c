/*
 * 540479c
 * Ryutaro Yamaguchi
 * kadai01.c
 * solve transient reaction of RL circuit
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double h_step     = 0.001;
double Resistance = 1.0  ;
double Lenz       = 1.0  ;

void ndsolve(double (*)(double, double), double, double, double);

double RL(double, double);

int main(void)
{
    ndsolve(RL, 0, 0, 10);
    return 0;
}

/*
 * Input voltage is a square wave
 */
double RL(double i , double t)
{
    if (t <= 2 && t >= 1) {
        return ((1.0 - i * Resistance) / Lenz);
    } else {
        return ((0.0 - i * Resistance) / Lenz);
    }
}

/*
 * ndsolve:
 *      a function for solving ordinary differential equations and printing values at each time
 *      in soving ODE, apply "the midpoint method"
 *      f : a pointer to a function
 *      x0 : an initial value
 *      t0 : an initial time
 *      tend : an terminal time
 */
void ndsolve(double (*f)(double, double), double x0, double t0, double tend)
{
    double func = x0;
    for (double t = t0; t <= tend; t += h_step) {
        printf("%lf\t%lf\n", t, func);
        func = func + h_step * f(func + h_step / 2 * f(func, t), t + h_step / 2);
    }
}
