#include <bits/stdc++.h>
#include <climits>
namespace /* clang-format off */ {
namespace /* aliases */ {
#define all(cont) cont.begin(), cont.end()
using i8 = std::int8_t; using i16 = std::int16_t; using i32 = std::int32_t; using i64 = std::int64_t;
using u8 = std::uint8_t; using u16 = std::uint16_t; using u32 = std::uint32_t; using u64 = std::uint64_t; using f64 = long double;
using pi32 = std::pair<i32, i32>; using vpi32 = std::vector<pi32>; using vvpi32 = std::vector<vpi32>; using pi64 = std::pair<i64, i64>;  using vpi64 = std::vector<pi64>; using vvpi64 = std::vector<vpi64>;
using vi32 = std::vector<i32>; using vvi32 = std::vector<vi32>; using vi64 = std::vector<i64>; using vvi64 = std::vector<vi64>;
using vb = std::vector<bool>; using vvb = std::vector<vb>; using vc = std::vector<char>; using vvc = std::vector<vc>;
using si32 = std::set<i32>; using spi32 = std::set<pi32>; using si64 = std::set<i64>; using spi64 = std::set<pi64>;
using mpi32 = std::map<i32, i32>; using umpi32 = std::unordered_map<i32, i32>; using mpi64 = std::map<i64, i64>;  using umpi64 = std::unordered_map<i64, i64>;
}
namespace /* in/out op. overloadings */ {
template <typename T, typename V> std::istream &operator>>(std::istream &is, std::pair<T, V> &p) { is >> p.first >> p.second; return is; }
template <typename T> std::istream &operator>>(std::istream &is, std::vector<T> &cont) { for (auto &i : cont) { is >> i; } return is; }
template <typename T, typename V, char SEP1 = ' ', char SEP2 = '\n'> std::ostream &operator<<(std::ostream &os, std::pair<T, V> const &p) { os << p.first << SEP1 << p.second << SEP2; return os; }
template <typename T, char SEP1 = ' ', char SEP2 = '\n'> std::ostream &operator<<(std::ostream &os, const std::vector<T> &cont) { for (const auto &i : cont) { os << i; if (SEP1) os << SEP1; } os << SEP2; return os; }
}
namespace /* functions */ {
#if __cplusplus >= 202002L
template <char SEP = ' '> void debug(auto&&...args) { ((std::cout << args << SEP), ...); std::cout << "\n"; }
#endif
template <typename T> void inline unique(std::vector<T> &cont) { cont.erase(std::unique(cont.begin(), cont.end()), cont.end()); }
std::mt19937_64 randu64(std::chrono::steady_clock().now().time_since_epoch().count());
}
using std::vector, std::string, std::pair, std::cin, std::cout;
} /* clang-format on */
#define REDIRECT 1 && __APPLE__
#define MULTITEST 0

struct event {
  i64 y1, y2;
  i64 x;
  i64 type;
};

class st final {
  struct node {
    i64 min = 0;
    i64 lazy = 0;
    i64 segm = 0;
  };
  vector<node> tr;
  i32 sz;
  void relax(node &n, node const &ls, node const &rs) {
    if (ls.min + ls.lazy == rs.min + rs.lazy) {
      n.min = ls.min + ls.lazy;
      n.segm = ls.segm + rs.segm;
    } else if (ls.min + ls.lazy < rs.min + rs.lazy) {
      n.min = ls.min + ls.lazy;
      n.segm = ls.segm;
    } else {
      n.min = rs.min + rs.lazy;
      n.segm = rs.segm;
    }
  }
  void build(vi64 const &a, i32 l, i32 r, i32 n) {
    if (l == r - 1)
      return static_cast<void>(tr[n].segm = a[l]);
    build(a, l, (l + r) >> 1, n << 1);
    build(a, (l + r) >> 1, r, n << 1 | 1);
    relax(tr[n], tr[n << 1], tr[n << 1 | 1]);
  }
  void update(i32 ql, i32 qr, i32 val, i32 l, i32 r, i32 n) {
    if (l >= qr || r <= ql)
      return;
    if (ql <= l && r <= qr)
      return static_cast<void>(tr[n].lazy += val);
    update(ql, qr, val, l, (l + r) >> 1, n << 1);
    update(ql, qr, val, (l + r) >> 1, r, n << 1 | 1);
    relax(tr[n], tr[n << 1], tr[n << 1 | 1]);
  }
  node get(i32 ql, i32 qr, i32 l, i32 r, i32 n) {
    if (l >= qr || r <= ql)
      return {0, 0, 0};
    if (ql <= l && r <= qr)
      return tr[n];
    node L = get(ql, qr, l, (l + r) >> 1, n << 1);
    node R = get(ql, qr, (l + r) >> 1, r, n << 1 | 1);
    node Re;
    relax(Re, L, R);
    return Re;
  }

public:
  st(vi64 const &a) : sz{static_cast<i32>(a.size())} {
    tr.resize(4 * sz);
    build(a, 0, sz, 1);
  }
  void add(i32 ql, i32 qr, i32 val) { return update(ql, qr, val, 0, sz, 1); }
  i64 get() { return tr[1].segm; }
};

void solve() {
  i32 n;
  cin >> n;
  if (n == 0) {
    cout << 0;
    return;
  }
  vector<event> events;
  vi64 all_y;
  for (i32 i = 0; i < n; ++i) {
    i64 x1, x2, y1, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    events.push_back({y1, y2, x1, 1});
    events.push_back({y1, y2, x2, -1});
    all_y.push_back(y1);
    all_y.push_back(y2);
  }
  std::sort(all(events),
            [](event const &lhs, event const &rhs) { return lhs.x < rhs.x; });
  std::sort(all(all_y));
  unique(all_y);
  mpi64 y_match;
  for (i32 i = 0; i < all_y.size(); ++i)
    y_match[all_y[i]] = i;
  vi64 diff_y(2 * all_y.size());
  for (i32 i = 0; i < all_y.size() - 1; ++i) {
    diff_y[i] = all_y[i + 1] - all_y[i];
  }
  st tr(diff_y);
  i64 res =
      (events.back().x - events.front().x) * (all_y.back() - all_y.front());
  for (i32 i = 0; i < events.size(); ++i) {
    if (i)
      res -= tr.get() * (i64)(events[i].x - events[i - 1].x);
    i64 my1 = y_match[events[i].y1], my2 = y_match[events[i].y2];
    tr.add(my1, my2, events[i].type);
  }
  cout << res << '\n';
}

#define PRECALCULATE 0
void precalc();
i32 main(i32 argc, char *argv[]) /* clang-format off */ {
    std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false); setlocale(LC_ALL, "Russian");
#if REDIRECT
    std::freopen("/Users/dmitrii/Documents/Code/Code/input.txt", "r", stdin);
    std::freopen("/Users/dmitrii/Documents/Code/Code/output.txt", "w", stdout);
#endif
#if PRECALCULATE
    precalc();
#endif
#if MULTITEST
    i32 t; std::cin >> t; for (i32 i = 0; i < t; i++)
#endif
    solve();
    return 0;
} /* clang-format on */