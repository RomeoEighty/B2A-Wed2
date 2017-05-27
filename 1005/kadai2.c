#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

enum {
    STRINGLENGTH = 4096,
};

bool isNewline(char ch)
{
    if (ch == '\n')
        return true;
    return false;
}

int main(void)
{
    char buf[STRINGLENGTH];
    int index = 0;
    bool newline = true;
    bool flag = false;

    while ((buf[index++] = fgetc(stdin)) != EOF);

    for (int i = 0; i < strlen(buf); i++) {
        if (!newline)
            newline = isNewline(buf[i]);
        else {
            while (isalpha(buf[i])) {
                flag = true;
                putchar(buf[i++]);
            }
            if (flag) {
                puts("");
                newline = false;
                flag = false;
            }
        }
    }

    return 0;
}
