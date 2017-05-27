#include <stdio.h>
#include <stdbool.h>
#include <math.h>

enum {
    MAXNUM = 10000,
};

bool num[MAXNUM + 1];

void init(void);
int next_prime(int);
void sieve(void);
void print_result(void);
bool isPrime(int);
long double eulerProduct(void);

int main(void)
{
    init();
//    printf("%d\n\n", next_prime(0));
    sieve();
//    print_result();
    printf("pi = %Lf\n", eulerProduct());
    return 0;
}

void init(void)
{
    num[0] = false;
    num[1] = false;
    for (int i = 2; i < MAXNUM + 1; i++)
        num[i] = true;
}

int next_prime(int i)
{
    for (++i; !(num[i]); i++);
    return i;
}

void sieve(void)
{
    for (int i = next_prime(0); i <= sqrt((double)MAXNUM); i = next_prime(i))
        for (int j = i * 2; j <= MAXNUM; j += i) 
            num[j] = false;
}

void print_result(void)
{
    for (int i = 0; i <= MAXNUM; i++) {
        if (num[i])
            printf("%d ", i);
    }
    puts("");
}

bool isPrime(int i)
{
    return num[i];
}

long double eulerProduct(void)
{
    long double pi = 1.0L;
    for (int i = next_prime(0); i <= MAXNUM; i = next_prime(i))
        pi *= (1.0L - (1 / (long double)i / (long double)i));
    return sqrt(6.0L / pi);
}
