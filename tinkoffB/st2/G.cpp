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

struct event {
  i32 x1, x2, y1, y2;
  i32 ev;
  i32 ind;
};

struct st {
private:
  struct node {
    i32 val = 0;
  };
  vector<node> tr;
  i32 sz;
  void upd(i32 i, i32 x, i32 l, i32 r, i32 n) {
    if (l > i || r <= i)
      return;
    if (l == r - 1) {
      tr[n].val = x;
      return;
    }
    upd(i, x, l, (l + r) >> 1, n << 1);
    upd(i, x, (l + r) >> 1, r, n << 1 | 1);
    tr[n].val = std::min(tr[n << 1].val, tr[n << 1 | 1].val);
  }
  i32 get(i32 ql, i32 qr, i32 l, i32 r, i32 n) {
    if (l >= qr || r <= ql)
      return 1E9;
    if (ql <= l && r <= qr)
      return tr[n].val;
    return std::min(get(ql, qr, l, (l + r) >> 1, n << 1),
                    get(ql, qr, (l + r) >> 1, r, n << 1 | 1));
  }

public:
  st(i32 n) : sz{n} { tr.resize(4 * n); }
  void upd(i32 i, i32 x) { return upd(i, x, 0, sz, 1); }
  i32 get(i32 ql, i32 qr) { return get(ql, qr, 0, sz, 1); }
};

void solve() {
  i32 n, m, k, q;
  cin >> n >> m >> k >> q;
  vpi32 p(k);
  cin >> p;
  vector<event> evx, evy;
  for (i32 i = 0; i < q; ++i) {
    i32 x1, x2, y1, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    evx.push_back({x1, x2, y1 - 1, y2, 0, i});
    evy.push_back({y1, y2, x1 - 1, x2, 0, i});
  }
  for (auto &&[x, y] : p) {
    evx.push_back({x, x, y - 1, y - 1, 1, 0});
    evy.push_back({y, y, x - 1, x - 1, 1, 0});
  }
  auto comp = [](event const &lhs, event const &rhs) {
    if (lhs.x2 == rhs.x2)
      return lhs.ev > rhs.ev;
    return lhs.x2 < rhs.x2;
  };
  vb ans(q);
  std::sort(all(evx), comp);
  std::sort(all(evy), comp);
  st xtr(m), ytr(n);
  for (i32 i = 0; i < evx.size(); ++i) {
    if (evx[i].ev) {
      xtr.upd(evx[i].y1, evx[i].x1);
    } else {
      if (xtr.get(evx[i].y1, evx[i].y2) >= evx[i].x1) {
        ans[evx[i].ind] = 1;
      }
    }
  }
  for (i32 i = 0; i < evy.size(); ++i) {
    if (evy[i].ev) {
      ytr.upd(evy[i].y1, evy[i].x1);
    } else {
      if (ytr.get(evy[i].y1, evy[i].y2) >= evy[i].x1) {
        ans[evy[i].ind] = 1;
      }
    }
  }
  for (auto i : ans)
    i ? cout << "YES\n" : cout << "NO\n";
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