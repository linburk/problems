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
  const i32 mod = 1e9 + 7;
  const i64 INF = 1e18;
  vi64 dist;
  vvpi64 gr;
  vi32 minlen, maxlen;
  vi64 count;
  vb used;
  void solve() {
    i32 n, m;
    cin >> n >> m;
    gr.resize(n);
    used.resize(n);
    dist.resize(n, INF);
    minlen.resize(n, INF);
    maxlen.resize(n, -INF);
    count.resize(n, 0);
    dist[0] = 0;
    count[0] = 1;
    minlen[0] = 0;
    maxlen[0] = 0;
    for (i32 i = 0; i < m; ++i) {
      i32 a, b, w;
      cin >> a >> b >> w;
      gr[a - 1].push_back({b - 1, w});
    }
    std::set<pi64> q;
    q.insert({0, 0});
    for (; q.size();) {
      auto [d, v] = *q.begin();
      q.erase(q.begin());
      for (auto [to, w] : gr[v]) {
        if (dist[to] > dist[v] + w) {
          q.erase({dist[to], to});
          count[to] = count[v];
          minlen[to] = minlen[v] + 1;
          maxlen[to] = maxlen[v] + 1;
          dist[to] = dist[v] + w;
          q.insert({dist[to], to});
        } else if (dist[to] == dist[v] + w) {
          count[to] = (count[to] + count[v]) % mod;
          minlen[to] = std::min(minlen[to], minlen[v] + 1);
          maxlen[to] = std::max(maxlen[to], maxlen[v] + 1);
        }
      }
    }
    cout << dist[n - 1] << ' ' << count[n - 1] << ' ' << minlen[n - 1] << ' '
         << maxlen[n - 1] << std::endl;
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
