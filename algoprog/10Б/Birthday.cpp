#include <bits/stdc++.h>
#include <climits>

#define LOCAL__ 1 && __APPLE__
#define REDIRECT__ 1 && __APPLE__
#define PRECALCULATE__ 0
#define MULTITEST__ 1

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
using u8 = std::uint8_t; using u16 = std::uint16_t; using u32 = std::uint32_t; using u64 = std::uint64_t; using f64 = long double; using f32 = float;
using pi32 = std::pair<i32, i32>; using vpi32 = std::vector<pi32>; using vvpi32 = std::vector<vpi32>; using pi64 = std::pair<i64, i64>; using vpi64 = std::vector<pi64>; using vvpi64 = std::vector<vpi64>; using pu32 = std::pair<u32, u32>; using pu64 = std::pair<u64, u64>;
using vi32 = std::vector<i32>; using vvi32 = std::vector<vi32>; using vi64 = std::vector<i64>; using vvi64 = std::vector<vi64>; using vu64 = std::vector<u64>; using vvu64 = std::vector<vu64>;
using vb = std::vector<bool>; using vvb = std::vector<vb>; using vc = std::vector<char>; using vvc = std::vector<vc>;
using si32 = std::set<i32>; using spi32 = std::set<pi32>; using si64 = std::set<i64>; using spi64 = std::set<pi64>;
using mpi32 = std::map<i32, i32>; using umpi32 = std::unordered_map<i32, i32>; using mpi64 = std::map<i64, i64>; using umpi64 = std::unordered_map<i64, i64>;
#if __GNUC__ && ( __x86_64__ || __arm64__ )
using i128 = __int128; using u128 = unsigned __int128;
using pi128 = std::pair<i128, i128>; using vpi128 = std::vector<pi128>; using vvpi128 = std::vector<vpi128>;
using vi128 = std::vector<i128>; using vvi128 = std::vector<vi128>;
using si128 = std::set<i128>; using spi128 = std::set<pi128>;
using mpi128 = std::map<i128, i128>; using umpi128 = std::unordered_map<i128, i128>;
#endif
template <typename T> using v = std::vector<T>;
template <typename T> using s = std::set<T>;
template <typename T, typename V> using p = std::pair<T, V>;
template <typename T, typename V> using m = std::map<T, V>;
template <typename T, typename V> using um = std::unordered_map<T, V>;
}
namespace /* in/out op. overloadings */ {
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
    cin >> m >> n;
    vvi32 gr(n);
    for (i32 i = 0; i < m; ++i) {
      vb to_(n);
      for (i32 c; cin >> c && c != 0;) {
        to_[c - 1] = 1;
      }
      for (i32 j = 0; j < n; ++j) {
        if (to_[j] == 0) {
          gr[j].push_back(i);
        }
      }
    }
    vi32 match(m, -1);
    vi32 used(n, -1);
    std::function<bool(i32, i32)> dfs = [&] (i32 v, i32 it) -> bool {
      if (used[v] == it) return 0;
      used[v] = it;
      for (auto to : gr[v]) {
        if (match[to] == -1 || dfs(match[to], it)) {
          match[to] = v;
          return 1;
        }
      }
      return 0;
    };
    for (i32 i = 0; i < n; ++i) {
      dfs(i, i);
    }
    vb used1(n), used2(m);
    vb in_matching(n);
    for (auto &&i : match) { --i; in_matching[i] = 1; }
    std::function<void(i32)> dfs2 = [&] (i32 v) {
      if (used1[v]) return;
      used1[v] = 1;
      for (auto to : gr[v]) {
        used2[to] = 1;
        if (match[to] != -1)
          dfs2(match[to]);
      }
    };
    for (i32 i = 0; i < n; ++i) {
      if (!in_matching[i]) dfs2(i);
    }
    vi32 f, s;
    for (i32 i = 0; i < n; ++i) {
      if (used1[i]) {
        s.push_back(i + 1);
      }
    }
    for (i32 i = 0; i < m; ++i) {
      if (!used2[i])
        f.push_back(i + 1);
    }
    cout << f.size() + s.size() << '\n' << f.size() << ' ' << s.size() << '\n' << f << '\n' << s << '\n';
  }
  void precalculate();
} solution;

i32 main(i32 argc, char *argv[], char *envp[]) /* clang-format off */ {
  cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
  std::setlocale(LC_ALL, "Russian");
#if REDIRECT__
  cin.open("/users/dmitrii/xcode_solution/xcode_solution/input.txt");
  cout.open("/users/dmitrii/xcode_solution/xcode_solution/output.txt");
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