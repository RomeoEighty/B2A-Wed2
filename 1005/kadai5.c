#include <stdio.h>
#include <stdbool.h>
#include <math.h>

enum {
    MAXNUM = 1000,
};

bool num[MAXNUM + 1];

void init(void);
int next_prime(int);
void sieve(void);
void print_result(void);

int main(void)
{
    init();
//    printf("%d\n\n", next_prime(0));
    sieve();
    print_result();
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
