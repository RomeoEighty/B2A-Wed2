#include <stdio.h>
#include <math.h>

int zeller(int year, int month, int day)
{
    int pre_y = year / 100;
    int pos_y = year % 100;
    return (pos_y + pos_y / 4 + pre_y / 4 - 2 * pre_y + 13 * (month + 1) / 5 + day) % 7;
}

int main(void)
{
    int y, m, d;
    int wod;
    printf("Please input [year] [month] [day]\n");
    scanf("%d%d%d", &y, &m, &d);
    wod = zeller(y, m, d);

    switch (wod) {
    case 1:
        puts("Sun");
        break;
    case 2:
        puts("Mon");
        break;
    case 3:
        puts("Tue");
        break;
    case 4:
        puts("Wed");
        break;
    case 5:
        puts("Thu");
        break;
    case 6:
        puts("Fri");
        break;
    default:
        puts("Sar");
        break;
    }

    return 0;
}
