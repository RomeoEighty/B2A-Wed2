#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void arabic2roman(int , char*, size_t size);

int main(void)
{
    char roman[32] = {};

    arabic2roman(14, roman, sizeof(roman));
    printf("14 = %s\n", roman); //XIV
    arabic2roman(495, roman, sizeof(roman));
    printf("495 = %s\n", roman); //CDXCV
    arabic2roman(1945, roman, sizeof(roman));
    printf("1945 = %s\n", roman); //MCMXLV
    arabic2roman(3999, roman, sizeof(roman));
    printf("3999 = %s\n", roman); //MMMCMXCIX
    return 0;
}

void arabic2roman(int arabic, char *roman, size_t size)
{
    char *components[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"}; /* M:1000, D:500, C:100, L:50, X:10, V:5, I:1 */
    int arabicnums[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

    for (size_t i = 0; i < size; i++) {
        roman[i] = '\0';
    }

    while (arabic > 0) {
        for (size_t i = 0; i < sizeof(arabicnums) / sizeof(int); i++) {
            for (; arabic >= arabicnums[i]; arabic -= arabicnums[i]) {
                strcat(roman, components[i]);
            }
        }
    }
}
