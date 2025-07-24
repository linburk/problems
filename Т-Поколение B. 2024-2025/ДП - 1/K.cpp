#include <bits/stdc++.h>
#include <climits>

#define LOCAL 1 && __APPLE__
#define ALTERSTREAM 1 && __APPLE__
#define PRECALCULATE 0
#define MULTITEST 0

namespace /* clang-format off */ {
#define all(cont) cont.begin(), cont.end()
using std::vector, std::string, std::pair;
#if ALTERSTREAM
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
#if LOCAL
  os << "<" << p.first << ", " << p.second << ">"; return os;
#else
  os << p.first << SEP << p.second << ENDL; return os;
#endif
}
template <typename T, char SEP = ' ', char ENDL = '\n'> std::ostream &operator<<(std::ostream &os, const std::vector<T> &cont) {
#if LOCAL
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
    i32 n, k;
    cin >> n >> k;
    vi32 p(n);
    cin >> p;
    vi32 cycles;
    vi32 used(n);
    vi32 stack;
    std::function<i32(i32)> dfs = [&] (i32 v) -> i32 {
      if (used[v]) {
        i32 r = static_cast<i32>(stack.size());
        stack.clear();
        return r;
      }
      used[v] = 1;
      stack.push_back(v);
      return dfs(p[v]-1);
    };
    for (i32 i = 0; i < n; ++i) {
      i32 s = dfs(i);
      if (s != 0) {
        cycles.push_back(s);
      }
    }
    i32 max = 0;
    i32 kt = k;
    for (i32 i = 0; i < cycles.size(); ++i) {
      max += std::min(kt, cycles[i] / 2) * 2;
      kt -= std::min(kt, cycles[i] / 2);
    }
    for (i32 i = 0; i < cycles.size(); ++i) {
      if (kt && cycles[i] % 2) --kt, ++max;
    }
    vi32 nw = [&] -> vi32 {
      mpi32 cw;
      for (i32 i = 0; i < cycles.size(); ++i)
        ++cw[cycles[i]];
      vi32 nw;
      for (auto &&[w, c] : cw) {
        for (i32 i = 0, s = 0;; ++i) {
          nw.push_back(w * (1 << i));
          s |= (1 << i);
          if ((s | (1 << (i + 1))) > c) {
            nw.push_back(w * (c - s));
            break;
          }
        }
        
      }
      return nw;
    }();
    std::bitset<1000001> ks;
    ks[0] = 1;
    for (i32 i = 0; i < nw.size(); ++i) {
      ks |= ks << nw[i];
    }
    i32 min = (ks[k] ? k : k+1);
    cout << min << ' ' << max << '\n';
  }
  void precalculate();
} solution;

i32 main(i32 argc, char *argv[], char *envp[]) /* clang-format off */ {
  std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
  std::setlocale(LC_ALL, "Russian");
#if ALTERSTREAM
  cin.open(std::getenv("FINPATH"));
  cout.open(std::getenv("FOUTPATH"));
#endif
#if PRECALCULATE
  solution.precalculate();
#endif
#if MULTITEST
  i32 t; std::cin >> t; for (i32 i = 0; i < t; i++)
#endif
  solution.solve();
#if ALTERSTREAM
  cin.close();
  cout.close();
#endif
  return 0;
} /* clang-format on */

