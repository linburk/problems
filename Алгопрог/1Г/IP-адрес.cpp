#include "regex.h"
#include "stdio.h"
const char IPREGEX[] = "^((((25[0-5]?)|(2[0-4]?[0-9]?)|([0-1][0-9]?[0-9]?))\.){"
                       "3}((25[0-5]?)|(2[0-4]?[0-9]?)|([0-1][0-9]?[0-9]?)))$";

int main(int argc, char **argv) {
  char str[16];
  scanf("%15s", str);
  regex_t reg;
  regcomp(&reg, IPREGEX, REG_EXTENDED);
  int cnt = regexec(&reg, str, 0, 0, 0);
  printf("%d", cnt != REG_NOMATCH);
  return 0;
}