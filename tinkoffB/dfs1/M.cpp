#include <bits/stdc++.h>
#include <climits>

#define LOCAL__ 1 && __APPLE__
#define REDIRECT__ 0 && __APPLE__
#define PRECALCULATE__ 0
#define MULTITEST__ 0

namespace /* clang-format off */ {
#define all(cont) cont.begin(), cont.end()
using std::vector, std::string, std::pair;
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
  void solve() {
    i32 n, m;
    cin >> n >> m;
    if (m > 2 * n - 2) {
      cout << "! No" << std::endl;
      return;
    }
    vvpi32 gr(n);
    for (i32 i = 0, remain = 0; i < n; ++i) {
      for (i32 ask = 0; remain != m;) {
        cout << "? " << i + 1 << std::endl;
        cin >> ask;
        if (ask == -1) break;
        if (ask != i + 1) {
          gr[i].push_back({ask - 1, remain});
          gr[ask - 1].push_back({i, remain});
        }
        ++remain;
      }
    }
    vi32 depth(n);
    vi32 min_depth(n);
    vi32 is_bridge(m);
    vpi32 bridges;
    std::function<void(i32, i32, i32)> dfs = [&] (i32 v, i32 p, i32 p_ind) {
      depth[v] = min_depth[v] = depth[p] + 1;
      for (auto [to, to_ind] : gr[v]) {
        if (to == p && to_ind != p_ind)
          is_bridge[to_ind] = is_bridge[p_ind] = -1;
        if (to == p) continue;
        if (depth[to]) {
          min_depth[v] = std::min(depth[to], min_depth[v]);
        } else {
          dfs(to, v, to_ind);
          min_depth[v] = std::min(min_depth[v], min_depth[to]);
          if (min_depth[to] > depth[v] && is_bridge[to_ind] != -1) {
            bridges.push_back({v + 1, to + 1});
          }
        }
      }
    };
    for (i32 i = 0; i < n; ++i) {
      if (!depth[i]) dfs(i, i, -1);
    }
    if (bridges.size() < (m + 1) / 2) {
      cout << "! No" << std::endl;
    } else {
      cout << "! Yes\n";
      for (i32 i = 0; i < (m + 1) / 2; ++i)
        cout << bridges[i].first << " " << bridges[i].second << "\n";
      cout.flush();
    }
  }
  void precalculate();
} solution;

i32 main(i32 argc, char *argv[], char *envp[]) /* clang-format off */ {
//  std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
//  std::setlocale(LC_ALL, "Russian");
#if REDIRECT__
  cin.open(std::getenv("FINPATH"));
  cout.open(std::getenv("FOUTPATH"));
#endif
#if PRECALCULATE__
  solution.precalculate();
#endif
#if MULTITEST__
  i32 t; std::cin >> t; for (i32 i = 0; i < t; i++)
#endif
  solution.solve();
#if REDIRECT__
  cin.close();
  cout.close();
#endif
  return 0;
} /* clang-format on */

