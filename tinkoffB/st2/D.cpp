#include <bits/stdc++.h>
#include <climits>
namespace /* clang-format off */ {
#define all(cont) cont.begin(), cont.end()
namespace /* aliases */ {
using i8 = std::int8_t; using i16 = std::int16_t; using i32 = std::int32_t; using i64 = std::int64_t;
using u8 = std::uint8_t; using u16 = std::uint16_t; using u32 = std::uint32_t; using u64 = std::uint64_t; using f64 = long double; using f32 = float;
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

struct st {
private:
  static const i32 bit_sz = 21;
  struct node {
    i64 val = 0;
    vi64 bit_count;
    i64 xor_value = 0;
    node() { bit_count.resize(bit_sz); }
  };
  vector<node> tr;
  i32 sz;
  void pull(node &n, node &ls, node &rs, i32 l, i32 r) {
    i32 s = r - l;
    if (n.xor_value != 0) {
      n.val = 0;
      for (i64 i = 0; i < bit_sz; ++i) {
        if (n.xor_value & (1 << i))
          n.bit_count[i] = s - n.bit_count[i];
        n.val += (1 << i) * n.bit_count[i];
      }
      ls.xor_value ^= n.xor_value;
      rs.xor_value ^= n.xor_value;
      n.xor_value = 0;
    }
  }
  void merge(node &n, node &ls, node &rs) {
    n.val = ls.val + rs.val;
    for (i32 i = 0; i < bit_sz; ++i) {
      n.bit_count[i] = ls.bit_count[i] + rs.bit_count[i];
    }
  }

private:
  void build(vi32 const &a, i32 l, i32 r, i32 n) {
    if (l == r - 1) {
      tr[n].val = a[l];
      for (i32 i = 0; i < bit_sz; ++i) {
        if (a[l] & (1 << i))
          ++tr[n].bit_count[i];
      };
      return;
    }
    build(a, l, (l + r) >> 1, n << 1);
    build(a, (l + r) >> 1, r, n << 1 | 1);
    merge(tr[n], tr[n << 1], tr[n << 1 | 1]);
  }
  void xor_r(i32 ql, i32 qr, i32 x, i32 l, i32 r, i32 n) {
    pull(tr[n], tr[n << 1], tr[n << 1 | 1], l, r);
    if (l >= qr || r <= ql)
      return;
    if (ql <= l && r <= qr) {
      tr[n].xor_value ^= x;
      pull(tr[n], tr[n << 1], tr[n << 1 | 1], l, r);
      return;
    }
    xor_r(ql, qr, x, l, (l + r) >> 1, n << 1);
    xor_r(ql, qr, x, (l + r) >> 1, r, n << 1 | 1);
    merge(tr[n], tr[n << 1], tr[n << 1 | 1]);
  }
  i64 sum(i32 ql, i32 qr, i32 l, i32 r, i32 n) {
    pull(tr[n], tr[n << 1], tr[n << 1 | 1], l, r);
    if (l >= qr || r <= ql)
      return 0;
    if (ql <= l && r <= qr)
      return tr[n].val;
    return sum(ql, qr, l, (l + r) >> 1, n << 1) +
           sum(ql, qr, (l + r) >> 1, r, n << 1 | 1);
  }

public:
  st(vi32 const &a) : sz{static_cast<i32>(a.size())} {
    tr.resize(8 * sz);
    build(a, 0, sz, 1);
  }
  void xor_r(i32 ql, i32 qr, i32 x) { return xor_r(ql, qr, x, 0, sz, 1); }
  i64 sum(i32 ql, i32 qr) { return sum(ql, qr, 0, sz, 1); }
};

void solve() {
  i32 n;
  cin >> n;
  vi32 a(n);
  cin >> a;
  st tr(a);
  i32 m;
  cin >> m;
  for (i32 i = 0; i < m; ++i) {
    char c;
    cin >> c;
    if (c == '1') {
      i32 l, r;
      cin >> l >> r;
      cout << tr.sum(l - 1, r) << '\n';
    } else {
      i32 l, r, x;
      cin >> l >> r >> x;
      tr.xor_r(l - 1, r, x);
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