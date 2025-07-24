#include <bits/stdc++.h>
#include <climits>

#define LOCAL__ 1 && __APPLE__
#define REDIRECT__ 1 && __APPLE__
#define PRECALCULATE__ 0
#define MULTITEST__ 0

namespace /* clang-format off */ {
#define all(cont) cont.begin(), cont.end()
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

namespace gpl {
template <typename T> struct vector {
  T x, y;
  vector();
  vector(int null);
  vector(const T x, const T y);
  long double abs();
  long double arg();
  vector operator-();
  vector &operator+=(const vector &pnt);
  vector &operator-=(const vector &pnt);
  vector &operator*=(long double q);
  vector operator+(const vector &pnt) const;
  vector operator-(const vector &pnt) const;
  vector operator*(long double q) const;
  bool operator==(const vector &pnt) const;
  bool operator!=(const vector &pnt) const;
  T operator*(const vector &pnt) const; // Dot product
  T operator%(const vector &pnt) const; // Cross product
  long double operator^(const vector &pnt) const;
};

template <typename T> std::istream &operator>>(std::istream &is, vector<T> &pnt);

template <typename T>
long double abs(const vector<T> &pntA, const vector<T> &pntB);

template <typename T> long double area(const std::vector<vector<T>> &shape);

template <typename T> struct segment {
  vector<T> st, end;
  segment();
  segment(const vector<T> &end);
  segment(const vector<T> &st, const vector<T> &end);
  long double abs();
  long double arg();
  void rotate(long double angle);
  segment &operator+=(const segment &seg);
  segment &operator-=(const segment &seg);
  segment &operator*=(long double q);
  segment operator-() const;
  segment operator+(const segment &seg) const;
  segment operator-(const segment &seg) const;
  segment operator*(long double q) const;
  bool operator==(const segment &seg) const;
  bool operator!=(const segment &seg) const;
  segment &operator+=(const vector<T> &pnt);
  segment &operator-=(const vector<T> &pnt);
  segment operator+(const vector<T> &pnt) const;
  segment operator-(const vector<T> &pnt) const;
  T operator*(const segment &seg) const;
  T operator%(const segment &seg) const;
  long double operator^(const segment &seg) const;
};

template <typename T> vector<T>::vector() {}

template <typename T> vector<T>::vector(int null) : x(0), y(0) {}

template <typename T> vector<T>::vector(const T x, const T y) : x(x), y(y) {}

template <typename T> long double vector<T>::abs() {
  return std::hypot(x, y);
}

template <typename T> long double vector<T>::arg() {
  return std::atan2(y, x);
}

template <typename T> vector<T> vector<T>::operator-() {
  return vector(-(this->x), -(this->y));
}

template <typename T> vector<T> &vector<T>::operator+=(const vector<T> &pnt) {
  x += pnt.x, y += pnt.y;
  return *this;
}
template <typename T> vector<T> &vector<T>::operator-=(const vector<T> &pnt) {
  x -= pnt.x, y -= pnt.y;
  return *this;
}

template <typename T> vector<T> &vector<T>::operator*=(long double q) {
  x *= q, y *= q;
  return *this;
}

template <typename T>
vector<T> vector<T>::operator+(const vector &pnt) const {
  return vector(*this) += pnt;
}
template <typename T>
vector<T> vector<T>::operator-(const vector &pnt) const {
  return vector(*this) -= pnt;
}

template <typename T> vector<T> vector<T>::operator*(long double q) const {
  return vector(*this) *= q;
}

template <typename T> bool vector<T>::operator==(const vector &pnt) const {
  return (pnt.x == (this->x) && pnt.y == (this->y));
}

template <typename T> bool vector<T>::operator!=(const vector &pnt) const {
  return !(pnt == *this);
}

template <typename T> T vector<T>::operator*(const vector &pnt) const {
  return (this->x) * pnt.x + (this->y) * pnt.y;
}

template <typename T> T vector<T>::operator%(const vector &pnt) const {
  return (this->x) * pnt.y - (this->y) * pnt.x;
}

template <typename T> std::istream &operator>>(std::istream &is, vector<T> &A) {
  is >> A.x >> A.y;
  return is;
}

template <typename T>
long double vector<T>::operator^(const vector<T> &rhs) const {
  return atan2((*this) % rhs, (*this) * rhs);
}

template <typename T> long double area(const std::vector<vector<T>> &shape) {
  long long S = 0;
  for (size_t i = 0; i < shape.size(); i++) {
    S += shape[i] % shape[(i + 1) % shape.size()];
  }
  return (long double)std::abs(S) / 2;
}

template <typename T> segment<T>::segment() {}

template <typename T>
segment<T>::segment(const vector<T> &pnt) : st(0), end(pnt) {}

template <typename T>
segment<T>::segment(const vector<T> &pntA, const vector<T> &pntB)
    : st(pntA), end(pntB) {}

template <typename T> long double segment<T>::abs() {
  return (this->end - this->st).abs();
}

template <typename T> long double segment<T>::arg() {
  return (end - st).arg();
}

template <typename T> void segment<T>::rotate(long double angle) {
  long double newX, newY;
  end -= st;
  newX = end.x * cos(angle) - end.y * sin(angle);
  newY = end.x * sin(angle) + end.y * cos(angle);
  end.x = newX;
  end.y = newY;
  end += st;
}

template <typename T> segment<T> &segment<T>::operator+=(const vector<T> &pnt) {
  st += pnt;
  end += pnt;
  return *this;
}

template <typename T>
segment<T> &segment<T>::operator+=(const segment<T> &seg) {
  vector<T> tEndSt = end - st, tsegEndSt = seg.end - seg.st;
  end = tEndSt + tsegEndSt + st;
  return *this;
}

template <typename T> segment<T> &segment<T>::operator-=(const vector<T> &pnt) {
  st -= pnt, end -= pnt;
  return *this;
}
template <typename T>
segment<T> &segment<T>::operator-=(const segment<T> &seg) {
  vector<T> tEndSt = end - st, tsegEndSt = seg.end - seg.st;
  end = tEndSt - tsegEndSt + st;
  return *this;
}

template <typename T> segment<T> &segment<T>::operator*=(long double q) {
  end -= st;
  end *= q;
  end += st;
  return *this;
}

template <typename T> segment<T> segment<T>::operator-() const {
  return segment(*this) *= -1;
}

template <typename T>
segment<T> segment<T>::operator+(const vector<T> &pnt) const {
  return segment(*this) += pnt;
}

template <typename T>
segment<T> segment<T>::operator+(const segment<T> &seg) const {
  return segment(*this) += seg;
}

template <typename T>
segment<T> segment<T>::operator-(const vector<T> &pnt) const {
  return segment(*this) -= pnt;
}

template <typename T>
segment<T> segment<T>::operator-(const segment<T> &seg) const {
  return segment(*this) -= seg;
}

template <typename T>
segment<T> segment<T>::operator*(long double q) const {
  return segment(*this) *= q;
}

template <typename T>
bool segment<T>::operator==(const segment<T> &seg) const {
  const vector tEndSt = end - st;
  const vector tsegStEnd = seg.end - seg.st;
  return tEndSt == tsegStEnd;
}

template <typename T>
bool segment<T>::operator!=(const segment<T> &seg) const {
  return !(seg == (*this));
}

template <typename T> T segment<T>::operator*(const segment<T> &seg) const {
  const vector tEndSt = end - st;
  const vector tsegEndSt = seg.end - seg.st;
  return tEndSt * tsegEndSt;
}

template <typename T> T segment<T>::operator%(const segment<T> &seg) const {
  const vector tEndSt = end - st;
  const vector tsegEndSt = seg.end - seg.st;
  return tEndSt % tsegEndSt;
}

template <typename T>
long double segment<T>::operator^(const segment<T> &seg) const {
  const vector tEndStA = this->end - this->st;
  const vector tEndStB = seg.end - this->st;
  return tEndStA ^ tEndStB;
}

} // namespace gpl

struct {
  template<typename T> bool on_the_segment(gpl::vector<T> a, gpl::vector<T> b, gpl::vector<T> v) {
    return (a - b) * (v - b) >= 0 && (b - a) * (v - a) >= 0;
  }
  void solve() {
    gpl::vector<i64> a, b, c, d;
    cin >> a >> b >> c >> d;
    i64 A_ab = -(a - b).y, B_ab = (a - b).x;
    i64 A_cd = -(c - d).y, B_cd = (c - d).x;
    i64 C_ab = A_ab * a.x + B_ab * a.y;
    i64 C_cd = A_cd * c.x + B_cd * c.y;
    
    i64 det = A_ab * B_cd - B_ab * A_cd;
    i64 det_x = C_ab * B_cd - B_ab * C_cd;
    i64 det_y = A_ab * C_cd - C_ab * A_cd;
    cout << std::setprecision(8) << std::fixed;
    if (a == b && c == d) {
      if (a == c) {
        cout << a.x << " " << a.y << "\n";
      } else {
        cout << "Empty\n";
      }
      return;
    }
    if (a == b) {
      if (on_the_segment(c, d, a) && (c - d) % (a - d) == 0) {
        cout << a.x << " " << a.y << "\n";
      } else {
        cout << "Empty\n";
      }
      return;
    }
    if (c == d) {
      if (on_the_segment(a, b, c) && (a - b) % (c - b) == 0) {
        cout << c.x << " " << c.y << "\n";
      } else {
        cout << "Empty\n";
      }
      return;
    }
    if (det == 0) {
      if (det_x == 0 && det_y == 0) {
        std::vector<gpl::vector<i64> > ans;
        std::vector<gpl::vector<i64> > p_b{a, b, c, d};
        for (auto v : p_b) {
          if (on_the_segment(a, b, v) && on_the_segment(c, d, v)) {
            ans.push_back(v);
          }
        }
        if (ans.size() == 0) {
          cout << "Empty\n";
          return;
        }
        std::sort(all(ans), [] (gpl::vector<i64> &lhs, gpl::vector<i64> &rhs) {
          return (lhs.x == rhs.x ? lhs.y < rhs.y : lhs.x < rhs.x);
        } );
        unique(ans);
        for (auto [x, y] : ans) {
          cout << x << " " << y << "\n";
        }
      } else {
        cout << "Empty\n";
      }
    } else {
      gpl::vector<f64> a_f(a.x, a.y);
      gpl::vector<f64> b_f(b.x, b.y);
      gpl::vector<f64> c_f(c.x, c.y);
      gpl::vector<f64> d_f(d.x, d.y);
      gpl::vector<f64> m(det_x / 1. / det, det_y / 1. / det);
      if (on_the_segment(a_f, b_f, m) && on_the_segment(c_f, d_f, m)) {
        cout << m.x << " " << m.y << "\n";
      } else {
        cout << "Empty\n";
      }
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
