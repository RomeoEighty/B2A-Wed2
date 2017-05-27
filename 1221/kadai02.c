/*
 * 540479c
 * Ryutaro Yamaguchi
 * kadai02.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double h_step     = 0.001;

void ndsolve(double (**)(double*, double), double*, double, double, int);


double Rossler_chaos0(double*, double);
double Rossler_chaos1(double*, double);
double Rossler_chaos2(double*, double);

double (*Rc[3])(double*, double) = {Rossler_chaos0,
                                    Rossler_chaos1,
                                    Rossler_chaos2};
int main(void)
{
    double x[3] = {0., 0., 0.};
    ndsolve(Rc, x, 0, 800, 3);
    return 0;
}

/*
 * Rossler_chaos
 */
double c_1 = 0.15;
double c_2 = 0.20;
double c_3 = 7.10;
double Rossler_chaos0(double *x , double t)
{
    return - x[1] - x[2];
}
double Rossler_chaos1(double *x , double t)
{
    return x[0] + c_1 * x[1];
}
double Rossler_chaos2(double *x , double t)
{
    return c_2 + x[2] * (x[0] - c_3);
}

/*
 * ndsolve:
 *      a function for solving ordinary differential equations and printing values at each time
 *      in soving ODE, apply "the midpoint method"
 *      f : a pointer to a pointer to a function
 *      x0 : an initial value
 *      t0 : an initial time
 *      tend : an terminal time
 *      N : dimention of system
 */
void ndsolve(double (**f)(double*, double), double *x0, double t0, double tend, int N)
{
    double *x     = malloc(sizeof(double) * N);
    double *x_buf = malloc(sizeof(double) * N);
    for (int i = 0; i < N; i++) {
        x[i]     = x0[i];
        x_buf[i] = x0[i];
    }

    for (double t = t0; t <= tend; t += h_step) {
        printf("%lf\t", t);
        
        for (int i = 0; i < N; i++) {
            x_buf[i] = x[i] + h_step / 2 * f[i](x, t);
        }
        for (int i = 0; i < N; i++) {
            printf("%lf\t", x[i]);
            x[i] = x[i] + h_step * f[i](x_buf, t + h_step / 2);
        }
        puts("");
    }
}
