#include "stdio.h"

int main(int argc, const char **argv) {
  char t[2001][2001];
  int n, m, k;

  scanf("%d %d %d\n", &n, &m, &k);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      scanf("%c", &t[i][j]);
    }
    scanf("\n");
  }
  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    for (int l = 0, r = 0; l < m;) {
      if (t[i][l] == '*') {
        ++l;
        continue;
      }
      r = l;
      while (r < m && t[i][r] == '.')
        ++r;
      if (r - l - k >= 0)
      cnt += (r - l + 1 - k);
      l = r;
    }
  }
  for (int j = 0; j < m; ++j) {
    for (int l = 0, r = 0; l < n;) {
      if (t[l][j] == '*') {
        ++l;
        continue;
      }
      r = l;
      while (r < n && t[r][j] == '.')
        ++r;
      if (r - l - k >= 0)
      cnt += (r - l + 1 - k);
      l = r;
    }
  }
  printf("%d\n", cnt);
}