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
using i8 = std::int8_t; using i16 = std::int16_t; using i32 = std::int32_t; using i64 = std::int64_t; using i128 = __int128;
using u8 = std::uint8_t; using u16 = std::uint16_t; using u32 = std::uint32_t; using u64 = std::uint64_t; using u128 = unsigned __int128; using f64 = long double; using f32 = float;
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
  i128 x, y;
  i128 abs() const { return (x * x + y * y); }
//  auto operator<=>(p_ const &rhs) const = default;
};
std::istream& operator>>(std::istream& is, p_ &rhs) {
  i64 x, y;
  is >> x >> y;
  rhs = {x, y};
  return is;
}
p_ operator-(p_ const &lhs, p_ const &rhs) {
  return {lhs.x - rhs.x, lhs.y - rhs.y};
}
p_ operator+(p_ const &lhs, p_ const &rhs) {
  return {lhs.x + rhs.x, lhs.y + rhs.y};
}
i64 operator%(p_ const &lhs, p_ const &rhs) {
  return lhs.x * rhs.y - lhs.y * rhs.x;
}
i64 operator*(p_ const &lhs, p_ const &rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y;
}
p_ operator*(p_ const &lhs, i64 k) {
  return {lhs.x * k, lhs.y * k};
}
bool operator!=(p_ const &lhs, p_ const &rhs) {
  return !(lhs.x == rhs.x && lhs.y == rhs.y);
}
bool operator<(p_ const &lhs, p_ const &rhs) {
  if (lhs.x == rhs.x) return lhs.y < rhs.y;
  return lhs.x < rhs.x;
}

struct l_ {
  i128 a, b, c;
  i128 operator()(p_ &p) {
    return a * p.x + b * p.y + c;
  }
};
std::istream& operator>>(std::istream& is, l_ &rhs) {
  i64 a, b, c;
  is >> a >> b >> c;
  rhs = {a, b, c};
  return is;
}

struct {
  vector<p_> build_ch(vector<p_> pnt) {
    vector<p_> hull;
    for (i32 i = 1; i < pnt.size(); ++i)
      if (pnt[i].x < pnt[0].x || (pnt[i].x == pnt[0].x && pnt[i].y < pnt[0].y))
        std::swap(pnt[i], pnt[0]);
    std::sort(pnt.begin() + 1, pnt.end(), [&pnt] (p_ &lhs, p_ &rhs) {
      p_ a = lhs - pnt[0], b = rhs - pnt[0];
      if (a % b == 0)
        return a.abs() < b.abs();
      return a % b > 0;
    });
    hull.push_back(pnt[0]);
    for (i32 i = 1; i < pnt.size(); ++i) {
      for (; hull.size() > 1;) {
        p_ pr_v = hull.back() - hull[hull.size() - 2];
        p_ cu_v = pnt[i] - hull.back();
        if (pr_v % cu_v <= 0) hull.pop_back();
        else break;
      }
      hull.push_back(pnt[i]);
    }
    return hull;
  }
  i32 const iters = 25;
  i128 max_dist(vector<p_> &ch, l_ ln, i64 l, i64 r) {
    for (; std::abs(r - l) > 2;) {
      i64 m1 = (l * 2 + r) / 3;
      i64 m2 = (l + 2 * r) / 3;
      ln(ch[m1 % ch.size()]) < ln(ch[m2 % ch.size()]) ? l = m1 : r = m2;
    }
    i128 res = -1E19;
    for (i32 i = -iters; i < iters; ++i) {
      res = std::max(res, ln(ch[(l + i + iters * ch.size()) % ch.size()]));
    }
    return res;
  }
  i128 min_dist(vector<p_> &ch, l_ ln, i64 l, i64 r) {
    for (; std::abs(r - l) > 2;) {
      i64 m1 = (l * 2 + r) / 3;
      i64 m2 = (l + 2 * r) / 3;
      ln(ch[m1 % ch.size()]) > ln(ch[m2 % ch.size()]) ? l = m1 : r = m2;
    }
    i128 res = 1E19;
    for (i32 i = -iters; i < iters; ++i) {
      res = std::min(res, ln(ch[(l + i + iters * ch.size()) % ch.size()]));
    }
    return res;
  }
  void solve() {
    i32 n, m;
    cin >> n >> m;
    vector<l_> ln(n);
    cin >> ln;
    vector<p_> pnt(m);
    vb intersect(n);
    cin >> pnt;
    auto ch = build_ch(pnt);
    i32 count = 0;
    for (i32 i = 0; i < n; ++i) {
      i128 max_d = -1E19, min_d = 1E19;
      for (i32 j = 1; j < 10; ++j) {
        i64 bord = ch.size() / 10 * j;
        i128 mxd1 = max_dist(ch, ln[i], 0, bord);
        i128 mxd2 = max_dist(ch, ln[i], bord, ch.size());
        i128 mid1 = min_dist(ch, ln[i], 0, bord);
        i128 mid2 = min_dist(ch, ln[i], bord, ch.size());
        max_d = std::max({mxd1, mxd2, max_d});
        min_d = std::min({mid1, mid2, min_d});
      }
      if (max_d * min_d <= 0)
        intersect[i] = 1, ++count;
      else {
        i32 d = 0;
      }
    }
    cout << count << '\n';
    for (i32 i = 0; i < n; ++i) {
      if (intersect[i]) {
        cout << i + 1 << ' ';
      }
    }
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

