#include <stdio.h>
#include <string.h>

enum {
    LENGTH = 1024,
};

int main(void)
{
    char str[LENGTH];
    char *p;
    fgets(str, sizeof(str) - 1, stdin);
    if (p = strchr(str, '\n'))
        *p = '\0';
    else
        str[LENGTH - 1] = '\0';
    for (unsigned int i = 0; i < strlen(str); i++)
        if (i % 2)
            printf("%c ", str[i]);
    puts("");

    return 0;
}
