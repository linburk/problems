#include <bits/stdc++.h>
#include <climits>

#define LOCAL 1 && __APPLE__
#define REDIRECT 1 && __APPLE__
#define PRECALCULATE 0
#define MULTITEST 1

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
void print(auto&&...args) { ((std::cout << args), ...); }
void input(auto&&... args) { ((std::cin >> args), ...); }
#endif
template <typename T> void inline unique(std::vector<T> &cont) { cont.erase(std::unique(cont.begin(), cont.end()), cont.end()); }
std::mt19937_64 ru64(std::chrono::steady_clock().now().time_since_epoch().count());
}
using std::vector, std::string, std::pair, std::cin, std::cout;
} /* clang-format on */

struct {
  void solve() {
    i64 n, s;
    cin >> n >> s;
    vi64 a(n);
    cin >> a;
    vpi64 dp(1 << n, {1e9, 0});
    dp[0] = {1, 0};
    vpi32 prev(1 << n);
    for (i32 m = 0; m < (1 << n); ++m) {
      if (dp[m].first == 1e9)
        continue;
      for (i32 i = 0; i < n; ++i) {
        if (!(m & (1 << i))) {
          i64 n_s, n_k;
          if (dp[m].second + a[i] > s) {
            n_k = dp[m].first + 1;
            n_s = a[i];
          } else {
            n_k = dp[m].first;
            n_s = dp[m].second + a[i];
          }
          if (dp[m ^ 1 << i].first > n_k ||
              (dp[m ^ 1 << i].first == n_k && dp[m ^ 1 << i].second > n_s)) {
            dp[m ^ 1 << i] = {n_k, n_s};
            prev[m ^ 1 << i] = {i, n_k != dp[m].first};
          }
        }
      }
    }
    vvi32 kn(dp[(1 << n) - 1].first);
    for (i32 i = 0, m = (1 << n) - 1; m;) {
      kn[i].push_back(prev[m].first + 1);
      i += prev[m].second;
      m ^= 1 << prev[m].first;
    }
    cout << kn.size() << '\n';
    for (i32 i = 0; i < kn.size(); ++i) {
      cout << kn[i].size() << ' ' << kn[i] << '\n';
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
