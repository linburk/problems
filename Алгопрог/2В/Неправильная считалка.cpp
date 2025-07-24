#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

int gcd(int a, int b) {
  int t;
  while (b) {
    a %= b;
    t = a;
    a = b;
    b = t;
  }
  return a;
}

int main(int argc, char *argv[]) {
#if 0
  freopen("/Users/dmitrii/Documents/Code/Code/input.txt", "r", stdin);
  freopen("/Users/dmitrii/Documents/Code/Code/output.txt", "w", stdout);
#endif
  int n, k;
  scanf("%d %d", &n, &k); k %= n;
  printf("%d", n - n / gcd(n, k));
}