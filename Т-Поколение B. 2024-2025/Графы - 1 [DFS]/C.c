#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#define min(a, b) (a < b ? a : b)
#define MAX_V_SIZE 100000

struct edge_t {
  int to;
  int weight;
  struct edge_t *prev;
};

typedef struct edge_t edge;

edge *graph[MAX_V_SIZE];
int dist[MAX_V_SIZE];
int order[MAX_V_SIZE];
int order_size = 0;

void dfs_sort(int v) {
  dist[v] = INT_MAX;
  for (edge *i = graph[v]; i != NULL; i = i->prev) {
    if (!dist[i->to])
      dfs_sort(i->to);
  }
  order[order_size++] = v;
}

int main(int argc, char **argv) {
  int n, m, s, t;
  scanf("%d %d %d %d", &n, &m, &s, &t);
  --s, --t;
  for (int i = 0; i < m; ++i) {
    int b, e, w;
    scanf("%d %d %d", &b, &e, &w);
    --b, --e;
    edge *new_e = (edge *)(calloc(1, sizeof(edge)));
    new_e->to = e;
    new_e->weight = w;
    new_e->prev = graph[b];
    graph[b] = new_e;
  }
  for (int i = 0; i < n; ++i) {
    if (dist[i] != INT_MAX)
      dfs_sort(i);
  }
  dist[s] = 0;
  for (int i = n - 1; i >= 0; --i) {
    int v = order[i];
    if (dist[v] != INT_MAX) {
      for (edge *e = graph[v]; e != NULL; e = e->prev) {
        dist[e->to] = min(dist[e->to], dist[v] + e->weight);
      }
    }
  }
  if (dist[t] == INT_MAX)
    printf("Unreachable\n");
  else
    printf("%d\n", dist[t]);
}