#include <bits/stdc++.h>
#include <climits>

namespace /* clang-format off */ {
#define all(cont) cont.begin(), cont.end()
namespace /* aliases */ {
using i8 = std::int8_t; using i16 = std::int16_t; using i32 = std::int32_t; using i64 = std::int64_t;
using u8 = std::uint8_t; using u16 = std::uint16_t; using u32 = std::uint32_t; using u64 = std::uint64_t; using f64 = long double; using f32 = float;
using pi32 = std::pair<i32, i32>; using vpi32 = std::vector<pi32>; using vvpi32 = std::vector<vpi32>; using pi64 = std::pair<i64, i64>;  using vpi64 = std::vector<pi64>; using vvpi64 = std::vector<vpi64>;
using vi32 = std::vector<i32>; using vvi32 = std::vector<vi32>; using vi64 = std::vector<i64>; using vvi64 = std::vector<vi64>;
using vb = std::vector<bool>; using vvb = std::vector<vb>; using vc = std::vector<char>; using vvc = std::vector<vc>;
using si32 = std::set<i32>; using spi32 = std::set<pi32>; using si64 = std::set<i64>; using spi64 = std::set<pi64>;
using mpi32 = std::map<i32, i32>; using umpi32 = std::unordered_map<i32, i32>; using mpi64 = std::map<i64, i64>;  using umpi64 = std::unordered_map<i64, i64>;
}
namespace /* in/out op. overloadings */ {
template <typename T, typename V> std::istream &operator>>(std::istream &is, std::pair<T, V> &p) { is >> p.first >> p.second; return is; }
template <typename T> std::istream &operator>>(std::istream &is, std::vector<T> &cont) { for (auto &i : cont) { is >> i; } return is; }
template <typename T, typename V, char SEP1 = ' ', char SEP2 = '\n'> std::ostream &operator<<(std::ostream &os, std::pair<T, V> const &p) { os << p.first << SEP1 << p.second << SEP2; return os; }
template <typename T, char SEP1 = ' ', char SEP2 = '\n'> std::ostream &operator<<(std::ostream &os, const std::vector<T> &cont) { for (const auto &i : cont) { os << i; if (SEP1) os << SEP1; } os << SEP2; return os; }
}
namespace /* functions */ {
#if __cplusplus >= 202002L
template <char SEP = ' '> void debug(auto&&...args) { ((std::cout << args << SEP), ...); std::cout << "\n"; }
#endif
template <typename T> void inline unique(std::vector<T> &cont) { cont.erase(std::unique(cont.begin(), cont.end()), cont.end()); }
std::mt19937_64 randu64(std::chrono::steady_clock().now().time_since_epoch().count());
}
using std::vector, std::string, std::pair, std::cin, std::cout;
} /* clang-format on */

#define REDIRECT 1 && __APPLE__
#define PRECALCULATE 0
#define MULTITEST 0

struct {
  i32 n, m;
  vvpi32 gr;
  vi32 depth;
  vi32 min_depth;
  vi32 is_bridge;
  vi32 comp;
  i32 comp_sz = 0;
  std::stack<i32> st;
  void dfs(i32 v, i32 p, i32 p_edge) {
    min_depth[v] = depth[v] = depth[p] + 1;
    st.push(v);
    for (auto [to, ind] : gr[v]) {
      if (ind == p_edge) {
        continue;
      }
      if (to == p && ind != p_edge) {
        is_bridge[ind] = is_bridge[p_edge] = -1;
        continue;
      }
      if (depth[to]) {
        min_depth[v] = std::min(min_depth[v], depth[to]);
      } else {
        dfs(to, v, ind);
        min_depth[v] = std::min(min_depth[v], min_depth[to]);
        if (min_depth[to] > depth[v] && is_bridge[ind] != -1) {
          is_bridge[ind] = 1;
          for (++comp_sz; st.size() && st.top() != to; st.pop())
            comp[st.top()] = comp_sz;
          comp[st.top()] = comp_sz;
          st.pop();
        }
      }
    }
  }
  vvi32 cgr;
  void solve() {
    cin >> n >> m;
    comp.resize(n);
    gr.resize(n);
    depth.resize(n);
    min_depth.resize(n);
    is_bridge.resize(m);
    for (i32 i = 0; i < m; ++i) {
      i32 a, b;
      cin >> a >> b;
      --a, b--;
      if (a == b)
        continue;
      gr[a].push_back({b, i});
      gr[b].push_back({a, i});
    }
    for (i32 i = 0; i < n; ++i) {
      if (depth[i] == 0) {
        ++comp_sz;
        dfs(i, i, -1);
        for (++comp_sz; st.size(); st.pop())
          comp[st.top()] = comp_sz;
      }
    }
    mpi32 match;
    for (i32 i = 0; i < n; ++i) {
      if (!match.count(comp[i]))
        match[comp[i]] = static_cast<i32>(match.size());
      comp[i] = match[comp[i]];
    }
    comp_sz = static_cast<i32>(match.size());
    vi32 count(comp_sz);
    cgr.resize(comp_sz);
    for (i32 i = 0; i < n; ++i)
      ++count[comp[i]];
    const i32 mod = 1e9 + 7;
    for (i32 i = 0; i < n; ++i) {
      for (auto [to, ind] : gr[i]) {
        if (is_bridge[ind]) {
          cgr[comp[i]].push_back(comp[to]);
        }
      }
    }
    i64 r = 1;
    i32 c = 0;
    for (i32 i = 0; i < comp_sz; ++i) {
      if (cgr[i].size() <= 1) {
        r = r * count[i] % mod;
        ++c;
      }
    }
    cout << c << '\n' << r;
  }
} solution;

i32 main(i32 argc, char *argv[], char *envp[]) /* clang-format off */ {
  std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false); setlocale(LC_ALL, "Russian");
#if REDIRECT
  char const *FINPATH = std::getenv("FINPATH"), *FOUTPATH = std::getenv("FOUTPATH");
  std::freopen(FINPATH, "r", stdin); std::freopen(FOUTPATH, "w", stdout);
#endif
#if PRECALCULATE
  solution.precalc();
#endif
#if MULTITEST
  i32 t; std::cin >> t; for (i32 i = 0; i < t; i++)
#endif
  solution.solve();
  return 0;
} /* clang-format on */
