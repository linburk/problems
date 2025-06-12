#include "stdio.h"
#include "string.h"

typedef long long i64;

int main(int argc, const char **argv) {
  i64 n, k;
  scanf("%lld %lld", &n, &k);
  if (k > 1) {
    n |= (1 << (63 - __builtin_clzll(n))) - 1;
  }
  printf("%lld\n", n);
  return 0;
}