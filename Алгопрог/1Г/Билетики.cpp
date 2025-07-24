#include "stdio.h"
#include "strings.h"
int main(int argc, char **argv) {
  int arr[50001];
  bzero(arr, sizeof(int) * 50001);
  int n, k;
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &arr[i]);
  }
  int err = 0;
  for (int i = 1; i <= n; ++i) {
    if (i - 1 + k >= n)
      break;
    if (arr[i - 1] != arr[i - 1 + k]) {
      if (!err)
        err = i;
      else
        err = -1;
    }
  }
  if (err == -1) {
    printf("FAIL\n");
  } else {
    printf("OK\n%d", err);
  }
  return 0;
}