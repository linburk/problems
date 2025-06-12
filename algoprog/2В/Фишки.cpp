#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

int n;
int rec(int pos) {
  if (n == 0)
    return 0;
  if (pos == n)
    return --n;
  printf("%d ", pos + 1);
  if (pos > 0) printf("%d ", -pos);
  rec(pos + 1);
  rec(0);
  return 0;
}

int solve() {
  scanf("%d", &n);
  rec(0);
  return 0;
}

int main(int argc, char *argv[]) {
#if 1
  freopen("/Users/dmitrii/Documents/Code/Code/input.txt", "r", stdin);
  freopen("/Users/dmitrii/Documents/Code/Code/output.txt", "w", stdout);
#endif
  return solve();
}