#include <stdio.h>
#include <math.h>

int main() {
  int n, i;
  double sum = 0, x;
  (void) scanf("%i", &n);
  for(i = 0; i < n; i++) {
    (void) scanf("%lf", &x);
    if((i + 1) % 2 == 0) {
    sum += pow(x, 2);
    } else {
    sum -= pow(x, 2);
  }
  }
  printf("%lf", sum);
  return 0;
} 
