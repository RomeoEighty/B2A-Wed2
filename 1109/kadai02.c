#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum {
    BUFSIZE = 64,
    LINENUMS = 10000,
};

char SOURCEFILE[] = "sentence.txt";
char TARGETFILE[] = "sentence(capitalized).txt";

int bufloc = 0;
char BUF[3];

char check_buf(int loc)
{
    if (loc == 0) {
        return BUF[bufloc];
    } else if (loc == 1) {
        if (bufloc <= 1) {
            return BUF[bufloc + loc];
        } if (bufloc == 2) {
            return BUF[0];
        }
    } else /*if (loc == 2)*/ {
        if (bufloc == 0) {
            return BUF[2];
        } else if (bufloc == 1) {
            return BUF[0];
        } else {
            return BUF[1];
        }
    }
}
void capitalize_buf(int loc)
{
    if (loc == 0) {
        BUF[bufloc] = toupper(BUF[bufloc]);
    } else if (loc == 1) {
        if (bufloc <= 1) {
            BUF[bufloc + loc] = toupper(BUF[bufloc + loc]);
        } if (bufloc == 2) {
            BUF[0] = toupper(BUF[0]);
        }
    } else if (loc == 2) {
        if (bufloc == 0) {
            BUF[2] = toupper(BUF[2]);
        } else if (bufloc == 1) {
            BUF[0] = toupper(BUF[0]);
        } else {
            BUF[1] = toupper(BUF[1]);
        }
    }
}
char dump_buf_sub(void)
{
    char tmp = BUF[bufloc];
    if (bufloc == 2) {
        bufloc = 0;
    } else {
        bufloc++;
    }
    return tmp;
}
char* dump_buf(void)
{
    static char str[3];
    for (int i = 0; i < 3; i++) {
        str[i] = dump_buf_sub();
    }
    return str;
}
void push_buf(char ch)
{
    BUF[bufloc] = ch;
    if (bufloc == 2) {
        bufloc = 0;
    } else {
        bufloc++;
    }
}
char push(char ch)
{
    char tmp;
    tmp = check_buf(0);
    push_buf(ch);
    return tmp;
}
typedef enum {
    CAPITALIZED,
    SENTENCEENDED,
    IS_I_OR_NOT,
    IS_I_OR_NOT2,
} state_t;
int main(void)
{
    FILE *fpr;
    FILE *fpw;
    state_t state = SENTENCEENDED;
    int counter = 0;

    if ((fpr = fopen(SOURCEFILE, "r")) == NULL) {
        printf("source file cannot open\n");
        return 1;
    }
    if ((fpw = fopen(TARGETFILE, "w")) == NULL) {
        printf("source file cannot open\n");
        return 1;
    }

    char ch;
    while ((ch = fgetc(fpr)) != EOF) {
        switch (state) {
        case CAPITALIZED:
            if (ch == '.' || ch == '?' || ch == '!') {
                state = SENTENCEENDED;
            } else if (ch == ' ') {
                state = IS_I_OR_NOT;
            }
            break;
        case SENTENCEENDED:
            if (isalpha(ch)) {
                ch = toupper(ch);
                state = CAPITALIZED;
            } else if (ch == '"') {
                /* after quote, capitalize is not needed */
                if (check_buf(2) != ' ') {
                    state = CAPITALIZED;
                }
            }
            break;
        case IS_I_OR_NOT: 
            if (ch == 'i') {
                state = IS_I_OR_NOT2;
            } else if (/* ch != 'i' && */isalpha(ch)) {
                state = CAPITALIZED;
            }
            break;
        case IS_I_OR_NOT2:
            if (ch == ' ' || ch == '\'') {
                capitalize_buf(2);
            }
            state = CAPITALIZED;
            break;
        }
        if (counter++ > 2) {
            fputc(push(ch), fpw);
        } else {
            push(ch);
        }
    }
    fputs(dump_buf(), fpw);

    fclose(fpw);
    fclose(fpr);
    return 0;
}
