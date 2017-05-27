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

double random_normal_d(double mu, double sigma)
{
    return random_normal() * sigma + mu;
}
