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
  for (auto beg = cont.begin(), end = cont.end(); beg != end; ++beg) os << *beg << (beg + 1 == end ? "]" : ", "); return os;
#else
  for (auto beg = cont.begin(), end = cont.end(); beg != end; ++beg) os << *beg << (beg + 1 == end ? ENDL : SEP); return os;
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
    i32 const mod = (1 << 30) + 1;
    i32 n, m;
    cin >> n >> m;
    if (n > m)
      std::swap(n, m);
    vvi32 curr(n, vi32(1 << (n + 1))), next(n, vi32(1 << (n + 1)));
    i32 bm = (1 << (n + 1)) - 1;
    curr[0][0] = 1;
    for (i32 j = 0; j < m; ++j) {
      next.assign(n, vi32(1 << (n + 1), 0));
      for (i32 i = 0; i < n; ++i) {
        for (i32 mask = 0; mask < (1 << (n + 1)); ++mask) {
          std::bitset<24> tm(mask);
          if (i == 0 && i != n - 1) {
            curr[i + 1][(mask << 1) & bm | 0] =
                (1ll * curr[i + 1][(mask << 1) & bm | 0] + curr[i][mask]) % mod;
            curr[i + 1][(mask << 1) & bm | 1] =
                (1ll * curr[i + 1][(mask << 1) & bm | 1] + curr[i][mask]) % mod;
          } else {
            i32 mv = (i + 1) % n == 0;
            if (j == 0 || i - 1 < 0 || i + 1 > n ||
                !(tm[i - 1] == tm[i] && tm[i] == tm[i + 1])) {
              if (mv) {
                next[0][mask] = (1ll * next[0][mask] + curr[i][mask]) % mod;
              } else {
                curr[i + 1][mask] =
                    (1ll * curr[i + 1][mask] + curr[i][mask]) % mod;
              }
            }
            if (mv) {
              next[0][mask ^ (1 << i)] =
                  (1ll * next[0][mask ^ (1 << i)] + curr[i][mask]) % mod;
            } else {
              curr[i + 1][mask ^ (1 << i)] =
                  (1ll * curr[i + 1][mask ^ (1 << i)] + curr[i][mask]) % mod;
            }
          }
        }
      }
      curr = next;
    }
    i64 r = 0;
    for (i32 i = 0; i < (1 << (n + 1)); ++i) {
      r = (r + next[0][i]) % mod;
    }
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
