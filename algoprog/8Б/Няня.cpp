#include <iostream>
#include <vector>

std::vector<std::pair<int, int>> edges;
std::vector<std::vector<int>> imp_graph;
std::vector<std::vector<int>> rev_imp_graph;
std::vector<char> used;
std::vector<int> order;
std::vector<int> member;

void topsort(int v) {
  used[v] = 1;
  for (auto to : imp_graph[v]) {
    if (!used[to]) {
      topsort(to);
    }
  }
  order.push_back(v);
}

void get_member(int v, int cnt) {
  member[v] = cnt;
  for (auto to : rev_imp_graph[v]) {
    if (member[to] == -1) {
      get_member(to, cnt);
    }
  }
}

bool check(int m) {
  // Ð´Ð° Ð½Ñ Ð´Ð°Ð¶Ðµ Ð½Ðµ Ð±Ð»Ð¸Ð·ÐºÐ¾
}

void solve() {
  int n, m;
  std::cin >> n >> m;
  order.clear();
  imp_graph.assign(2 * n, std::vector<int>{});
  rev_imp_graph.assign(2 * n, std::vector<int>{});
  edges.resize(m);
  for (int i = 0; i < m; i++) {
    int a, b;
    std::cin >> a >> b;
    a--, b--;
    edges[i] = {a, b};
    imp_graph[2 * a + 1].push_back(2 * b);
    imp_graph[2 * b + 1].push_back(2 * a);
    rev_imp_graph[2 * b].push_back(2 * a + 1);
    rev_imp_graph[2 * a].push_back(2 * b + 1);
  }
  int cnt = 0;
  used.assign(2 * n, 0);
  for (int i = 0; i < 2 * n; i++) {
    if (!used[i])
      topsort(i);
  }
  member.assign(2 * n, -1);
  for (int i = 2 * n - 1; i >= 0; i--) {
    if (member[order[i]] == -1)
      get_member(order[i], cnt++);
  }
  int l = 0, r = n + 1;
  while (r - l > 1) {
    int m = (l + r) >> 1;
    if (check(m)) {
      l = m;
    } else {
      r = m;
    }
  }
  std::cout << r << "\n";
}

int main(int argc, char **argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  imp_graph.reserve(200000);
  rev_imp_graph.reserve(200000);
  edges.reserve(200000);
  order.reserve(200000);
  used.reserve(200000);
  int t;
  std::cin >> t;
  for (int i = 0; i < t; i++) {
    solve();
  }
  return 0;
}