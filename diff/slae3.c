#include <stdio.h>

int count_d3(int det[3][4]) {
  return det[0][0] * det[1][1] * det[2][2] + det[0][1] * det[1][2] * det[2][0] +
         det[1][0] * det[2][1] * det[0][2] - det[0][2] * det[1][1] * det[2][0] -
         det[0][0] * det[2][1] * det[1][2] - det[0][1] * det[1][0] * det[2][2];
}

int main(int argc, char **argv) {
  int matrix[3][4];
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      scanf("%d", &matrix[i][j]);
    }
  }
  int d[3];
  int dm = count_d3(matrix);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      int t = matrix[j][3];
      matrix[j][3] = matrix[j][i];
      matrix[j][i] = t;
    }
    d[i] = count_d3(matrix);
    for (int j = 0; j < 3; ++j) {
      int t = matrix[j][3];
      matrix[j][3] = matrix[j][i];
      matrix[j][i] = t;
    }
  }
  if (dm == 0) {
    printf("\nno solution\n");
    return 0;
  }
  printf("\nd: %d\ndx: %d\ndy: %d\ndz: %d\n", dm, d[0], d[1], d[2]);
  printf("\nx: %Lf\ny: %Lf\nz: %Lf\n", (long double)d[0] / dm,
         (long double)d[1] / dm, (long double)d[2] / dm);
}
