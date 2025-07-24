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
  operator p_<f64>() { return p_<f64>{static_cast<f64>(x), static_cast<f64>(y)}; }
};
template <class T> std::ostream& operator<<(std::ostream& os, p_<T> const &rhs) {
  os << "(" << rhs.x << ", " << rhs.y << ")";
  return os;
}
template <class T> std::istream& operator>>(std::istream& is, p_<T> &rhs) {
  is >> rhs.x >> rhs.y;
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
  vector<p_<i64> > build_ch(vector<p_<i64> > &pnt) {
    vector<p_<i64> > hull;
    for (i32 i = 1; i < pnt.size(); ++i)
      if (pnt[i].x < pnt[0].x || (pnt[i].x == pnt[0].x && pnt[i].y < pnt[0].y))
        std::swap(pnt[0], pnt[i]);
    std::sort(pnt.begin() + 1, pnt.end(), [&pnt] (p_<i64> const &lhs, p_<i64> const &rhs) {
      p_ a = lhs - pnt[0], b = rhs - pnt[0];
      if (a % b == 0)
        return a * a < b * b;
      return a % b > 0;
    });
    hull.push_back(pnt[0]);
    for (i32 i = 0; i < pnt.size(); ++i) {
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
  i64 area(vi64 &pref_ar, vector<p_<i64> > &pnt, i32 l_ind, i32 r_ind) {
    i64 res = pnt[r_ind] % pnt[l_ind];
    if (r_ind < l_ind) {
      res += pref_ar[pnt.size()] - pref_ar[l_ind];
      res += pref_ar[r_ind];
    } else {
      res += pref_ar[r_ind] - pref_ar[l_ind];
    }
    return std::abs(res);
  }
  i32 find_tg(vector<p_<i64> > &p_hull, p_<i64> p, i32 l, i32 r) {
    bool rotate = std::signbit((p_hull[l] - p) % (p_hull[(l + 1) % p_hull.size()] - p_hull[l]));
    for (; r - l > 1;) {
      i32 m = (l + r) / 2;
      rotate == std::signbit((p_hull[m] - p) % (p_hull[(m + 1) % p_hull.size()] - p_hull[m])) ? l = m : r = m;
    }
    return r % p_hull.size();
  }
  pair<p_<i64>, p_<i64> > tangent(vector<p_<i64> > &p_hull, p_<i64> p) {
    p_<i64> res[2];
    i32 bord = [&p_hull, &p] {
      i32 l = 0, r = static_cast<i32>(p_hull.size()) + 1;
      bool rotate = std::signbit((p_hull[0] - p) % (p_hull[1] - p));
      for (; r - l > 1;) {
        i32 m = (l + r) >> 1;
        rotate == std::signbit((p_hull[0] - p) % (p_hull[m % p_hull.size()] - p)) ? l = m : r = m;
      }
      return l;
    }() % p_hull.size();
    i32 tg_1 = find_tg(p_hull, p, 0, bord);
    i32 tg_2 = find_tg(p_hull, p, bord, static_cast<i32>(p_hull.size()));
    res[0] = p_hull[tg_1];
    res[1] = p_hull[tg_2];
    return {res[0], res[1]};
  }
  void solve() {
    i32 n;
    cin >> n;
    vector<p_<i64> > pnt(n);
    cin >> pnt;
#if 1
    i32 m;
    cin >> m;
    vector<p_<i64> > pepper(m);
    cin >> pepper;
    vector<p_<i64> > p_hull = build_ch(pepper);
    vi64 pref_ar(n + 1);
    for (i32 i = 0; i < n; ++i)
      pref_ar[i + 1] = pref_ar[i] + pnt[i] % pnt[(i + 1) % n];
    i64 res = 0;
    for (i32 i = 0; i < n; ++i) {
      auto p = tangent(p_hull, pnt[i]);
//      print(pnt[i], "\n", p, "\n\n");
      i32 l = 0, r = n;
      for (; r - l > 1;) {
        i32 m = (l + r) >> 1;
        (p.first - pnt[i]) % (pnt[(i + m) % n] - pnt[i]) < 0
        &&
        (p.second - pnt[i]) % (pnt[(i + m) % n] - pnt[i]) < 0
        ? l = m : r = m;
      }
      res = std::max(res, area(pref_ar, pnt, i, (i + l) % n));
    }
    cout << res << '\n';
#else
    p_<i64> p;
    cin >> p;
    auto tg = tangent(pnt, p);
    print(tg);
#endif
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

