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
    i64 val = 0;
    i64 lazy = 0;
    i64 d = 0;
  };
  vector<node> tr;
  i32 sz;
  void relax(node &n, node const &ls, node const &rs, i32 l, i32 r) {
    i32 m = (l + r) >> 1;
    n.val = 0;
    n.val += ls.val + ls.lazy * (m - l) + progression(0, (m - l), ls.d);
    n.val += rs.val + rs.lazy * (r - m) + progression(0, (r - m), rs.d);
  }
  i64 progression(i64 a1, i64 len, i64 d) {
    return (2 * a1 + (len - 1) * d) * len / 2;
  }
  void add(i32 ql, i32 qr, i64 val, i32 l, i32 r, i32 n) {
    if (l >= qr || r <= ql)
      return;
    if (ql <= l && r <= qr)
      return static_cast<void>(tr[n].lazy += val);
    add(ql, qr, val, l, (l + r) >> 1, n << 1);
    add(ql, qr, val, (l + r) >> 1, r, n << 1 | 1);
    relax(tr[n], tr[n << 1], tr[n << 1 | 1], l, r);
  }
  void add_progression(i32 ql, i32 qr, i64 d, i32 l, i32 r, i32 n) {
    if (l >= qr || r <= ql)
      return;
    if (ql <= l && r <= qr)
      return static_cast<void>(tr[n].d += d, tr[n].lazy += d * (l - ql));
    add_progression(ql, qr, d, l, (l + r) >> 1, n << 1);
    add_progression(ql, qr, d, (l + r) >> 1, r, n << 1 | 1);
    relax(tr[n], tr[n << 1], tr[n << 1 | 1], l, r);
  }
  i64 get(i32 ql, i32 qr, i32 l, i32 r, i32 n) {
    if (l >= qr || r <= ql)
      return 0;
    if (ql <= l && r <= qr)
      return tr[n].val + tr[n].lazy * (r - l) +
             progression(0, (r - l), tr[n].d);
    i64 L = get(ql, qr, l, (l + r) >> 1, n << 1);
    i64 R = get(ql, qr, (l + r) >> 1, r, n << 1 | 1);
    i32 intersection_len = std::min(qr, r) - std::max(ql, l);
    i64 a1 = std::max(0, (ql - l)) * tr[n].d;
    return L + R + tr[n].lazy * intersection_len +
           progression(a1, intersection_len, tr[n].d);
  }

public:
  st(i32 n) : sz{n} { tr.resize(4 * sz); }
  i64 get(i32 ql, i32 qr) { return get(ql, qr, 0, sz, 1); }
  void add_progression(i32 ql, i32 qr, i32 d) {
    return add_progression(ql, qr, d, 0, sz, 1);
  }
  void add(i32 ql, i32 qr, i32 val) { return add(ql, qr, val, 0, sz, 1); }
};

void solve() {
  i32 n, m;
  cin >> n >> m;
  st tr(n);
  for (i32 i = 0; i < m; ++i) {
    char c;
    cin >> c;
    //        cout << c << "\n";
    if (c == '?') {
      i32 l, r;
      cin >> l >> r;
      cout << tr.get(l - 1, r) << '\n';
    }
    if (c == 'R') {
      i32 x, q;
      cin >> x >> q;
      --x;
      tr.add(std::max(0, x - q + 1), x + 1, std::max(0, q - x));
      //            for (i32 i = 0; i < n; ++i) {
      //                cout << tr.get(i, i+1) << " ";
      //            } cout << "\n";
      tr.add_progression(std::max(0, x - q), x + 1, 1);
      //            for (i32 i = 0; i < n; ++i) {
      //                cout << tr.get(i, i+1) << " ";
      //            } cout << "\n";
      tr.add(x + 1, std::min(n, x + q), q - 1);
      //            for (i32 i = 0; i < n; ++i) {
      //                cout << tr.get(i, i+1) << " ";
      //            } cout << "\n";
      tr.add_progression(x + 1, std::min(n, x + q), -1);
      //            for (i32 i = 0; i < n; ++i) {
      //                cout << tr.get(i, i+1) << " ";
      //            } cout << "\n\n";
    }
    if (c == 'C') {
      i32 l, r, x;
      cin >> l >> r >> x;
      tr.add(l - 1, r, -x);
      //            for (i32 i = 0; i < n; ++i) {
      //                cout << tr.get(i, i+1) << " ";
      //            } cout << "\n\n";
    }
  }
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