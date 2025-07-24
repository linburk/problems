#include <stdio.h>
#include <stdlib.h>
#define min(a, b) (a < b ? a : b)
#define MAX_V_SIZE 20000
#define MAX_E_SIZE 200000
struct edge {
  int to;
  int index;
  struct edge *prev;
};

struct edge *graph[MAX_V_SIZE];
int is_bridge[MAX_E_SIZE];
int depth[MAX_V_SIZE];
int min_depth[MAX_V_SIZE];
int component[MAX_V_SIZE];
int count = 0;

void dfs(int v, int p, int p_edge) {
  min_depth[v] = depth[v] = depth[p] + 1;
  for (struct edge *i = graph[v]; i != NULL; i = i->prev) {
    int to = i->to;
    if (to == p && i->index == p_edge)
      continue;
    if (to == p && i->index != p_edge) {
      if (p_edge != -1)
        is_bridge[p_edge] = -1;
      is_bridge[i->index] = -1;
      continue;
    }
    if (depth[to]) {
      min_depth[v] = min(min_depth[v], depth[to]);
    } else {
      dfs(to, v, i->index);
      min_depth[v] = min(min_depth[v], min_depth[to]);
      if (min_depth[to] > depth[v] && is_bridge[i->index] != -1)
        is_bridge[i->index] = 1;
    }
  }
}

void dfs2(int v, int c) {
  if (component[v])
    return;
  component[v] = c;
  for (struct edge *i = graph[v]; i != NULL; i = i->prev) {
    if (is_bridge[i->index] == 1)
      continue;
    dfs2(i->to, c);
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
      struct edge *nedge = (struct edge *)(calloc(1, sizeof(struct edge)));
      nedge->to = e;
      nedge->prev = graph[b];
      nedge->index = i;
      graph[b] = nedge;
    }
    {
      struct edge *nedge = (struct edge *)(calloc(1, sizeof(struct edge)));
      nedge->to = b;
      nedge->prev = graph[e];
      nedge->index = i;
      graph[e] = nedge;
    }
  }
  for (int v = 0; v < n; ++v) {
    dfs(v, v, -1);
  }
  for (int v = 0; v < n; ++v) {
    if (!component[v]) {
      ++count;
      dfs2(v, count);
    }
  }
  printf("%d\n", count);
  for (int v = 0; v < n; ++v) {
    printf("%d ", component[v]);
  }
}