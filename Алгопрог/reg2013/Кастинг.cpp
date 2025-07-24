#include <stdio.h>

#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)

int main(int argc, char **argv) {
  int d;
  scanf("%d", &d);
  int n, a, b, c;
  scanf("%d %d %d %d", &n, &a, &b, &c);
  if (d == 2) {
    printf("%d\n", min(a, min(b, c)));
  } else {
    printf("%d\n", n - min(a, min(b, c)));
  }
}