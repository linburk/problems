#include <stdio.h>
#include <stdlib.h>

#define MAX_V_SIZE 200000

typedef struct edge_t {
  int to;
  struct edge_t *prev;
} edge;

edge *graph[MAX_V_SIZE];
edge *rgraph[MAX_V_SIZE];
int used[MAX_V_SIZE];
int order[MAX_V_SIZE];
int member[MAX_V_SIZE];
int comp_sz = 0;
int order_sz = 0;

void dfs(int v) {
  if (used[v])
    return;
  used[v] = 1;
  for (edge *i = graph[v]; i != NULL; i = i->prev) {
    dfs(i->to);
  }
  order[order_sz++] = v;
}

void dfs2(int v) {
  if (member[v])
    return;
  member[v] = comp_sz;
  for (edge *i = rgraph[v]; i != NULL; i = i->prev) {
    dfs2(i->to);
  }
}

int main(int argc, char **argv) {
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int b, e;
    scanf("%d %d", &b, &e);
    --b, --e;
    edge *new_e = (edge *)(calloc(1, sizeof(edge)));
    new_e->to = e;
    new_e->prev = graph[b];
    graph[b] = new_e;

    new_e = (edge *)(calloc(1, sizeof(edge)));
    new_e->to = b;
    new_e->prev = rgraph[e];
    rgraph[e] = new_e;
  }
  for (int i = 0; i < n; ++i) {
    dfs(i);
  }
  for (int i = n - 1; i >= 0; --i) {
    if (!member[order[i]]) {
      ++comp_sz;
      dfs2(order[i]);
    }
  }
  printf("%d\n", comp_sz);
  for (int i = 0; i < n; ++i) {
    printf("%d ", member[i]);
  }
}