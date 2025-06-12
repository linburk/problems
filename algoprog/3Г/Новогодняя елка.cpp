#include "stdio.h"
#include "string.h"
int main(int argc, const char **argv) {
  int par[1001];
  char is_leaf[1001];
  int cnt[1001];
  memset(par, 0, sizeof(int) * 1001);
  memset(is_leaf, 1, 1001);
  memset(cnt, 0, sizeof(int) * 1001);
  int n;
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int p;
    scanf("%d", &p);
    --p;
    par[i] = p;
  }
  char res = 1;
  for (int i = 0; i < n; ++i) {
    is_leaf[par[i]] = 0;
  }
  for (int i = 0; i < n; ++i) {
    if (is_leaf[i])
      ++cnt[par[i]];
  }
  for (int i = 0; i < n; ++i) {
    if (!is_leaf[i] && cnt[i] < 3)
      res = 0;
  }
  printf("%s\n", res ? "Yes" : "No");
}