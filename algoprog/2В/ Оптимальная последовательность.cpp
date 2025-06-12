#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a, b) ((a) > (b) ? (a) : (b))
int get_len(int x) {
  int cnt = 1;
  while (x) {
    x /= 10;
    cnt *= 10;
  }
  return cnt;
}

int main(int argc, char *argv[]) {
#ifdef __APPLE__
  freopen("/Users/dmitrii/Documents/Code/Code/input.txt", "r", stdin);
  freopen("/Users/dmitrii/Documents/Code/Code/output.txt", "w", stdout);
#endif
  int resheto[1000000];
  for (int i = 0; i < 1000000; i++)
    resheto[i] = 1;
  resheto[0] = resheto[1] = 0;
  for (int i = 2; i < 1000; i++) {
    if (resheto[i]) {
      for (int j = i + i; j < 1000000; j += i) {
        resheto[j] = 0;
      }
    }
  }
  int n;
  scanf("%d", &n);
  int r[1000][1000];
  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 1000; j++) {
      r[i][j] = 0;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      r[i][j] = max(r[i - 1][j], r[i][j - 1]) + resheto[i * get_len(j) + j];
    }
  }
  printf("%d", r[n][n] - 1);
  return 0;
}