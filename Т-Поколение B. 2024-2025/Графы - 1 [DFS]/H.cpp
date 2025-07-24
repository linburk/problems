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
#define MULTITEST 0

vvi32 gr;
vvi32 rgr;
vi32 out;
vb used;
vi32 order;
vi32 member;
i32 csz = 0;

void ts(i32 v) {
  if (used[v])
    return;
  used[v] = 1;
  for (auto to : gr[v])
    ts(to);
  order.push_back(v);
}
void cs(i32 v) {
  member[v] = csz;
  for (auto to : rgr[v])
    if (member[to] == -1)
      cs(to);
}

void solve() {
  i32 n, m;
  cin >> n >> m;
  vvi32 t(n, vi32(m));
  gr.resize(n * m);
  rgr.resize(n * m);
  out.resize(n * m);
  used.resize(n * m);
  member.resize(n * m, -1);
  cin >> t;
  vpi32 mv{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  for (i32 i = 0; i < n; ++i) {
    for (i32 j = 0; j < m; ++j) {
      for (auto [di, dj] : mv) {
        if (di + i < n && di + i >= 0 && dj + j < m && dj + j >= 0) {
          if (t[i][j] >= t[di + i][dj + j]) {
            gr[i * m + j].push_back((di + i) * m + j + dj);
            rgr[(di + i) * m + j + dj].push_back(i * m + j);
          }
        }
      }
    }
  }
  for (i32 i = 0; i < n * m; ++i) {
    ts(i);
  }
  for (i32 i = n * m - 1; i >= 0; --i) {
    if (member[order[i]] == -1) {
      cs(order[i]);
      ++csz;
    }
  }
  for (i32 i = 0; i < n * m; ++i) {
    for (auto to : gr[i]) {
      if (member[to] != member[i])
        ++out[member[i]];
    }
  }
  i32 c = 0;
  for (i32 i = 0; i < csz; ++i) {
    if (out[i] == 0)
      ++c;
  }
  cout << c << '\n';
}

#define PRECALCULATE 0
void precalc();
i32 main(i32 argc, char *argv[]) /* clang-format off */ {
    std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false); setlocale(LC_ALL, "Russian");
#if REDIRECT
    char *FINPATH = std::getenv("FINPATH"), *FOUTPATH = std::getenv("FOUTPATH");
    std::freopen(FINPATH, "r", stdin); std::freopen(FOUTPATH, "w", stdout);
#endif
#if PRECALCULATE
    precalc();
#endif
#if MULTITEST
    i32 t; std::cin >> t; for (i32 i = 0; i < t; i++)
#endif
    solve();
    return 0;
} /* clang-format on */
