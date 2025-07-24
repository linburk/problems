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

struct p_ {
  __int128 x, y;
};
std::istream& operator>>(std::istream& is, p_ &rhs) {
  i64 x_, y_;
  is >> x_ >> y_;
  rhs.x = x_, rhs.y = y_;
  return is;
}
p_ operator-(p_ const &lhs, p_ const &rhs) {
  return {lhs.x - rhs.x, lhs.y - rhs.y};
}
__int128 operator%(p_ const &lhs, p_ const &rhs) {
  return lhs.x * rhs.y - lhs.y * rhs.x;
}
__int128 operator*(p_ const &lhs, p_ const &rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y;
}

struct {
  void solve() {
    i32 n;
    cin >> n;
    vector<pair<__int128, vector<p_> > > fence(n);
    for (i32 i = 0; i < n; ++i) {
      i32 k;
      cin >> k;
      fence[i].second.resize(k);
      fence[i].first = LONG_LONG_MAX;
      cin >> fence[i].second;
      for (i32 j = 0; j < k; ++j)
        fence[i].first = std::min(fence[i].second[j].x, fence[i].first);
    }
    std::sort(all(fence), [] (pair<__int128, vector<p_> > const &lhs, pair<__int128, vector<p_> > const &rhs) {
      return lhs.first > rhs.first;
    });
    auto in_angle = [] (p_ a, p_ o, p_ b, p_ m) -> bool {
      return ((a - o) % (m - o)) * ((a - o) % (b - o)) >= 0 && ((b - o) % (m - o)) * ((b - o) % (a - o)) >= 0;
    };
    auto area = [] (vector<p_> &sh) -> __int128 {
      __int128 res = sh[sh.size() - 1] % sh[0];
      for (i32 i = 0; i < sh.size() - 1; ++i) {
        res += sh[i] % sh[i + 1];
      }
      return res < 0 ? -res : res;
    };
    auto localize = [&in_angle] (vector<p_> &fence, p_ p) -> bool {
      i32 l_b = 1;
      i32 cent = 0;
      i32 r_b = 1;
      i32 l, r;
      for (l = r_b, r = static_cast<i32>(fence.size()) - 1; r - l > 1;) {
        i32 m = (l + r) >> 1;
        in_angle(fence[fence.size() - l_b], fence[cent], fence[m], p) ? l = m : r = m;
      }
      r_b = l;
      for (l = l_b, r = static_cast<i32>(fence.size()) - r_b; r - l > 1;) {
        i32 m = (l + r) >> 1;
        in_angle(fence[fence.size() - m], fence[cent], fence[r_b], p) ? l = m : r = m;
      }
      l_b = l;
      return in_angle(fence[fence.size() - l_b], fence[cent], fence[r_b], p) && in_angle(fence[r_b], fence[fence.size() - l_b], fence[cent], p);
    };
    vb count(n);
    i32 q;
    cin >> q;
    for (i32 i = 0; i < q; ++i) {
      i32 l = -1, r = n;
      p_ p; cin >> p;
      for (; r - l > 1;) {
        i32 m = (l + r) >> 1;
        localize(fence[m].second, p) ? r = m : l = m;
      }
      if (r == n) continue;
      count[r] = 1;
    }
    __int128 res = 0;
    for (i32 i = 0; i < n; ++i) {
      if (count[i]) res += area(fence[i].second);
      if (i - 1 > 0) res -= area(fence[i - 1].second);
    }
    cout << std::setprecision(6) << std::fixed << static_cast<f64>(res) / 2.L << '\n';
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