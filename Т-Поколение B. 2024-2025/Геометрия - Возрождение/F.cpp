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

template <class T>
struct p_ {
  T x, y;
  f64 abs() const { return std::sqrt(x * x + y * y); }
};
template <class T> std::istream& operator>>(std::istream& is, p_<T> &rhs) {
  cin >> rhs.x >> rhs.y;
  return is;
}
template <class T> p_<T> operator-(p_<T> const &lhs, p_<T> const &rhs) {
  return {lhs.x - rhs.x, lhs.y - rhs.y};
}
template <class T> p_<T> operator+(p_<T> const &lhs, p_<T> const &rhs) {
  return {lhs.x + rhs.x, lhs.y + rhs.y};
}
template <class T> T operator%(p_<T> const &lhs, p_<T> const &rhs) {
  return lhs.x * rhs.y - lhs.y * rhs.x;
}
template <class T> T operator*(p_<T> const &lhs, p_<T> const &rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y;
}
template <class T> p_<T> operator*(p_<T> const &lhs, T k) {
  return {lhs.x * k, lhs.y * k};
}

struct {
  void solve() {
    i32 n;
    cin >> n;
    vector<p_<f64> > pnt(n);
    cin >> pnt;
    f64 l = 1E5, r = -1E5;
    for (i32 i = 0; i < n; ++i) {
      l = std::min(l, pnt[i].x);
      r = std::max(r, pnt[i].x);
    }
    auto area2 = [&pnt, &n] (f64 x) -> pair<f64, f64> {
      f64 res[2] {0, 0};
      bool was[2] {0, 0};
      p_<f64> mid[2];
      p_<f64> first[2];
      bool f = 0;
      f64 eps = 1E-7;
      for (i32 i = 0; i < n; ++i) {
        if (!was[f])
          first[f] = pnt[i];
        p_ st = pnt[i];
        p_ en = pnt[(i + 1) % n];
        if ((en.x + eps > x && x > st.x) || (en.x - eps < x && x < st.x)) {
          mid[f] = {en - st};
          mid[f] = mid[f] * ((x - st.x) / (en - st).x);
          mid[f] = mid[f] + st;
          res[f] += st % mid[f];
          res[f ^ 1] += mid[f] % en;
          f ^= 1;
        } else {
          res[f] += st % en;
        }
      }
      res[0] += mid[0] % mid[1];
      res[1] += mid[1] % mid[0];
      return {std::abs(res[0]), std::abs(res[1])};
    };
    for (i32 i = 0; i < 200; ++i) {
      f64 m1 = (2 * l + r) / 3;
      f64 m2 = (l + 2 * r) / 3;
      pair<f64, f64> ar1 = area2(m1), ar2 = area2(m2);
      std::abs(ar1.first - ar1.second) > std::abs(ar2.first - ar2.second) ? l = m1 : r = m2;
    }
    cout << std::setprecision(9) << std::fixed << l << '\n';
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

