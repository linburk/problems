#include <stdio.h>
#include <stdlib.h>

#define MAX_V_SIZE 3000

typedef struct edge_t {
  int to;
  struct edge_t *prev;
} edge;

edge *graph[MAX_V_SIZE];
edge *rgraph[MAX_V_SIZE];
int member[MAX_V_SIZE];
int used[MAX_V_SIZE];
int order[MAX_V_SIZE];
int comp_out[MAX_V_SIZE];
int order_sz = 0;
int comp_sz = 0;

void dfs(int v) {
  if (used[v])
    return;
  used[v] = 1;
  for (edge *e = graph[v]; e != NULL; e = e->prev)
    dfs(e->to);
  order[order_sz++] = v;
}

void dfs2(int v) {
  if (member[v])
    return;
  member[v] = comp_sz;
  for (edge *e = rgraph[v]; e != NULL; e = e->prev) {
    dfs2(e->to);
  }
}

int main(int argc, char **argv) {
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int b, e;
    scanf("%d %d", &b, &e);
    --b, --e;
    {
      edge *n_e = (edge *)(calloc(1, sizeof(edge)));
      n_e->to = e;
      n_e->prev = graph[b];
      graph[b] = n_e;
    }
    {
      edge *n_e = (edge *)(calloc(1, sizeof(edge)));
      n_e->to = b;
      n_e->prev = rgraph[e];
      rgraph[e] = n_e;
    }
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
  for (int i = 0; i < n; ++i) {
    for (edge *e = graph[i]; e != NULL; e = e->prev) {
      if (member[e->to] != member[i])
        ++comp_out[member[i]];
    }
  }
  int count_drain = 0;
  for (int i = 0; i < comp_sz; ++i) {
    if (comp_out[i] == 0)
      ++count_drain;
  }
  printf("%d\n", count_drain);
}