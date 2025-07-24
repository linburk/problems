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
template <char SEP = ' '> void print(auto&&...args) { ((std::cout << args << SEP), ...); std::cout << "\n"; }
void input(auto&&... args) { ((std::cin >> args), ...); }
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
  struct big_int {
    vi64 data;
    bool is_0() {
      for (i32 i = static_cast<i32>(data.size())-1; i >= 0; --i)
        if (data[i]) return 0;
      return 1;
    }
    bool odd() {
      return data[0] & 1;
    }
    big_int half() {
      big_int res = *this;
      for (i32 i = static_cast<i32>(res.data.size())-1; i >= 0; --i) {
        if (i > 0)
            res.data[i - 1] += (res.data[i] % 2) * 1e9;
        res.data[i] /= 2;
      }
      return res;
    }
    big_int(string s) {
      data.resize(s.size() / 9 + 1);
      for (i64 i = 0, p = 1; i < s.size(); ++i, p *= 10) {
        p %= static_cast<i32>(1e9);
        data[i / 9] += (s[i] - '0') * p;
      }
    }
  };
  vvi32 mult(vvi32 const &m1, vvi32 const &m2, i32 mod) {
    vvi32 m(m1.size(), vi32(m2[0].size()));
    for (i32 i = 0; i < m1.size(); ++i) {
      for (i32 j = 0; j < m2[0].size(); ++j) {
        for (i32 p = 0; p < m1[0].size(); ++p) {
          m[i][j] = (m[i][j] + m1[i][p] * m2[p][j] % mod) % mod;
        }
      }
    }
    return m;
  }
  vvi32 bpow(vvi32 matrix, big_int pow, i32 mod) {
    if (pow.is_0()) {
      vvi32 res(matrix.size(), vi32(matrix.size()));
      for (i32 i = 0; i < matrix.size(); ++i) res[i][i] = 1;
      return res;
    }
    vvi32 res = bpow(matrix, pow.half(), mod);
    if (pow.odd()) {
      return mult(mult(res, res, mod), matrix, mod);
    }
    return mult(res, res, mod);
  }
  void solve() {
    string n;
    i32 m, p;
    cin >> n >> m >> p;
    if (n.size() == 1 && n[0] == '1') {
      cout << (1<<m);
      return;
    }
    vvi32 matrix((1<<m)+1, vi32((1<<m)+1));
    auto check = [&m](i32 i, i32 j) {
      std::bitset<6> a(i), b(j);
      for (i32 k = 0; k < m-1; ++k) {
        if (a[k] == a[k+1] && a[k+1] == b[k] && b[k] == b[k+1]) {
          return 0;
        }
      }
      return 1;
    };
    for (i32 i = 1; i <= (1<<m); ++i) {
      matrix[0][i] = 1;
    }
    for (i32 i = 1; i <= (1<<m); ++i) {
      for (i32 j = 1; j <= (1<<m); ++j) {
        matrix[i][j] = check(i-1, j-1);
      }
    }
    vvi32 a{{0, 1}, {1, 1}};
//    print(matrix);
    vvi32 r = bpow(matrix, big_int(n), p);
//    print(r);
    i32 res = 0;
    for (i32 i = 1; i <= (1<<m); ++i) {
      res = (res + r[0][i]) % p;
    }
    cout << res << '\n';
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