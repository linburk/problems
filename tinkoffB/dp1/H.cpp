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
std::mt19937_64 ru64(std::chrono::steady_clock().now().time_since_epoch().count());
}
using std::vector, std::string, std::pair, std::cin, std::cout;
} /* clang-format on */

#define REDIRECT 1 && __APPLE__
#define PRECALCULATE 0
#define MULTITEST 0

struct {
  vvi32 gr;
  vi32 max_depth;
  i32 r = 0;
  void dfs(i32 v, i32 p, i32 d) {
    max_depth[v] = d;
    for (auto to : gr[v]) {
      if (to != p) {
        dfs(to, v, d + 1);
        max_depth[v] = std::max(max_depth[v], max_depth[to]);
      }
    }
  }
  void max_p(pi32 &a, pi32 const &b) {
    if (b.first > a.first) {
      a.second = a.first;
      a.first = b.first;
    } else {
      a.second = std::max(a.second, b.first);
    }
    a.second = std::max(a.second, b.second);
  }
  void dfs2(i32 v, i32 p, i32 up_val, i32 up_max, i32 d) {
    vpi32 suf_max(gr[v].size());
    pi32 pref_max;
    for (i32 i = static_cast<i32>(gr[v].size()) - 1; i > 0; --i) {
      max_p(suf_max[i - 1], suf_max[i]);
      if (gr[v][i] != p) max_p(suf_max[i - 1], {max_depth[gr[v][i]], 0});
    }
    for (i32 i = 0; i < gr[v].size(); ++i) {
      i32 to = gr[v][i];
      if (to != p) {
        i32 to_up_val = std::max({
          up_val + 2,
          2 * (up_max + std::max(suf_max[i].first, pref_max.first) - d) + 2,
          2 * (suf_max[i].first + suf_max[i].second - 2 * d) + 2,
          2 * (pref_max.first + pref_max.second - 2 * d) + 2,
          2 * (suf_max[i].first + pref_max.first - 2 * d) + 2
        });
        i32 to_up_max = std::max({
          up_max,
          suf_max[i].first - d,
          pref_max.first - d
        }) + 1;
        dfs2(to, v, to_up_val, to_up_max, d + 1);
        max_p(pref_max, {max_depth[gr[v][i]], 0});
      }
    }
    r = std::max({r,
      up_val,
      2 * (up_max + pref_max.first - d),
      2 * (pref_max.first + pref_max.second - 2 * d)
    });
  }
  void solve() {
    i32 n;
    cin >> n;
    gr.resize(n);
    max_depth.resize(n);
    for (i32 i = 0; i < n-1; ++i) {
      i32 a, b;
      cin >> a >> b;
      gr[a-1].push_back(b-1);
      gr[b-1].push_back(a-1);
    }
    dfs(0, 0, 0);
    dfs2(0, 0, 0, 0, 0);
    cout << r;
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
