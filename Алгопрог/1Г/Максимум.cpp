#include "stdint.h"
#include "stdio.h"
#include "strings.h"
int main(int argc, char **argv) {
  uint16_t a = 0x0000, b = 0x0000, res = 0x0000, diff = 0x0000;
  scanf("%hu %hu", &a, &b);
  diff = ((a - b) & 0x8000) >> 15;
  res = (diff ^ 1) * a + diff * b;
  printf("%hu", res);
  return 0;
}