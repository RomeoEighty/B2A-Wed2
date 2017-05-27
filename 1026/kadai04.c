#include <stdio.h>
#include <string.h>

void uppercase(char *);

int main(void)
{
    char str[] = "hello world";
    uppercase(str);
    printf("%s\n", str);
    return 0;
}

void uppercase(char *str)
{
    for (size_t i = 0; i < strlen(str); i++) {
        if ('a' <= str[i] && str[i] <= 'z') {
            str[i] = str[i] + 'A' - 'a';
        }
    }
}
