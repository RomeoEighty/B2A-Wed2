#include <stdio.h>

enum {
    DIVIDEND_BASE = 541,
    DIVIDEND_LOG = 1234,
    DIVISOR = 1299709,
};

int mod_apm(int, int, int);

int main(void)
{
    printf("%d^%d mod %d = %d\n", DIVIDEND_BASE, DIVIDEND_LOG, DIVISOR, mod_apm(DIVIDEND_BASE, DIVIDEND_LOG, DIVISOR));
    return 0;
}

int mod_apm(int dividend_base, int dividend_log, int divisor)
{
    if (dividend_log > 0) {
        return (dividend_base * mod_apm(dividend_base, dividend_log - 1, divisor)) % divisor;
    } else {
        return 1;
    }
}
