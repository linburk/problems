#include <stdio.h>

char t[51][51];
char r[51][51];
char prefcol[51];

int main(int argc, char **argv) {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      r[i][j] = '2';
    }
  }
  int all_c = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%s", t[i]);
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (t[i][j] == 'C') {
        ++prefcol[i];
        ++all_c;
      }
    }
  }
  int count = 0;
  for (int i = 0; i < n; ++i) {
    if (prefcol[i] + count < all_c / 2) {
      count += prefcol[i];
      for (int j = 0; j < n; ++j) {
        r[i][j] = '1';
      }
    } else {
      for (int j = 0; j < n && count < all_c / 2; ++j) {
        for (int k = i; k < n && count < all_c / 2; ++k) {
          if (t[k][j] == 'C') {
            ++count;
          }
          r[k][j] = '1';
        }
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    printf("%s\n", r[i]);
  }
}