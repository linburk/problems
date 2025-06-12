#include "algorithm"
#include "iostream"
#include "string"
#include "vector"

using std::vector, std::string, std::pair;

class GRAPH {
private:
  int const BINMAX = 18;
  vector<vector<int>> graph;
  vector<vector<int>> binup;
  vector<int> depth;

  void dfs(int v, int p) {
    depth[v] = depth[p] + 1;
    binup[v][0] = p;
    for (int i = 1; i < BINMAX; ++i) {
      binup[v][i] = binup[binup[v][i - 1]][i - 1];
    }
    for (auto to : graph[v]) {
      if (to != p)
        dfs(to, v);
    }
  }

public:
  GRAPH(int n) {
    graph.resize(n);
    binup.resize(n, vector<int>(BINMAX));
    depth.resize(n);
  }
  int get_lca(int a, int b) {
    if (depth[a] < depth[b])
      std::swap(a, b);
    for (int i = BINMAX - 1; i >= 0; --i) {
      if (depth[binup[a][i]] >= depth[b]) {
        a = binup[a][i];
      }
    }
    if (a == b)
      return a;
    for (int i = BINMAX - 1; i >= 0; --i) {
      if (binup[a][i] != binup[b][i]) {
        a = binup[a][i];
        b = binup[b][i];
      }
    }
    return binup[a][0];
  }
  vector<int> get_path(int a, int b) {
    vector<int> path_a, path_b{b};
    int lca = get_lca(a, b);
    while (a != lca) {
      path_a.push_back(a);
      a = binup[a][0];
    }
    while (b != lca) {
      b = binup[b][0];
      path_b.push_back(b);
    }
    std::reverse(path_b.begin(), path_b.end());
    path_a.insert(path_a.end(), std::make_move_iterator(path_b.begin()),
                  std::make_move_iterator(path_b.end()));
    return path_a;
  }
  void add_edge(int a, int b) {
    graph[a].push_back(b);
    graph[b].push_back(a);
  }
  void build(int v) {
    depth[v] = -1;
    return dfs(v, v);
  }
};

class GRAPH_2SAT final : public GRAPH {
private:
  vector<vector<int>> igraph;
  vector<vector<int>> rigraph;
  vector<char> symbols;

  vector<bool> used;
  vector<int> order;
  vector<int> member;
  string answer;

  int count_m = 0;
  bool IMPOSSIBLE = false;
  int n_, q_;

private:
  void topsort(int v) {
    used[v] = 1;
    for (auto to : igraph[v]) {
      if (!used[to])
        topsort(to);
    }
    order.push_back(v);
  }
  void set_member(int v) {
    member[v] = count_m;
    for (auto to : rigraph[v]) {
      if (!member[to]) {
        set_member(to);
      }
    }
  }
  void condensate() {
    for (int i = 0; i < 2 * (n_ + q_); ++i) {
      if (!used[i])
        topsort(i);
    }
    for (int i = 2 * (n_ + q_) - 1; i >= 0; --i) {
      if (!member[order[i]]) {
        ++count_m;
        set_member(order[i]);
      }
    }
  }
  bool get_answer() {
    condensate();
    for (int i = 0; i < (n_ + q_); ++i) {
      if (member[2 * i] == member[2 * i + 1]) {
        IMPOSSIBLE = true;
      }
    }
    for (int i = 0; i < (n_); ++i) {
      answer += (member[2 * i] < member[2 * i + 1] ? symbols[2 * i]
                                                   : symbols[2 * i + 1]);
    }
    return IMPOSSIBLE;
  }

public:
  GRAPH_2SAT(int n, int q) : GRAPH(n), n_(n), q_(q) {
    igraph.resize(2 * n + 2 * q);
    rigraph.resize(2 * n + 2 * q);
    symbols.resize(2 * n);
    used.resize(2 * n + 2 * q);
    member.resize(2 * n + 2 * q);
  }
  void set_condition(int x, int y, string const &s, string const &rs, int ind) {
    vector<int> path = get_path(x, y);
    bool CAN_REVERSET = true, CAN_STRAIGHTT = true;
    bool CAN_REVERSEF = true, CAN_STRAIGHTF = true;
    for (int j = 0; auto i : path) {
      if (symbols[2 * i] && symbols[2 * i] != s[j]) {
        CAN_STRAIGHTT = false;
      }
      if (symbols[2 * i + 1] && symbols[2 * i + 1] != s[j]) {
        CAN_STRAIGHTF = false;
      }
      if (symbols[2 * i] && symbols[2 * i] != rs[j]) {
        CAN_REVERSET = false;
      }
      if (symbols[2 * i + 1] && symbols[2 * i + 1] != rs[j++]) {
        CAN_REVERSEF = false;
      }
    }
    if (!CAN_REVERSET && !CAN_REVERSEF && !CAN_STRAIGHTT && !CAN_STRAIGHTF)
      IMPOSSIBLE = true;
    if (CAN_REVERSET && !CAN_STRAIGHTT) {
      for (int j = 0; auto i : path) {
        symbols[2 * i] = rs[j++];
        rigraph[2 * i].push_back(2 * n_ + 2 * ind + 1);
        igraph[2 * n_ + 2 * ind + 1].push_back(2 * i);
      }
    }
    if (CAN_REVERSEF) {
      for (int j = 0; auto i : path) {
        symbols[2 * i + 1] = rs[j++];
        rigraph[2 * i + 1].push_back(2 * n_ + 2 * ind + 1);
        igraph[2 * n_ + 2 * ind + 1].push_back(2 * i + 1);
      }
    }
    if (CAN_STRAIGHTT) {
      for (int j = 0; auto i : path) {
        symbols[2 * i] = s[j++];
        igraph[2 * i].push_back(2 * n_ + 2 * ind);
        rigraph[2 * n_ + 2 * ind].push_back(2 * i);
      }
    }
    if (CAN_STRAIGHTF && !CAN_REVERSEF) {
      for (int j = 0; auto i : path) {
        symbols[2 * i + 1] = s[j++];
        rigraph[2 * i + 1].push_back(2 * n_ + 2 * ind);
        igraph[2 * n_ + 2 * ind].push_back(2 * i + 1);
      }
    }
  }
  pair<bool, string> result() {
    bool can = get_answer();
    return {can, answer};
  }
};

int main(int argc, char **argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n, q;
  std::cin >> n >> q;
  GRAPH_2SAT gr(n, q);
  for (int i = 1; i < n; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    gr.add_edge(u, v);
  }
  gr.build(0);
  for (int i = 0; i < q; ++i) {
    int x, y;
    string s;
    std::cin >> x >> y >> s;
    --x, --y;
    string rs = s;
    std::reverse(rs.begin(), rs.end());
    gr.set_condition(x, y, s, rs, i);
  }
  pair<bool, string> ans = gr.result();
  if (ans.first) {
    std::cout << "NO\n";
  } else {
    std::cout << "YES\n" << ans.second;
  }
}