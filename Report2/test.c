#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <float.h>
#include <stdbool.h>

#define NEARLYZERO 0.00000000001

double getDoubleValue(char *doubleString)
{
    puts("");
    // doubleString is supposed to be an double
    double doubleValue = atof(doubleString);
    char extractedValue[128];
    int getNumberOfCharacters = snprintf(extractedValue, strlen(doubleString) + 1, "%lf", doubleValue);
    if (strcmp(extractedValue, doubleString) == 0) {
        return doubleValue;
    } else {
        fprintf(stderr, "[[[INVALID VALUE DETECTED.]]]\n"
                        "extractedValue: \"%s\"\n"
                        "doubleValue: \"%lf\"\n", extractedValue, doubleValue);
        return doubleValue;
    }
}
bool isNearlyZero(double x)
{
    return fabs(x) < NEARLYZERO;
}
//bool IsNearlyZero(double x)
//{
////    return (fabs(x) < DBL_MIN); // この100は適当に範囲を持たせるためのスケール値
//    return fabs(x) < NEARLYZERO;
//}

int main(void)
{
    char str[256] = "239020.23200";
    char str2[256] = "";
    double dval = atof(str);
    printf("%lf", atof(str));
    puts("");
    snprintf(str2, strlen(str) + 1, "%lf", dval);
    printf(str2);
    puts("");


    char str3[256] = "0003232";
    char str4[256] = "";
    int ival = atoi(str3);
    printf("%d", atoi(str3));
    puts("");
    snprintf(str4, strlen(str3) + 1, "%d", ival);
    printf(str4);
    printf("%lf\n", 1/0);
    if (sin(M_PI) == 0.0L)
        printf("sin(%lf) == 0. is true\n", M_PI);
    else
        printf("false sin(%lf) is %lf\n", M_PI, sin(M_PI));
    if (isNearlyZero(sin(M_PI)))
        printf("Function works: sin(%lf) == 0. is true\n", M_PI);
    printf("getDoubleValue(\"0\") == %lf\n", getDoubleValue("0.00.1"));
    return 0;
}
