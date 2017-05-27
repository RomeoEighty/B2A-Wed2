/*
 * kadai03
 * solve problem by using Monte Carlo method
 * 540479c
 * Yamaguchi Ryutaro
 */

#include <stdio.h>
#include <limits.h>
#include <math.h>

#define MAX_XORSHIFT 4294967295

unsigned int xorshift(void)
{
    static unsigned int x = 1;
    static unsigned int y = 2;
    static unsigned int z = 3;
    static unsigned int w = 4;
    unsigned int t;
    t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

int random_integer(int m)
{
    return xorshift() % m;
}

double random_double(void)
{
    return xorshift() * 1.0 / MAX_XORSHIFT;
}

double random_normal()
{
    return sqrt(-2*log(random_double())) * cos(2 * M_PI * random_double());
}

int cards[52];
int card_num;
int selected_cards[4];

void init(void)
{
    card_num = 52;
    for (int i = 0; i < 52; i++) {
        cards[i] = i;
    }
    for (int i = 0; i < 4; i++) {
        selected_cards[i] = EOF;
    }
}

int take_card(void)
{
    int i = random_integer(card_num--);
    int j = 0;
    j = cards[i];
    cards[i] = cards[card_num];
    return j % 4;
}

double calc_waseda(void)
{
    int max_count = 10000000;
    int count = 0;
    int indicater = 0;
    int i;
    for (i = 0; i < max_count; ) {
        init();
        for (int j = 0; j < 4; j++) {
            selected_cards[j] = take_card();
        }
        if (selected_cards[1] == 0 &&
            selected_cards[2] == 0 &&
            selected_cards[3] == 0) {
            i++;
            if (selected_cards[0] == 0) {
                count++;
            }
        }
        if (max_count >= 10000 && (double)i / max_count >= (double)indicater / 100) {
            printf("\r%d%%", indicater++);
            fflush(stdout);
        }
    }
    return (double) count / max_count;
}

int main(void)
{
    printf("\n%f\n", calc_waseda());
    return 0;
}
