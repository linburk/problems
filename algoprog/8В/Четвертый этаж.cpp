#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 200002
#define min(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
  int pos;
} node;

void build(int l, int r, int n, node *tree) {
  if (l == r - 1)
    return (void)(tree[n].pos = l);
  int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
  build(l, m, ls, tree);
  build(m, r, rs, tree);
  tree[n].pos = min(tree[ls].pos, tree[rs].pos);
}

void update(int i, int l, int r, int n, node *tree) {
  if (l > i || r <= i)
    return;
  if (l == r - 1)
    return (void)(tree[n].pos = (tree[n].pos == INT_MAX ? i : INT_MAX));
  int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
  update(i, l, m, ls, tree);
  update(i, m, r, rs, tree);
  tree[n].pos = min(tree[ls].pos, tree[rs].pos);
}

int get(int ql, int qr, int l, int r, int n, node *tree) {
  if (l >= qr || r <= ql)
    return INT_MAX;
  if (ql <= l && r <= qr)
    return tree[n].pos;
  int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
  return min(get(ql, qr, l, m, ls, tree), get(ql, qr, m, r, rs, tree));
}

int main(int argc, char *argv[]) {
  freopen("/users/dmitrii/documents/code/code/input.txt", "r", stdin);
  freopen("/users/dmitrii/documents/code/code/output.txt", "w", stdout);
  int n;
  scanf("%d", &n);
  node tree[4 * MAXSIZE];
  build(0, MAXSIZE, 1, tree);
  for (int i = 0; i < n; i++) {
    int a;
    scanf("%d", &a);
    if (a < 0) {
      update(-a, 0, MAXSIZE, 1, tree);
    } else {
      int pos = get(a, MAXSIZE, 0, MAXSIZE, 1, tree);
      update(pos, 0, MAXSIZE, 1, tree);
      printf("%d\n", pos);
    }
  }
}