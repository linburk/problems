#include <bits/stdc++.h>
#include <climits>

#define LOCAL__ 1 && __APPLE__
#define REDIRECT__ 1 && __APPLE__
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
    i64 const INF = 1E18;
    i32 n, m, k;
    cin >> n >> m >> k;
    vi32 rare(k);
    cin >> rare;
    for (auto &&i : rare) --i;
    vvpi64 rgr(n);
    vvpi64 gr(n);
    for (i32 i = 0; i < m; ++i) {
      i64 a, b, w;
      cin >> a >> b >> w;
      rgr[b - 1].push_back({a - 1, w});
      gr[a - 1].push_back({b - 1, w});
    }
    std::function<vi64(i32, bool)> dijkstra_all = [&] (i32 s, bool reversive) -> vi64 {
      vi64 dist(n, 2 * INF);
      dist[s] = 0;
      spi64 q{{0, s}};
      for (; q.size();) {
        auto [d, v] = *q.begin();
        q.erase(q.begin());
        for (auto [to, w] : (reversive ? rgr[v] : gr[v])) {
          if (dist[to] > dist[v] + w) {
            q.erase({dist[to], to});
            dist[to] = dist[v] + w;
            q.insert({dist[to], to});
          }
        }
      }
      return dist;
    };
    vvi64 rare_dist_to(k);
    vvi64 rare_dist_from(k);
    for (i32 i = 0; i < k; ++i) {
      rare_dist_to[i] = dijkstra_all(rare[i], 1);
      rare_dist_from[i] = dijkstra_all(rare[i], 0);
    }
    umpi32 match;
    for (i32 i = 0; i < k; ++i)
      match[rare[i]] = i;
    vvi64 rare_path(k, vi64(k));
    for (i32 i = 0; i < k; ++i) {
      for (i32 j = 0; j < k; ++j) {
        rare_path[i][j] = rare_dist_from[i][rare[j]];
      }
    }
    std::function<i64(i32, i32, vi32)> query = [&] (i32 s, i32 t, vi32 p) -> i64 {
      vvi64 dist(1 << p.size(), vi64(p.size(), 2 * INF));
      vi32 v(p.size());
      for (i32 i = 0; i < p.size(); ++i) {
        v[i] = match[p[i]];
      }
      std::set<pair<i64, pi32> > q;
      for (i32 i = 0; i < p.size(); ++i) {
        dist[1 << i][i] = rare_dist_to[v[i]][s];
        q.insert({dist[1 << i][i], {1 << i, i}});
      }
      for (; q.size(); ) {
        auto [d, tmp] = *q.begin();
        auto [cur_mask, cur] = tmp;
        q.erase(q.begin());
        for (i32 i = 0; i < v.size(); ++i) {
          i32 to = i;
          i32 to_mask = cur_mask | (1 << i);
          i64 w = rare_path[v[cur]][v[to]];
          if (to == cur) continue;
          if (dist[to_mask][to] > dist[cur_mask][cur] + w) {
            q.erase({dist[to_mask][to], {to_mask, to}});
            dist[to_mask][to] = dist[cur_mask][cur] + w;
            q.insert({dist[to_mask][to], {to_mask, to}});
          }
        }
      }
      i64 res = 2 * INF;
      for (i32 i = 0; i < v.size(); ++i) {
        i64 w = rare_dist_from[v[i]][t];
        res = std::min(res, dist.back()[i] + w);
      }
      return res;
    };
    i32 q;
    cin >> q;
    for (i32 i = 0; i < q; ++i) {
      i32 s, t, p;
      cin >> s >> t >> p;
      vi32 k(p);
      cin >> k;
      --s, --t;
      for (auto &&j : k) --j;
      i64 r = query(s, t, k);
      cout << (r > INF ? -1 : r) << '\n';
    }
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
  i32 t; std::cin >> t; for (i32 i = 0; i < t; i++)
#endif
  solution.solve();
#if REDIRECT__
  cin.close();
  cout.close();
#endif
  return 0;
} /* clang-format on */

