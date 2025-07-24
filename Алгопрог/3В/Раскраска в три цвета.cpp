#include <bits/stdc++.h>
#include <climits>
using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<vvi> vvvi;
typedef vector<vvl> vvvl;

#define all(cont) cont.begin(), cont.end()
#define funique(cont) cont.erase(unique(all(cont)), cont.end())

namespace tools {
// mt19937_64 rng(chrono::steady_clock().now().time_since_epoch().count());
template <typename T>
std::istream &operator>>(std::istream &is, std::vector<T> &array) {
  for (auto &i : array) {
    is >> i;
  }
  return is;
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &array) {
  for (const auto &i : array) {
    os << i << " ";
  }
  //        os << "\n";
  return os;
}
template <typename T, typename V>
std::istream &operator>>(std::istream &is, std::pair<T, V> &p) {
  is >> p.first >> p.second;
  return is;
}
} // namespace tools

using namespace tools;
// GLOBAL VARS START
int n, m;
vvi gr;
vvi imp_gr;
vvi imp_gr_rev;
vi colors;
// GLOBAL VARS END
// IMPLICATION BUILD START
void build_implication() {
  imp_gr.resize(2 * n);
  imp_gr_rev.resize(2 * n);
  for (int v = 0; v < n; v++) { // even - true, odd - false
    for (auto to : gr[v]) {
      if (colors[v] == 1) {
        if (colors[to] == 1) {
          imp_gr[2 * v].push_back(2 * to + 1);
          imp_gr[2 * v + 1].push_back(2 * to);

          imp_gr_rev[2 * to + 1].push_back(2 * v);
          imp_gr_rev[2 * to].push_back(2 * v + 1);
        }
        if (colors[to] == 2) {
          imp_gr[2 * v].push_back(2 * to + 1);

          imp_gr_rev[2 * to + 1].push_back(2 * v);
        }
        if (colors[to] == 3) {
          imp_gr[2 * v + 1].push_back(2 * to + 1);

          imp_gr_rev[2 * to + 1].push_back(2 * v + 1);
        }
      }
      if (colors[v] == 2) {
        if (colors[to] == 1) {
          imp_gr[2 * v].push_back(2 * to + 1);

          imp_gr_rev[2 * to + 1].push_back(2 * v);
        }
        if (colors[to] == 2) {
          imp_gr[2 * v].push_back(2 * to + 1);
          imp_gr[2 * v + 1].push_back(2 * to);

          imp_gr_rev[2 * to + 1].push_back(2 * v);
          imp_gr_rev[2 * to].push_back(2 * v + 1);
        }
        if (colors[to] == 3) {
          imp_gr[2 * v].push_back(2 * to);

          imp_gr_rev[2 * to].push_back(2 * v);
        }
      }
      if (colors[v] == 3) {
        if (colors[to] == 1) {
          imp_gr[2 * v].push_back(2 * to);

          imp_gr_rev[2 * to].push_back(2 * v);
        }
        if (colors[to] == 2) {
          imp_gr[2 * v + 1].push_back(2 * to);

          imp_gr_rev[2 * to].push_back(2 * v + 1);
        }
        if (colors[to] == 3) {
          imp_gr[2 * v].push_back(2 * to + 1);
          imp_gr[2 * v + 1].push_back(2 * to);

          imp_gr_rev[2 * to + 1].push_back(2 * v);
          imp_gr_rev[2 * to].push_back(2 * v + 1);
        }
      }
    }
  }
}
// IMPLICATION BUILD END
// INPUT START
void input() {
  cin >> n >> m;
  gr.resize(n);
  colors.resize(n);
  for (int i = 0; i < n; i++) {
    char c;
    cin >> c;
    if (c == 'R') {
      colors[i] = 1;
    }
    if (c == 'G') {
      colors[i] = 2;
    }
    if (c == 'B') {
      colors[i] = 3;
    }
  }
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    gr[a - 1].push_back(b - 1);
    gr[b - 1].push_back(a - 1);
  }
}
// INPUT END
// CONDENSATION START
vi order;
vb used;
vi member;
void topSort(int v) {
  if (used[v])
    return;
  used[v] = 1;
  for (auto to : imp_gr[v])
    topSort(to);
  order.push_back(v);
}
void makeOrder() {
  used.assign(2 * n, 0);
  for (int v = 0; v < 2 * n; v++) {
    if (!used[v]) {
      topSort(v);
    }
  }
}
void dfs(int v, int part) {
  if (member[v])
    return;
  member[v] = part;
  for (auto to : imp_gr_rev[v]) {
    dfs(to, part);
  }
}
void condensate() {
  member.assign(2 * n, 0);
  makeOrder();
  int count_clan = 1;
  for (int v = 2 * n - 1; v >= 0; v--) {
    if (!member[order[v]]) {
      dfs(order[v], count_clan++);
    }
  }
}
// CONDENSTATION END
// RESULT START
void checkMember() {
  for (int v = 0; v < n; v++) {
    if (member[2 * v] == member[2 * v + 1]) {
      cout << "Impossible";
      exit(0);
    }
  }
}
void buildAnswer() {
  for (int v = 0; v < n; v++) {
    int res = (member[2 * v] > member[2 * v + 1] ? 1 : 0);
    if (colors[v] == 1) {
      cout << (res ? 'B' : 'G');
    }
    if (colors[v] == 2) {
      cout << (res ? 'B' : 'R');
    }
    if (colors[v] == 3) {
      cout << (res ? 'G' : 'A');
    }
  }
}
// RESULT END
void solve() {
  input();
  build_implication();
  condensate();
  checkMember();
  buildAnswer();
}

int32_t main() {
  setlocale(LC_ALL, "Russian");
#ifdef __APPLE__
  std::freopen("/Users/dmitrii/Documents/Code/Code/input.txt", "r", stdin);
  std::freopen("/Users/dmitrii/Documents/Code/Code/output.txt", "w", stdout);
#endif
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);
  //    int t; cin >> t; for (; t; t--)
  solve();
  return 0;
}