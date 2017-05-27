#include <stdio.h>

void increment(int *);

int main(void)
{
    int a = 10;
    increment(&a);
    printf("%d\n",a); //出力 11
    return 0;
}
void increment(int *n)
{
    (*n)++;
}
