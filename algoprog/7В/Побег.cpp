#include <stdio.h>

int table[101][101];

int main(int argc, char **argv) {
  int k, b, x, y;
  scanf("%d\n%d\n%d %d", &k, &b, &x, &y);
  x--, y--, b--;
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < k; j++) {
      if ((i + j) % 2 == (x + y) % 2)
        table[i][j] = 1;
    }
  }
  for (int i = 1; i < k; i++) {
    for (int j = -1; j <= 1; j++) {
      if (b + j >= 0 && b - j < k && table[i][b + j] != 1) {
        b += j;
        printf("%d %d\n", i + 1, b + 1);
        fflush(stdout);
        break;
      }
    }
    if (i == k - 1)
      break;
    scanf("%d %d", &x, &y);
  }
  return 0;
}