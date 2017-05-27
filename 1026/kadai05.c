#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int roman2num_sub(char roman);
int roman2num(char*);
bool sys_is_little_endian(void);

int main(void)
{
    printf("XIV = %d\n", roman2num("XIV")); //14
    printf("CDXCV = %d\n", roman2num("CDXCV")); //495
    printf("MCMXLV = %d\n", roman2num("MCMXLV")); //1945
    printf("MMMCMXCIX = %d\n", roman2num("MMMCMXCIX")); //3999
    return 0;
}

int roman2num_sub(char roman)
{
    char components[] = "MDCLXVI"; /* M:1000, D:500, C:100, L:50, X:10, V:5, I:1 */
    int arabicnums[] = {1000, 500, 100, 50, 10, 5, 1};

    for (int i = 0; i < strlen(components); i++) {
        if (components[i] == roman) {
            return arabicnums[i];
        }
    }
    return EOF;
}


int roman2num(char *roman)
{
    int num = 0;
    int val;


    for (size_t i = 0; i < strlen(roman); i++) {
        if ((val = roman2num_sub(roman[i])) < roman2num_sub(roman[i + 1])) {
            num -= val;
        } else {
            num += val;
        }
    }
    return num;
}
