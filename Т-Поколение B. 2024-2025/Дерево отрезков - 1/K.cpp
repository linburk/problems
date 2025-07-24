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

class st final {
private:
  struct node {
    i32 open;
    i32 close;
    i32 non_used_open;
    i32 non_used_close;
    i32 val;
  };
  void combine(node &n, node const &ls, node const &rs) {
    n.open = ls.open + rs.open;
    n.close = ls.close + rs.close;
    i32 add = std::min(ls.non_used_open, rs.non_used_close);
    n.non_used_open = rs.non_used_open + ls.non_used_open - add;
    n.non_used_close = ls.non_used_close + rs.non_used_close - add;
    n.val = ls.val + rs.val + 2 * add;
  }
  void build(string const &str, i32 l, i32 r, i32 n) {
    if (l == r - 1) {
      tr[n] = {str[l] == '(', str[l] == ')', str[l] == '(', str[l] == ')', 0};
      return;
    }
    build(str, l, (l + r) >> 1, n << 1);
    build(str, (l + r) >> 1, r, n << 1 | 1);
    combine(tr[n], tr[n << 1], tr[n << 1 | 1]);
  }
  node get(i32 ql, i32 qr, i32 l, i32 r, i32 n) {
    if (l >= qr || r <= ql)
      return {0, 0, 0};
    if (ql <= l && r <= qr)
      return tr[n];
    node L = get(ql, qr, l, (l + r) >> 1, n << 1);
    node R = get(ql, qr, (l + r) >> 1, r, n << 1 | 1);
    node Res;
    combine(Res, L, R);
    return Res;
  }

private:
  vector<node> tr;
  i32 sz;

public:
  st(string const &str) : sz(static_cast<i32>(str.size())) {
    tr.resize(4 * sz);
    build(str, 0, sz, 1);
  }
  i32 get(i32 ql, i32 qr) { return get(ql, qr, 0, sz, 1).val; }
};

void solve() {
  string str;
  cin >> str;
  i32 m;
  cin >> m;
  st tr(str);
  for (i32 i = 0; i < m; ++i) {
    i32 l, r;
    cin >> l >> r;
    cout << tr.get(l - 1, r) << '\n';
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