#include <bits/stdc++.h>
#include <climits>

#define LOCAL__ 1 && __APPLE__
#define REDIRECT__ 1 && __APPLE__
#define PRECALCULATE__ 0
#define MULTITEST__ 0

namespace /* clang-format off */ {
#define all(cont) cont.begin(), cont.end()
using std::string;
#if REDIRECT__
std::ifstream cin; std::ofstream cout;
#else
using std::cin, std::cout;
#endif
namespace /* aliases */ {
using i8 = std::int8_t; using i16 = std::int16_t; using i32 = std::int32_t; using i64 = std::int64_t;
using u8 = std::uint8_t; using u16 = std::uint16_t; using u32 = std::uint32_t; using u64 = std::uint64_t;  using f64 = long double; using f32 = float;
#if __GNUC__ && (__x86_64__ || __arm64__)
using i128 = __int128; using u128 = unsigned __int128;
#endif
template <typename T> using v = std::vector<T>;
template <typename T> using s = std::set<T>;
template <typename T, typename V> using p = std::pair<T, V>;
template <typename T, typename V> using m = std::map<T, V>;
template <typename T, typename V> using um = std::unordered_map<T, V>;
}
namespace /* in/out op. overloadings */ {
template <typename T, typename V> std::istream &operator>>(std::istream &is, std::pair<T, V> &p) { is >> p.first >> p.second; return is; }
template <typename T> std::istream &operator>>(std::istream &is, std::vector<T> &cont) { for (auto &i : cont) { is >> i; } return is; }
template <typename T, typename V, char SEP = ' ', char ENDL = '\n'> std::ostream &operator<<(std::ostream &os, std::pair<T, V> const &p) {
#if LOCAL__
  os << "<" << p.first << ", " << p.second << ">";
  return os;
#else
  os << p.first << SEP << p.second << ENDL;
  return os;
#endif
}
template <typename T, char SEP = ' ', char ENDL = '\n'> std::ostream &operator<<(std::ostream &os, const std::vector<T> &cont) {
#if LOCAL__
  os << "[";
  for (auto b = cont.begin(), e = cont.end(); b != e; ++b)
    os << *b << (b + 1 == e ? "" : ", "); os << "]";
  return os;
#else
  for (auto b = cont.begin(), e = cont.end(); b != e; ++b)
    os << *b << (b + 1 == e ? ENDL : SEP);
  return os;
#endif
}
#if __GNUC__ && (__x86_64__ || __arm64__)
std::istream &operator>>(std::istream &is, i128 &rhs) {
  i64 res; is >> res; rhs = res; // btw, no sense to in nmbr mr than 20 chars
  return is;
}
std::ostream &operator<<(std::ostream &os, i128 const &rhs){
  std::string res;
  for (i128 tmp = (rhs < 0 ? -rhs : rhs); tmp; tmp /= 10)
    res += '0' + tmp % 10;
  if (rhs < 0) res += '-';
  for (auto i = res.rbegin(); i != res.rend(); ++i)
    os << *i;
  return os;
}
#endif
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
  void solve() {
    i32 n, m;
    cin >> n >> m;
    v<v<i32> > gr(n);
    for (i32 i = 1; i < n; ++i) {
      i32 p;
      cin >> p;
      gr[p].push_back(i);
    }
    v<v<i32> > up(n, v<i32>(20));
    v<i32> d(n);
    std::function<void(i32, i32)> dfs = [&] (i32 v, i32 p) {
      d[v] = d[p] + 1;
      up[v][0] = p;
      for (i32 i = 1; i < 20; ++i)
        up[v][i] = up[up[v][i - 1]][i - 1];
      for (auto to : gr[v])
        dfs(to, v);
    };
    dfs(0, 0);
    v<i32> a(2 * m);
    cin >> a[0] >> a[1];
    i64 x, y, z;
    cin >> x >> y >> z;
    for (i32 i = 2; i < 2 * m; ++i) {
      a[i] = (x * a[i - 2] + y * a[i - 1] + z) % n;
    }
    i64 ans = 0;
    for (i32 v = 0, i = 0; i < m; ++i) {
      i32 a1 = (a[2 * i] + v) % n;
      i32 a2 = a[2 * i + 1];
      if (d[a1] < d[a2]) std::swap(a1, a2);
      for (i32 j = 19; j >= 0; --j)
        if (d[up[a1][j]] >= d[a2])
          a1 = up[a1][j];
      if (a1 == a2) {
        ans += a1;
        v = a1;
        continue;
      }
      for (i32 j = 19; j >= 0; --j)
        if (up[a1][j] != up[a2][j])
          a1 = up[a1][j], a2 = up[a2][j];
      ans += up[a1][0];
      v = up[a1][0];
    }
    cout << ans << '\n';
  }
  void precalculate();
} solution;

i32 main(i32 argc, char *argv[], char *envp[]) /* clang-format off */ {
  cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
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

