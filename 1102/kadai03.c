/* 
 * ------------------------
 * 16/11/02
 * kadai03
 * 540479c
 * Ryutaro Yamaguchi
 * "divide polynomial into monomials"
 * ------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_mono(char *str)
{
    int count = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (i != 0 && (str[i] == '+' || str[i] == '-')) {
            count++;
        }
    }
    return count + 1;
}
void divide_poly(char *src, char **dests)
{
    char buf[16] = {};
    int j = 0;
    int polynum = 0;
    for (int i = 0; i < strlen(src); i++) {
        if (i != 0 && (src[i] == '-' || src[i] == '+')) {
            strcpy(dests[polynum++], buf);
            j = 0;
            memset(buf, '\0', 16);
            if (src[i] == '+') {
                continue;
            }
        }
        buf[j++] = src[i];
    }
    strcpy(dests[polynum], buf);
}

void print_strings(char **src, int strnum)
{
    for (int i = 0; i < strnum; i++) {
        printf("Monomial %d = %s\n", i + 1, src[i]);
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Usage: %s \"[formula]\"", argv[0]);
    }

    char str[128];
    strcpy(str, argv[1]);
    printf("Polynomial = %s\n", str);
//  printf("strlen(str)=%lu\n\n", strlen(str));
//  printf("numbers of monomials: %d\n\n", count_mono(str));
    int num_of_mono = count_mono(str);
    char **monomials = (char **)malloc(sizeof(char*) * num_of_mono);
    for (int i = 0; i < num_of_mono; i++) {
        monomials[i] = (char *)malloc(sizeof(char) * 16);
    }
    divide_poly(str, monomials);
    print_strings(monomials, num_of_mono);

    return 0;
}
