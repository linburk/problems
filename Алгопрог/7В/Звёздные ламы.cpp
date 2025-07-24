#include <stdio.h>
#include <string.h>
int main(int argc, char **argv) {
  char buff[100];
  bzero(buff, 100);
  while (1) {
    scanf("%s", buff);
    if (buff[0] == 'I')
      return 0;
    printf("%s\n", buff);
    fflush(stdout);
  }
}