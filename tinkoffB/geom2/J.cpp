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

template <typename T> struct vector;
template <typename T> struct segment;
template <typename T> struct line;

/* declaration */
template <typename T> struct vector {
private:
  T x__, y__;

public:
  vector();
  vector(T x, T y);
  operator vector<long double>() const;
  T &x();
  T &y();
  long double abs();
  long double arg();
  vector<long double> rotate(long double angle) const;
  vector &operator+=(const vector &pnt);
  vector &operator-=(const vector &pnt);
  vector &operator*=(T q);
  vector operator-() const;
  vector operator+(const vector &pnt) const;
  vector operator-(const vector &pnt) const;
  vector operator*(T q) const;
  bool operator==(const vector &pnt) const;
  bool operator!=(const vector &pnt) const;
  T operator*(const vector &pnt) const; // Dot product
  T operator%(const vector &pnt) const; // Cross product
  long double operator^(const vector &pnt) const;

  friend struct segment<T>;
  friend struct line<T>;
};

template <typename T>
std::istream &operator>>(std::istream &is, vector<T> &pnt);

template <typename T> long double area(const std::vector<vector<T>> &shape);

/* implementation */
template <typename T> vector<T>::vector() : x__(0), y__(0) {}

template <typename T> vector<T>::vector(T x, T y) : x__(x), y__(y) {}

template <typename T> vector<T>::operator vector<long double>() const {
  return vector<long double>(static_cast<long double>(x__),
                             static_cast<long double>(y__));
}

template <typename T> T &vector<T>::x() { return x__; }

template <typename T> T &vector<T>::y() { return y__; }

template <typename T> long double vector<T>::abs() {
  return std::hypot(x__, y__);
}

template <typename T> long double vector<T>::arg() {
  return std::atan2(y__, x__);
}

template <typename T>
vector<long double> vector<T>::rotate(long double angle) const {
  vector<long double> res(*this);
  long double res_x, res_y;
  res_x = res.x__ * cos(angle) - res.y__ * sin(angle);
  res_y = res.x__ * sin(angle) + res.y__ * cos(angle);
  res.x__ = res_x;
  res.y__ = res_y;
  return res;
}

template <typename T> vector<T> &vector<T>::operator+=(const vector<T> &pnt) {
  x__ += pnt.x__, y__ += pnt.y__;
  return *this;
}
template <typename T> vector<T> &vector<T>::operator-=(const vector<T> &pnt) {
  x__ -= pnt.x__, y__ -= pnt.y__;
  return *this;
}

template <typename T> vector<T> &vector<T>::operator*=(T q) {
  x__ *= q, y__ *= q;
  return *this;
}

template <typename T> vector<T> vector<T>::operator-() const {
  return vector(*this) *= -1;
}

template <typename T> vector<T> vector<T>::operator+(const vector &pnt) const {
  return vector(*this) += pnt;
}
template <typename T> vector<T> vector<T>::operator-(const vector &pnt) const {
  return vector(*this) -= pnt;
}

template <typename T> vector<T> vector<T>::operator*(T q) const {
  return vector(*this) *= q;
}

template <typename T> bool vector<T>::operator==(const vector &pnt) const {
  return pnt.x__ == x__ && pnt.y__ == y__;
}

template <typename T> bool vector<T>::operator!=(const vector &pnt) const {
  return !(pnt == *this);
}

template <typename T> T vector<T>::operator*(const vector &pnt) const {
  return x__ * pnt.x__ + y__ * pnt.y__;
}

template <typename T> T vector<T>::operator%(const vector &pnt) const {
  return x__ * pnt.y__ - y__ * pnt.x__;
}

template <typename T> std::istream &operator>>(std::istream &is, vector<T> &A) {
  is >> A.x() >> A.y();
  return is;
}

template <typename T>
long double vector<T>::operator^(const vector<T> &rhs) const {
  return atan2(*this % rhs, *this * rhs);
}

template <typename T> long double area(const std::vector<vector<T>> &shape) {
  T S = 0;
  for (size_t i = 0; i < shape.size(); i++) {
    S += shape[i] % shape[(i + 1) % shape.size()];
  }
  return static_cast<long double>(std::abs(S)) / 2;
}

