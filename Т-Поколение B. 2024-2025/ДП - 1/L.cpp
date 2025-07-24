#include <bits/stdc++.h>
#include <climits>

#define LOCAL 1 && __APPLE__
#define REDIRECT 1 && __APPLE__
#define PRECALCULATE 0
#define MULTITEST 0

namespace /* clang-format off */ {
#define all(cont) cont.begin(), cont.end()
namespace /* aliases */ {
using i8 = std::int8_t; using i16 = std::int16_t; using i32 = std::int32_t; using i64 = std::int64_t;
using u8 = std::uint8_t; using u16 = std::uint16_t; using u32 = std::uint32_t; using u64 = std::uint64_t; using f64 = long double; using f32 = float;
using pi32 = std::pair<i32, i32>; using vpi32 = std::vector<pi32>; using vvpi32 = std::vector<vpi32>; using pi64 = std::pair<i64, i64>;  using vpi64 = std::vector<pi64>; using vvpi64 = std::vector<vpi64>;
using vi8 = std::vector<i8>; using vvi8 = std::vector<vi8>; using vi32 = std::vector<i32>; using vvi32 = std::vector<vi32>; using vi64 = std::vector<i64>; using vvi64 = std::vector<vi64>;
using vb = std::vector<bool>; using vvb = std::vector<vb>; using vc = std::vector<char>; using vvc = std::vector<vc>;
using si32 = std::set<i32>; using spi32 = std::set<pi32>; using si64 = std::set<i64>; using spi64 = std::set<pi64>;
using mpi32 = std::map<i32, i32>; using umpi32 = std::unordered_map<i32, i32>; using mpi64 = std::map<i64, i64>;  using umpi64 = std::unordered_map<i64, i64>;
}
namespace /* in/out op. overloadings */ {
template <typename T, typename V> std::istream &operator>>(std::istream &is, std::pair<T, V> &p) { is >> p.first >> p.second; return is; }
template <typename T> std::istream &operator>>(std::istream &is, std::vector<T> &cont) { for (auto &i : cont) { is >> i; } return is; }
template <typename T, typename V, char SEP = ' ', char ENDL = '\n'> std::ostream &operator<<(std::ostream &os, std::pair<T, V> const &p) {
#if LOCAL
  os << "<" << p.first << ", " << p.second << ">"; return os;
#else
  os << p.first << SEP << p.second << ENDL; return os;
#endif
}
template <typename T, char SEP = ' ', char ENDL = '\n'> std::ostream &operator<<(std::ostream &os, const std::vector<T> &cont) {
#if LOCAL
  std::cout << "[";
  for (auto b = cont.begin(), e = cont.end(); b != e; ++b) os << *b << (b + 1 == e ? "" : ", "); std::cout << "]"; return os;
#else
  for (auto b = cont.begin(), e = cont.end(); b != e; ++b) os << *b << (b + 1 == e ? ENDL : SEP); return os;
#endif
}
}
namespace /* functions */ {
#if __cplusplus >= 202002L
void print(auto &&...args) { ((std::cout << args), ...); }
void input(auto &&...args) { ((std::cin >> args), ...); }
#endif
template <typename T> void inline unique(std::vector<T> &cont) { cont.erase(std::unique(cont.begin(), cont.end()), cont.end()); }
std::mt19937_64 ru64(std::chrono::steady_clock().now().time_since_epoch().count());
}
using std::vector, std::string, std::pair, std::cin, std::cout;
} /* clang-format on */

struct {
  i32 n;
  vvpi64 gr;
  vi64 sumk, sumt;
  vvi32 order;
  vi64 count;
  struct triple {
    i64 sum_t, edge, vert;
  };
  void dfs(i32 v, i32 p) {
    for (auto [to, w] : gr[v])
      if (to != p)
        dfs(to, v);
    for (auto [to, w] : gr[v])
      if (to != p)
        sumk[v] += sumk[to];
    vector<triple> times;
    for (auto [to, w] : gr[v])
      if (to != p)
        times.push_back({sumt[to] + 2 * w, w, to});
    std::sort(all(times), [this](triple const &a, triple const &b) {
      return static_cast<f64>(sumk[a.vert]) / a.sum_t >
             static_cast<f64>(sumk[b.vert]) / b.sum_t;
    });
    for (auto [tm, w, i] : times) {
      count[v] += count[i] + sumk[i] * (sumt[v] + w);
      sumt[v] += tm;
      order[v].push_back(i);
    }
  }
  vpi32 ans;
  void rest(i32 v) {
    for (auto to : order[v]) {
      if (to == v + n) {
        ans.push_back({1, v + 1});
        continue;
      } else {
        ans.push_back({0, to + 1});
        rest(to);
        ans.push_back({0, v + 1});
      }
    }
  }
  void solve() {
    cin >> n;
    gr.resize(2 * n);
    order.resize(2 * n);
    sumk.resize(2 * n);
    sumt.resize(2 * n);
    count.resize(2 * n);
    for (i32 i = n; i < 2 * n; ++i) {
      cin >> sumt[i];
    }
    for (i32 i = n; i < 2 * n; ++i) {
      cin >> sumk[i];
      count[i] = sumt[i] * sumk[i];
    }
    for (i32 i = 0; i < n - 1; ++i) {
      i32 a, b, w;
      cin >> a >> b >> w;
      gr[a - 1].push_back({b - 1, w});
      gr[b - 1].push_back({a - 1, w});
    }
    for (i32 i = 0; i < n; ++i) {
      gr[i].push_back({n + i, 0});
    }
    dfs(0, 0);
    rest(0);
    cout << count[0] << '\n';
    for (auto [f, s] : ans) {
      cout << (f ? "P " : "M ") << s << '\n';
    }
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
