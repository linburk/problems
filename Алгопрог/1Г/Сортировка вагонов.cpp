#include "stdio.h"
#include "strings.h"

int main(int argc, char **argv) {
  int train[2002];
  int n_train[2002];
  bzero(train, sizeof(int) * 2002);
  bzero(n_train, sizeof(int) * 2002);
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &train[i]);
  }
  int command[4004];
  int stack[2002];
  int s_size = 0;
  int n_size = 0;
  int c_size = 0;
  for (int i = 0; i < n; ++i) {
    while (s_size && stack[s_size - 1] <= train[i]) {
      n_train[n_size++] = stack[--s_size];
      command[c_size++] = 2;
    }
    if (!s_size || stack[s_size - 1] > train[i]) {
      stack[s_size++] = train[i];
      command[c_size++] = 1;
    }
  }
  while (s_size) {
    n_train[n_size++] = stack[--s_size];
    command[c_size++] = 2;
  }
  for (int i = 0; i < n - 1; ++i) {
    if (n_train[i] > n_train[i + 1]) {
      printf("0\n");
      return 0;
    }
  }
  for (int i = 0; i < c_size; ++i) {
    printf("%d 1\n", command[i]);
  }
}