/* declaration */
template <typename T> struct segment {
private:
  vector<T> st__, end__;

public:
  segment();
  segment(const vector<T> &end);
  segment(const vector<T> &st, const vector<T> &end);
  operator segment<long double>() const;
  vector<T> &st();
  vector<T> &end();
  long double abs();
  long double arg();
  segment<long double> rotate(long double angle) const;
  segment &operator+=(const segment &seg);
  segment &operator-=(const segment &seg);
  segment &operator*=(T q);
  segment operator-() const;
  segment operator+(const segment &seg) const;
  segment operator-(const segment &seg) const;
  segment operator*(T q) const;
  bool operator==(const segment &seg) const;
  bool operator!=(const segment &seg) const;
  segment &operator+=(const vector<T> &pnt);
  segment &operator-=(const vector<T> &pnt);
  segment operator+(const vector<T> &pnt) const;
  segment operator-(const vector<T> &pnt) const;
  T operator*(const segment &seg) const;
  T operator%(const segment &seg) const;
  long double operator^(const segment &seg) const;

  friend struct line<T>;
};

/* impementaion */
template <typename T> segment<T>::segment() {}

template <typename T>
segment<T>::segment(const vector<T> &pnt) : st__(), end__(pnt) {}

template <typename T>
segment<T>::segment(const vector<T> &st, const vector<T> &end)
    : st__(st), end__(end) {}

template <typename T> segment<T>::operator segment<long double>() const {
  return segment<long double>(static_cast<vector<long double>>(st__),
                              static_cast<vector<long double>>(end__));
}

template <typename T> vector<T> &segment<T>::st() { return st__; }

template <typename T> vector<T> &segment<T>::end() { return end__; }

template <typename T> long double segment<T>::abs() {
  return (end__ - st__).abs();
}

template <typename T> long double segment<T>::arg() {
  return (end__ - st__).arg();
}

template <typename T>
segment<long double> segment<T>::rotate(long double angle) const {
  segment<long double> res(*this);
  res.end__ -= res.st__;
  res.end__ = res.end__.rotate(angle);
  res.end__ += res.st__;
  return res;
}

template <typename T> segment<T> &segment<T>::operator+=(const vector<T> &pnt) {
  st__ += pnt;
  end__ += pnt;
  return *this;
}

template <typename T>
segment<T> &segment<T>::operator+=(const segment<T> &seg) {
  vector<T> tEndSt = end__ - st__, tsegEndSt = seg.end__ - seg.st__;
  end__ = tEndSt + tsegEndSt + st__;
  return *this;
}

template <typename T> segment<T> &segment<T>::operator-=(const vector<T> &pnt) {
  st__ -= pnt, end__ -= pnt;
  return *this;
}

template <typename T>
segment<T> &segment<T>::operator-=(const segment<T> &seg) {
  vector<T> tEndSt = end__ - st__, tsegEndSt = seg.end__ - seg.st__;
  end__ = tEndSt - tsegEndSt + st__;
  return *this;
}

