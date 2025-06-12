#include "stdio.h"
#include "string.h"
int main(int argc, const char **argv) {
  int n;
  scanf("%d", &n);
  printf("%d", (n) * (n + 1) / 4 + 1);
  return 0;
}