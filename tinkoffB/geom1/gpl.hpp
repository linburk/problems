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

/* impementation */
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