template <typename T> segment<T> &segment<T>::operator*=(T q) {
  end__ -= st__;
  end__ *= q;
  end__ += st__;
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

template <typename T> segment<T> segment<T>::operator*(T q) const {
  return segment(*this) *= q;
}

template <typename T> bool segment<T>::operator==(const segment<T> &seg) const {
  vector tEndSt = end__ - st__;
  vector tsegStEnd = seg.end__ - seg.st__;
  return tEndSt == tsegStEnd;
}

template <typename T> bool segment<T>::operator!=(const segment<T> &seg) const {
  return !(seg == *this);
}

template <typename T> T segment<T>::operator*(const segment<T> &seg) const {
  vector tEndSt = end__ - st__;
  vector tsegEndSt = seg.end__ - seg.st__;
  return tEndSt * tsegEndSt;
}

template <typename T> T segment<T>::operator%(const segment<T> &seg) const {
  vector tEndSt = end__ - st__;
  vector tsegEndSt = seg.end__ - seg.st__;
  return tEndSt % tsegEndSt;
}

template <typename T>
long double segment<T>::operator^(const segment<T> &seg) const {
  vector tEndStA = end__ - st__;
  vector tEndStB = seg.end__ - seg.st__;
  return tEndStA ^ tEndStB;
}

/* declaration */
template <typename T> struct line {
private:
  T A__, B__, C__;

public:
  line();
  line(T A, T B, T C);
  line(const vector<T> &norm);
  line(const vector<T> &p1, const vector<T> &p2);
  line(const segment<T> &seg);
  operator line<long double>() const;
  T &A();
  T &B();
  T &C();
  line norm() const;
  long double arg() const;
  line &operator&=(const vector<T> &p);
  line &operator&=(const segment<T> &seg);
  line operator&(const vector<T> &p) const;
  line operator&(const segment<T> &seg) const;
  vector<long double>
  operator&(const line &line) const;
  T operator()(const vector<T> &p) const;
};

/* implementation */
template <typename T> line<T>::line() : A__{0}, B__{0}, C__{0} {}

template <typename T> line<T>::line(T A, T B, T C) : A__{A}, B__{B}, C__{C} {}

template <typename T> line<T>::line(const vector<T> &norm): A__{norm.x__}, B__{norm.y__}, C__{0} {}

template <typename T> line<T>::line(const vector<T> &p1, const vector<T> &p2) {
  A__ = p1.y__ - p2.y__;
  B__ = p2.x__ - p1.x__;
  C__ = -(A__ * p1.x__ + B__ * p1.y__);
}

template <typename T>
line<T>::line(const segment<T> &seg) : line(seg.st__, seg.end__) {}

template <typename T> line<T>::operator line<long double>() const {
  return line<long double>(static_cast<long double>(A__),
                           static_cast<long double>(B__),
                           static_cast<long double>(C__));
}

template <typename T> T &line<T>::A() { return A__; }

template <typename T> T &line<T>::B() { return B__; }

template <typename T> T &line<T>::C() { return C__; }

template <typename T> line<T> line<T>::norm() const {
  return line(-B__, A__, 0);
}

template <typename T> long double line<T>::arg() const {
  return std::atan2(-A__, B__);
}

template <typename T> line<T> &line<T>::operator&=(const vector<T> &p) {
  C__ = -(A__ * p.x__ + B__ * p.y__);
  return *this;
}

template <typename T> line<T> &line<T>::operator&=(const segment<T> &seg) {
  return *this = line(seg);
}

template <typename T> line<T> line<T>::operator&(const vector<T> &p) const {
  return line(*this) &= p;
}

template <typename T> line<T> line<T>::operator&(const segment<T> &seg) const {
  return line(*this) &= seg;
}

template <typename T> T line<T>::operator()(const vector<T> &p) const {
  return A__ * p.x__ + B__ * p.y__ + C__;
}

template <typename T>
vector<long double> line<T>::operator&(const line &line) const {
  long double EPS = 1E-9;
  T det = A__ * line.B__ - B__ * line.A__;
  T det_x = -C__ * line.B__ + B__ * line.C__;
  T det_y = -line.C__ * A__ + line.A__ * C__;
  if (std::abs(det) < EPS) {
    return vector(std::numeric_limits<long double>::quiet_NaN(),
                  std::numeric_limits<long double>::quiet_NaN());
  }
  return vector(static_cast<long double>(det_x) / det,
                static_cast<long double>(det_y) / det);
}
} // namespace gpl

struct {
  using polygon = std::vector<gpl::vector<i64> >;
  using ray = gpl::segment<i64>;
  using segm = gpl::segment<i64>;
  using line = gpl::line<i64>;
  std::function<i64(void)> const rcoord = [] {
    return (ru64() % 2 ? -1 : 1) * (ru64() % 1000 + 1);
  };
  template <typename T> bool on_ray(ray &r, gpl::vector<T> &p) {
    f64 eps = 1e-9;
    return (p - r.st()) * (r.end() - r.st()) >= -eps;
  }
  bool is_intersect(ray &r, segm &s) {
    gpl::vector p_int = line(r) & line(s);
    ray s_se = ray(s.end(), s.st());
    ray s_es = ray(s.st(), s.end());
    return on_ray(s_es, p_int) && (on_ray(s_se, p_int))&& (on_ray(r, p_int));
  }
  i64 test(polygon &fig, gpl::vector<i64> p) {
    gpl::vector<i64> rand__{rcoord(), rcoord()};
    ray r{p, rand__};
    i32 i_count = 0;
    for (i32 i = 0; i < fig.size(); ++i) {
      segm s{fig[i], fig[(i + 1) % fig.size()]};
      i_count += is_intersect(r, s);
    }
    return i_count % 2;
  }
  void solve() {
    i64 n;
    gpl::vector<i64> p;
    cin >> n >> p;
    polygon fig(n);
    cin >> fig;
    for (i32 i = 0; i < n; ++i) {
      segm s(fig[i], fig[(i + 1) % n]);
      ray s_se = ray(s.st(), s.end());
      ray s_es = ray(s.end(), s.st());
      gpl::vector<i64> pe = p - s.end(), ps = p - s.st();
      if ((s.end() - s.st()) % (p - s.st()) == 0 && on_ray(s_es, ps) && on_ray(s_se, pe)) {
        cout << "YES\n";
        return;
      }
    }
    i64 prob = 0;
    for (i32 t = 0; t < 500; ++t) {
      prob += test(fig, p);
    }
    if (prob / 500.L > 0.1) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
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
  i32 t; cin >> t; for (i32 i = 0; i < t; i++)
#endif
  solution.solve();
#if REDIRECT__
  cin.close();
  cout.close();
#endif
  return 0;
} /* clang-format on *///

