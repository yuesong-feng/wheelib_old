#include <math.h>
#include <stdio.h>
#include <string.h>

int main() {
  double a = NAN;
  if (a == HUGE_VAL) {
    printf("%lf\n", a);
  }
  else if(a == -HUGE_VAL) {
    printf("%lf\n", a);
  }
  else if(isnan(a)) {
    printf("%lf\n", a);
  }
  return 0;
}