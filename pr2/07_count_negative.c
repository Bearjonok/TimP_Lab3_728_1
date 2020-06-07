#include <stdio.h>

int main() {
  int n, i, count = 0;
  double input;
  (void) scanf("%i", &n);
  for(i = 0; i < n; i++) {
    (void) scanf("%lf", &input);
    if(input<0) {
        count++;
    }
  }
  printf("%d", count);
  return 0;
} 
