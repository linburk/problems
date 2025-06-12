#include "stdio.h"
#include "string.h"

int main(int argc, const char **argv) {
  int k1, k2, k3;
  scanf("%d %d %d", &k1, &k2, &k3);
  int r1 = 0, r2 = 0, r3 = 0;
  r1 |= (k1 == 1) | (k2 == 1) | (k3 == 1);
  r2 |= (k1 == 2) | (k2 == 2) << 1 | (k3 == 2) << 2;
  r3 |= (k1 == 3) & (k2 == 3) & (k3 == 3);
  if (r1 | __builtin_popcount(r2) >= 2 | r3) {
    printf("YES\n");
  } else {
    printf("NO\n");
  }
  return 0;
}