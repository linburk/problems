#include "stdio.h"

int past[10][1020][1020][3];
int dp[10][1020][1020];
char ans[100];

int main(int argc, char **argv) {
  int k_, s, p, d;
  scanf("%d %d %d %d", &k_, &s, &p, &d);
  for (int i = 0; i <= s; ++i) {
    for (int j = 0; j <= p; ++j) {
      for (int k = 0; k < 10; ++k) {
        if ((dp[k][i][j] && dp[k][i][j] < k_) || (i == 0 && j == 0 && k == 0)) {
          for (int nk = (k == 0); nk < 10; ++nk) {
            int nj = j + (nk * d % 10 - k * d / 10) + nk * d / 10;
            int ni = i + nk;
            if (dp[nk][ni][nj] && dp[nk][ni][nj] <= dp[k][i][j] + 1) continue;
            dp[nk][ni][nj] = dp[k][i][j] + 1;
            int *pr = past[nk][ni][nj];
            pr[0] = k, pr[1] = i, pr[2] = j;
          }
        }
      }
    }
  }
  for (int k = 1; k < 10; ++k) {
    if (dp[k][s][p]) {
      int *pr = past[k][s][p];
      int i = 1;
      ans[0] = '0' + k;
      while (pr[2] != 0) {
        ans[i++] = '0' + pr[0];
        pr = past[pr[0]][pr[1]][pr[2]];
      }
      while (i < k_)
        ans[i++] = '0';
      for (int j = 0; j < k_; ++j) {
        printf("%c", ans[j]);
      }
      printf("\n");
      return 0;
    }
  }
  printf("-1\n");
}