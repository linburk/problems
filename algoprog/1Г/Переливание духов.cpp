#include "stdio.h"
#include "strings.h"
int main(int argc, char **argv) {
  int flacons[102][102];
  int n, m;
  scanf("%d %d", &n, &m);
  bzero(flacons, 102 * 102 * sizeof(int));
  for (int i = 1; i <= n; ++i) {
    int l, v;
    scanf("%d %d", &l, &v);
    flacons[i][l] = 100 * v;
  }
  int k;
  scanf("%d", &k);
  for (int i = 0; i < k; ++i) {
    int s, t, a;
    scanf("%d %d %d", &s, &t, &a);
    int vol[102];
    for (int j = 1; j <= m; ++j) {
      vol[j] = flacons[s][j] / 100 * a;
      flacons[s][j] -= vol[j];
    }
    for (int j = 1; j <= m; ++j) {
      flacons[t][j] += vol[j];
    }
  }
  for (int i = 1; i <= 1; ++i) {
    int sum_vol = 0;
    for (int j = 1; j <= m; ++j) {
      sum_vol += flacons[i][j];
    }
    for (int j = 1; j <= m; ++j) {
      printf("%.2f ", (double)(flacons[i][j]) / sum_vol * 100);
    }
    printf("\n");
  }
}