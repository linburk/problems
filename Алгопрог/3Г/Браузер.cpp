#include "stdio.h"

#define min(a, b) ((a) < (b) ? (a) : (b))
#define abs(a) ((a) < 0 ? -(a) : (a))
int main(int argc, const char **argv) {
  int n, pos, l, r, res;
  scanf("%d %d %d %d", &n, &pos, &l, &r);
  if (l == 1 && r == n) {
    res = 0;
  } else if (l == 1 || r == n) {
    res = 1 + min(abs(pos - l), abs(pos - r));
  } else {
    res = 2 + (r - l) + min(abs(pos - l), abs(pos - r));
  }
  printf("%d\n", res);
}