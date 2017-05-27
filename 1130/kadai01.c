#include <stdio.h>
#include <stdlib.h>

typedef struct monomial {
    int c;
    int n;
} monomial_t;

monomial_t *construct_monomial(int c, int n)
{
    monomial_t *monomial;
    monomial = (monomial_t *)malloc(sizeof(monomial_t));
    monomial->c = c;
    monomial->n = n;
    return monomial;
}

void diff_monomial(monomial_t *m)
{
    m->c = m->c * m->n;
    m->n = m->n - 1;
}

void print_monomial(monomial_t *m)
{
    printf("%d*x^%d\n", m->c, m->n);
}


int main(void)
{
    monomial_t *m1;
    m1 = construct_monomial(-4, 10);
    print_monomial(m1);
    diff_monomial(m1);
    print_monomial(m1);
    free(m1);
    return 0;
}
