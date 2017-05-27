#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char*);

int main(void)
{
    char s[] = "hello";

    reverse(s);
    printf("%s\n", s);
    return 0;
}

void reverse(char *str)
{
    char *tmp = (char *)malloc(sizeof(char) * (strlen(str) + 1));
    for (size_t i = 0; i < strlen(str); i++) {
        tmp[i] = str[strlen(str) - 1 - i];
    }
    strcpy(str, tmp);
}
