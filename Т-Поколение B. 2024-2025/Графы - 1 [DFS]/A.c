#include <stdio.h>
#include <stdlib.h>

#define min(a, b) (a < b ? a : b)
#define MAX_SIZE 20000

struct edge {
  int to;
  struct edge *prev;
};

struct edge *graph[MAX_SIZE];
int depth[MAX_SIZE];
int min_depth[MAX_SIZE];
int cut_vertex[MAX_SIZE];

void dfs(int v, int p) {
  min_depth[v] = depth[v] = depth[p] + 1;
  int c = 0;
  for (struct edge *i = graph[v]; i != NULL; i = i->prev) {
    int to = i->to;
    if (to == p)
      continue;
    if (depth[to]) {
      min_depth[v] = min(min_depth[v], depth[to]);
    } else {
      dfs(to, v);
      min_depth[v] = min(min_depth[v], min_depth[to]);
      if (min_depth[to] >= depth[v] && v != p)
        cut_vertex[v] = 1;
      ++c;
    }
  }
  if (v == p && c >= 2)
    cut_vertex[v] = 1;
}

int main(int argc, char **argv) {
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int b, e;
    scanf("%d %d", &b, &e);
    --b, --e;
    {
      struct edge *new_edge = (struct edge *)calloc(1, sizeof(struct edge));
      new_edge->to = e;
      if (graph[b] == NULL) {
        new_edge->prev = NULL;
      } else {
        new_edge->prev = graph[b];
      }
      graph[b] = new_edge;
    }
    {
      struct edge *new_edge = (struct edge *)calloc(1, sizeof(struct edge));
      new_edge->to = b;
      if (graph[e] == NULL) {
        new_edge->prev = NULL;
      } else {
        new_edge->prev = graph[e];
      }
      graph[e] = new_edge;
    }
  }
  for (int i = 0; i < n; ++i)
    if (!depth[i])
      dfs(i, i);
  int res = 0;
  for (int i = 0; i < n; ++i) {
    if (cut_vertex[i])
      ++res;
  }
  printf("%d\n", res);
  for (int i = 0; i < n; ++i) {
    if (cut_vertex[i])
      printf("%d ", i + 1);
  }
}