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
/* declaration */
template <typename T> struct vector { // (x, y)
  T x, y;
  vector();
  vector(int null);
  vector(T x, T y);
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

template <typename T> long double area(const std::vector<vector<T>> &shape);

/* implementation */
template <typename T> vector<T>::vector() {}

template <typename T> vector<T>::vector(int null) : x(0), y(0) {}

template <typename T> vector<T>::vector(T x, T y) : x(x), y(y) {}

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
  T S = 0;
  for (size_t i = 0; i < shape.size(); i++) {
    S += shape[i] % shape[(i + 1) % shape.size()];
  }
  return static_cast<long double>(std::abs(S)) / 2;
}

/* declaration */
template <typename T> struct segment { // (st, end)
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

/* impementaion */
template <typename T> segment<T>::segment() {}

template <typename T>
segment<T>::segment(const vector<T> &pnt) : st(0), end(pnt) {}

template <typename T>
segment<T>::segment(const vector<T> &st, const vector<T> &end)
    : st(st), end(end) {}

template <typename T> long double segment<T>::abs() {
  return (this->end - this->st).abs();
}

template <typename T> long double segment<T>::arg() {
  return st ^ end;
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
  return vec(*this) *= -1;
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
  vector tEndSt = end - st;
  vector tsegStEnd = seg.end - seg.st;
  return tEndSt == tsegStEnd;
}

template <typename T>
bool segment<T>::operator!=(const segment<T> &seg) const {
  return !(seg == (*this));
}

template <typename T> T segment<T>::operator*(const segment<T> &seg) const {
  vector tEndSt = end - st;
  vector tsegEndSt = seg.end - seg.st;
  return tEndSt * tsegEndSt;
}

template <typename T> T segment<T>::operator%(const segment<T> &seg) const {
  vector tEndSt = end - st;
  vector tsegEndSt = seg.end - seg.st;
  return tEndSt % tsegEndSt;
}

template <typename T>
long double segment<T>::operator^(const segment<T> &seg) const {
  vector tEndStA = this->end - this->st;
  vector tEndStB = seg.end - this->st;
  return tEndStA ^ tEndStB;
}

/* declaration */
template <typename T> struct line { // Ax + By + C
  T A, B, C;
  line() {}
  line(T A_, T B_, T C_);
  line(const vector<T> &p1, const vector<T> &p2);
  line(const segment<T> &seg);
  line norm() const;
  line& operator&=(const vector<T> &p);
  line& operator&=(const segment<T> &seg);
  line operator&(const vector<T> &p) const;
  line operator&(const segment<T> &seg) const;
  T operator()(const vector<T> &p) const;
};

template <typename T> vector<long double> intersect(const line<T> &l1, const line<T> &l2); // zero or more than 1 intersections -> return null vector

/* implementation */
template <typename T> line<T>::line(T A_, T B_, T C_): A{A_}, B{B_}, C{C_} {}

template <typename T> line<T>::line(const vector<T> &p1, const vector<T> &p2) {
  A = p1.y - p2.y;
  B = p2.x - p1.x;
  C = -(A * p1.x + B * p1.y);
}

template <typename T> line<T>::line(const segment<T> &seg): line(seg.st, seg.end) {}

template <typename T> line<T> line<T>::norm() const {
  return line(-B, A, 0);
}

template <typename T> line<T>& line<T>::operator&=(const vector<T> &p) {
  C = -(A * p.x + B * p.y);
  return *this;
}

template <typename T> line<T>& line<T>::operator&=(const segment<T> &seg) {
  line tmp(seg);
  A = tmp.A;
  B = tmp.B;
  C = tmp.C;
  return *this;
}

template <typename T> line<T> line<T>::operator&(const vector<T> &p) const {
  return line(*this) &= p;
}

template <typename T> line<T> line<T>::operator&(const segment<T> &seg) const {
  return line(*this) &= seg;
}

template <typename T> T line<T>::operator()(const vector<T> &p) const {
  return A * p.x + B * p.y + C;
}

template <typename T> vector<long double> intersect(const line<T> &l1, const line<T> &l2) {
  long double EPS = 1E-9;
  T det = l1.A * l2.B - l1.B * l2.A;
  T det_x = -l1.C * l2.B + l1.B * l2.C;
  T det_y = -l2.C * l1.A + l2.A * l1.C;
  if (det + EPS > 0 && det - EPS < 0) {
    return vector(std::numeric_limits<long double>::quiet_NaN(), std::numeric_limits<long double>::quiet_NaN());
  }
  return vector(static_cast<long double>(det_x) / det, static_cast<long double>(det_y) / det);
}
} // namespace gpl

struct {
  void solve() {
    gpl::vector<f64> p1, p2;
    f64 k; i64 b;
    cin >> p1 >> p2 >> k >> b;
    f64 A = k, B = -1, C = b;
    gpl::line<f64> line(A, B, C);
    if (line(p1) * line(p2) < 0) {
      cout << "No solution.\n";
      return;
    }
    gpl::vector<f64> m1 = gpl::intersect(line.norm() & p1, line), m2 = gpl::intersect(line.norm() & p2, line);
    f64 d1 = (p1 - m1).abs(), d2 = (p2 - m2).abs();
    f64 d12 = (m1 - m2).abs();
    f64 EPS = 1E-8;
    f64 l = -EPS, r = d12 + EPS;
    auto dist = [&] (f64 x) {
      return std::sqrt(d1 * d1 + x * x) + std::sqrt(d2 * d2 + (d12 - x) * (d12 - x));
    };
    for (i64 i = 0; i < 200; ++i) {
      f64 m1 = (2 * l + r) / 3;
      f64 m2 = (l + 2 * r) / 3;
      if (dist(m1) > dist(m2)) {
        l = m1;
      } else {
        r = m2;
      }
    }
    cout << std::setprecision(7) << std::fixed << dist(l) << '\n';
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

