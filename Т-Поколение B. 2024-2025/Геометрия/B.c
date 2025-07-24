#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[], char* envp[])
{
  int a, r;
  scanf("%d %d", &a, &r);
  double const pi = 4 * atan(1.0l);
  double square;
  if (r <= a / 2.0l) {
    square = pi * r * r;
  } else if (r < a / sqrt(2.0l)) {
    double angle = acos(a / 2.0l / r);
    square = pi * r * r - 4 * angle * r * r + 2 * sin(angle) * a * r;
  } else {
    square = a * a;
  }
  printf("%.7f\n", square);
}
