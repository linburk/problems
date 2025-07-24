#include "stdio.h"
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define abs(a) ((a) < 0 ? -(a) : (a))
int main(int argc, char **argv) {
  int l, k;
  scanf("%d %d", &l, &k);
  int fi, se, mi = -1;
  for (int i = 0; i < k; ++i) {
    int x;
    scanf("%d", &x);
    if (i == 0)
      fi = x;
    if (i == k - 1)
      se = x;
    if (x == l / 2 && !(l & 1) || (l & 1) && (x == l / 2 || x == (l + 1) / 2))
      mi = x;
  }
  if (mi != -1)
    printf("%d", mi);
  else
    printf("%d %d", fi, se);
}