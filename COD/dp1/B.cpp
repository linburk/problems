#include <bits/stdc++.h>
#include <climits>

#define LOCAL__ 1 && __APPLE__
#define REDIRECT__ 1 && __APPLE__
#define PRECALCULATE__ 0
#define MULTITEST__ 0

namespace /* clang-format off */ {
#define all(cont) cont.begin(), cont.end()
#if REDIRECT__
std::ifstream cin; std::ofstream cout;
#else
using std::cin, std::cout;
#endif
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
#if LOCAL__
  os << "<" << p.first << ", " << p.second << ">"; return os;
#else
  os << p.first << SEP << p.second << ENDL; return os;
#endif
}
template <typename T, char SEP = ' ', char ENDL = '\n'> std::ostream &operator<<(std::ostream &os, const std::vector<T> &cont) {
#if LOCAL__
  os << "[";
  for (auto b = cont.begin(), e = cont.end(); b != e; ++b) os << *b << (b + 1 == e ? "" : ", "); os << "]"; return os;
#else
  for (auto b = cont.begin(), e = cont.end(); b != e; ++b) os << *b << (b + 1 == e ? ENDL : SEP); return os;
#endif
}
}
namespace /* functions */ {
#if __cplusplus >= 202002L
void print(auto &&...args) { ((cout << args), ...); }
void input(auto &&...args) { ((cin >> args), ...); }
#endif
template <typename T> void inline unique(std::vector<T> &cont) { cont.erase(std::unique(cont.begin(), cont.end()), cont.end()); }
std::mt19937_64 ru64(std::chrono::steady_clock().now().time_since_epoch().count());
}
} /* clang-format on */

struct {
  i32 const mod = 1e9+7;
  vvi64 mult(vvi64 m1, vvi64 m2) {
    vvi64 res(m1.size(), vi64(m2[0].size()));
    for (i32 i = 0; i < m1.size(); ++i) {
      for (i32 j = 0; j < m2[0].size(); ++j) {
        for (i32 k = 0; k < m1[0].size(); ++k) {
          res[i][j] = (res[i][j] + m1[i][k] * m2[k][j] % mod) % mod;
        }
      }
    }
    return res;
  }
  vvi64 binpow(vvi64 matr, i64 pow) {
    vvi64 res(matr.size(), vi64(matr.size()));
    for (i32 i = 0; i < matr.size(); ++i) {
      res[i][i] = 1;
    }
    for (;pow;) {
      if (pow & 1) res = mult(res, matr);
      matr = mult(matr, matr);
      pow >>= 1;
    }
    return res;
  }
  void solve() {
    i64 n, m, k;
    cin >> n >> m >> k;
    vvi64 matrix(m+1, vi64(m+1, 1));
    for (i32 i = 0; i <= m; ++i)
      matrix[i][0] = 0;
    for (i32 i = 0; i < k; ++i) {
      char c1, c2;
      cin >> c1 >> c2;
      i8 c1_i = (std::isupper(c1) ? 26 + c1 - 'A' : c1 - 'a') + 1;
      i8 c2_i = (std::isupper(c2) ? 26 + c2 - 'A' : c2 - 'a') + 1;
      matrix[c1_i][c2_i] = 0;
    }
    vvi64 res = binpow(matrix, n);
    i64 ans = 0;
    for (i32 j = 1; j <= m; ++j) {
        ans = (ans + res[0][j]) % mod;
    }
    cout << ans << '\n';
  }
  void precalculate();
} solution;

i32 main(i32 argc, char *argv[], char *envp[]) /* clang-format off */ {
  std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
  std::setlocale(LC_ALL, "Russian");
#if REDIRECT__
  cin.open(std::getenv("FINPATH"));
  cout.open(std::getenv("FOUTPATH"));
#endif
#if PRECALCULATE__
  solution.precalculate();
#endif
#if MULTITEST__
  i32 t; cin >> t; for (i32 i = 0; i < t; i++)
#endif
  solution.solve();
#if REDIRECT__
  cin.close();
  cout.close();
#endif
  return 0;
} /* clang-format on */

