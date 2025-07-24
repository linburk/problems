#include "stdio.h"
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define abs(a) ((a) < 0 ? -(a) : (a))
int main(int argc, char **argv) {
  int n, i, j;
  scanf("%d %d %d", &n, &i, &j);
  printf("%d", min(abs(i - j), min(i, j) + n - max(i, j)) - 1);
}