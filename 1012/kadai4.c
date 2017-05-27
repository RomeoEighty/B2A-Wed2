#include <stdio.h>
#include <stdbool.h>
#include <math.h>

enum {
    TARGETNUM = 123456789,
};

bool num[TARGETNUM + 1];

void init(void);
int next_prime(int);
void sieve(void);
void print_result(void);
bool isPrime(int);

void print_factor(int);

int main(void)
{
    init();
//    printf("%d\n\n", next_prime(0));
    sieve();


    printf("Prime facror of %d\n%d = ", TARGETNUM, TARGETNUM);
    print_factor(TARGETNUM);
    return 0;
}

void init(void)
{
    num[0] = false;
    num[1] = false;
    for (int i = 2; i < TARGETNUM + 1; i++) {
        num[i] = true;
    }
}

int next_prime(int i)
{
    for (++i; !(num[i]); i++);
    return i;
}

void sieve(void)
{
    for (int i = next_prime(0); i <= sqrt((double)TARGETNUM); i = next_prime(i)) {
        for (int j = i * 2; j <= TARGETNUM; j += i) {
            num[j] = false;
        }
    }
}

void print_result(void)
{
    for (int i = 0; i <= TARGETNUM; i++) {
        if (num[i]) {
            printf("%d ", i);
        }
    }
    puts("");
}

bool isPrime(int i)
{
    return num[i];
}

void print_factor(int target)
{
    static int count = 0;
    int i;
    if (target == 1) {
        return;
    } else {
        for (i = next_prime(0); target % i != 0; i = next_prime(i)) {
            // do nothing
        }
        if (count++ == 0) {
            printf("%d ", i);
        } else {
            printf("* %d ", i);
        }
        print_factor(target / i);
    }
}
