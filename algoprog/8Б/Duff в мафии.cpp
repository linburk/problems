#include "algorithm"
#include "iostream"
#include "map"
#include "vector"

using std::vector, std::map, std::pair;

namespace {
struct edge {
  int u, v, c, t;
};
struct g_edge {
  int to, c, t, i;
};
vector<edge> edges;
vector<vector<g_edge>> graph;
vector<vector<int>> igraph, rigraph;
vector<int> order;
vector<int> member;
vector<bool> match;
vector<bool> used;
int n, m;
int count;

void topsort(int v) {
  used[v] = 1;
  for (auto to : igraph[v])
    if (!used[to])
      topsort(to);
  order.push_back(v);
}

void set_member(int v) {
  member[v] = count;
  for (auto to : rigraph[v])
    if (!member[to])
      set_member(to);
}

bool check(int x) {
  bool sat = 1;
  {
    for (int v = 0; v < n; ++v) {
      map<int, int> connected;
      for (auto [to, c, t, i] : graph[v]) {
        if (t > x)
          ++connected[c];
        if (connected[c] > 1)
          return 0;
      }
    }
  }
  {
    igraph.assign(2 * m, vector<int>{});
    rigraph.assign(2 * m, vector<int>{});
    member.assign(2 * m, 0);
    used.assign(2 * m, 0);
    count = 0;
  }
  for (int v = 0; v < n; ++v) {
    map<int, vector<int>> same;
    for (auto [to, c, t, i] : graph[v]) {
      same[c].push_back(i);
    }
    for (int i = 0; i < graph[v].size(); ++i) {
      for (int j = 0; j < graph[v].size(); ++j) {
        if (i != j) {
          igraph[2 * graph[v][i].i].push_back(2 * graph[v][j].i + 1);
          rigraph[2 * graph[v][j].i + 1].push_back(2 * graph[v][i].i);
        }
      }
    }
    for (auto [c, a] : same) {
      for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a.size(); ++j) {
          if (i != j) {
            igraph[2 * a[i] + 1].push_back(2 * a[j]);
            rigraph[2 * a[j]].push_back(2 * a[i] + 1);
          }
        }
      }
    }
  }
  {
    for (int v = 0; v < 2 * n; ++v) {
      if (!used[v])
        topsort(v);
    }
    for (int v = 2 * n - 1; v >= 0; --v) {
      if (!member[v]) {
        ++count;
        set_member(v);
      }
    }
    for (int v = 0; v < n; ++v) {
      if (member[2 * v] == member[2 * v + 1]) {
        sat = 0;
      }
    }
    for (int v = 0; v < n; ++v) {
      match[v] = member[2 * v] > member[2 * v + 1];
    }
  }
  {
    igraph.clear();
    rigraph.clear();
    member.clear();
    used.clear();
    order.clear();
    count = 0;
  }
  return sat;
}

} // namespace

int main(int argc, char **argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#ifdef __APPLE__
  std::freopen("/Users/dmitrii/Documents/Code/Code/input.txt", "r", stdin);
  std::freopen("/Users/dmitrii/Documents/Code/Code/output.txt", "w", stdout);
#endif
  std::cin >> n >> m;
  graph.resize(n);
  match.resize(n);
  edges.resize(n);
  for (int i = 0; i < m; ++i) {
    int u, v, c, t;
    std::cin >> u >> v >> c >> t;
    --u, --v;
    graph[u].push_back({v, c, t, i});
    graph[v].push_back({u, c, t, i});
    edges[i] = {u, v, c, t};
  }
  int l = -1, r = 1e9 + 1;
  while (r - l > 1) {
    int m = (l + r) >> 1;
    check(m) ? r = m : l = m;
  }
  bool ans = check(r);
  if (!ans) {
    std::cout << "No\n";
  } else {
    std::cout << "Yes\n";
    vector<int> roads;
    for (int i = 0; i < n; ++i) {
      if (match[i]) {
        roads.push_back(i + 1);
      }
    }
    std::cout << r << " " << roads.size() << "\n";
    for (auto i : roads)
      std::cout << i << " ";
  }
}
// log(t)*(~n*m^2*log(m))