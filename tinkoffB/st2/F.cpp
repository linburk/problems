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

struct mst {
private:
  struct node {
    vi64 val;
    vi64 pref_sum;
  };
  i32 sz;
  vector<node> tr;

private:
  void build(vi64 const &a, i32 l, i32 r, i32 n) {
    if (l == r - 1) {
      tr[n].val = {a[l]};
      tr[n].pref_sum = {0, a[l]};
      return;
    }
    build(a, l, (l + r) >> 1, n << 1);
    build(a, (l + r) >> 1, r, n << 1 | 1);
    std::merge(all(tr[n << 1].val), all(tr[n << 1 | 1].val),
               std::back_inserter(tr[n].val));
    tr[n].pref_sum.resize(tr[n].val.size() + 1);
    for (i32 i = 0; i < tr[n].val.size(); ++i) {
      tr[n].pref_sum[i + 1] = tr[n].pref_sum[i] + tr[n].val[i];
    }
  }
  i64 get(i32 ql, i32 qr, i64 k, i32 l, i32 r, i32 n) {
    if (l >= qr || r <= ql)
      return 0;
    if (ql <= l && r <= qr) {
      i32 c = static_cast<i32>(std::distance(
          tr[n].val.begin(), std::upper_bound(all(tr[n].val), k)));
      return tr[n].pref_sum[c];
    }
    return get(ql, qr, k, l, (l + r) >> 1, n << 1) +
           get(ql, qr, k, (l + r) >> 1, r, n << 1 | 1);
  }

public:
  mst(vi64 const &a) : sz{static_cast<i32>(a.size())} {
    tr.resize(4 * sz);
    build(a, 0, sz, 1);
  }
  i64 get(i32 ql, i32 qr, i64 k) { return get(ql, qr, k, 0, sz, 1); }
};

void solve() {
  i32 n, m;
  cin >> n >> m;
  vi64 a(n);
  cin >> a;
  mst tr(a);
  for (i32 i = 0; i < m; ++i) {
    i32 l, r;
    cin >> l >> r;
    i64 x = 0;
    for (;;) {
      i64 g = tr.get(l - 1, r, x + 1) - x;
      if (g <= 0)
        break;
      x += g;
    }
    cout << x + 1 << '\n';
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