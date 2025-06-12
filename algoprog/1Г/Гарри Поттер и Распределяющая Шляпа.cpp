#include "stdint.h"
#include "stdio.h"
#include "strings.h"
int main(int argc, char **argv) {
  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    uint64_t n, p;
    scanf("%llu %llu", &n, &p);
    uint64_t res = 0;
    while (n > 1) {
      uint64_t t = 1 << (63 - __builtin_clzll(n));
      n -= (t == n ? t / 2 : t);
      ++res;
    }
    printf("%llu\n", res % p);
  }
  return 0;
}