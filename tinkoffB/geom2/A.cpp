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
  i64 x, y;
};
std::istream& operator>>(std::istream& is, p_ &rhs) {
  is >> rhs.x >> rhs.y;
  return is;
}
p_ operator-(p_ const &lhs, p_ const &rhs) {
  return {lhs.x - rhs.x, lhs.y - rhs.y};
}
i64 operator%(p_ const &lhs, p_ const &rhs) {
  return lhs.x * rhs.y - lhs.y * rhs.x;
}
i64 operator*(p_ const &lhs, p_ const &rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y;
}

struct {
  void solve() {
    i32 n;
    cin >> n;
    vector<pair<i32, p_> > pnt(n);
    for (i32 i = 0; i < n; ++i)
      cin >> pnt[i].second, pnt[i].first = i;
    vi32 res(n);
    auto build_ch = [] (vector<pair<i32, p_> > &pnt) {
      vi32 ch{0};
      for (i32 i = 0; i < pnt.size(); ++i)
        if (pnt[i].second.x < pnt[0].second.x || (pnt[i].second.x == pnt[0].second.x && pnt[i].second.y < pnt[0].second.y))
          std::swap(pnt[i], pnt[0]);
      std::sort(pnt.begin() + 1, pnt.end(), [&] (pair<i32, p_> &a, pair<i32, p_> &b) {
        p_ v_a = a.second - pnt[0].second, v_b = b.second - pnt[0].second;
        if (v_a % v_b == 0)
          return v_a * v_a < v_b * v_b;
        return v_a % v_b > 0;
      });
      for (i32 i = 0; i < pnt.size(); ++i) {
        for (; ch.size() > 1;) {
          p_ prev_v = pnt[ch.back()].second - pnt[ch[ch.size() - 2]].second;
          p_ cur_v = pnt[i].second - pnt[ch.back()].second;
          if (prev_v % cur_v < 0) ch.pop_back();
          else break;
        }
        ch.push_back(i);
      }
      return ch;
    };
    for (i32 t = 1; pnt.size(); ++t) {
      vi32 ch = build_ch(pnt);
      si32 to_del;
      for (auto &&i : ch)
        res[pnt[i].first] = t, to_del.insert(i);
      vector<pair<i32, p_> > n_pnt;
      for (i32 i = 0; i < pnt.size(); ++i) {
        if (to_del.find(i) == to_del.end()) {
          n_pnt.push_back(pnt[i]);
        }
      }
      pnt = n_pnt;
    }
    cout << res << '\n';
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

