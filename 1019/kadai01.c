#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
  隱ｿ蜥檎ｴ壽焚 ¥sum_{i=1}^{n}(1 / i)
*/
double harmonic(int n) {
  double i;
  double sum = 0.;
  for (i = 1;i <= n;i++) {
    sum += 1 / i;
  }

  return sum;
}

int main() {
  int i;
  int upto = 5;
  double log_val;
  double harmonic_val;
  int N;

  for (i = 0;i <= upto;i++) {
    N = (int) pow(10, i);
    log_val = log(N + 1);
    harmonic_val = harmonic(N);
    printf("%f, %f\n", log_val, harmonic_val);
  }

  return 0;
}
