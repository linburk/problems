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
  struct node {
    i64 val = 0, lazy = 0;
    i32 ls = 0, rs = 0;
  };
  vector<node> tr;
  i64 sz;

private:
  void add(i64 ql, i64 qr, i64 val, i64 l, i64 r, i64 n) {
    if (l >= qr || r <= ql)
      return;
    if (ql <= l && r <= qr) {
      tr[n].lazy += val, tr[n].val += val;
      return;
    }
    if (std::min((l + r) >> 1, qr) - std::max(ql, l) > 0) {
      if (!tr[n].ls) {
        tr[n].ls = static_cast<i32>(tr.size());
        tr.push_back(node{});
      }
      add(ql, qr, val, l, (l + r) >> 1, tr[n].ls);
    }
    if (std::min(r, qr) - std::max(ql, (l + r) >> 1) > 0) {
      if (!tr[n].rs) {
        tr[n].rs = static_cast<i32>(tr.size());
        tr.push_back(node{});
      }
      add(ql, qr, val, (l + r) >> 1, r, tr[n].rs);
    }
    tr[n].val = std::max(tr[tr[n].ls].val, tr[tr[n].rs].val) + tr[n].lazy;
  }
  i64 get(i64 ql, i64 qr, i64 l, i64 r, i64 n) {
    if (l >= qr || r <= ql || n == 0)
      return 0ll;
    if (ql <= l && r <= qr)
      return tr[n].val;
    return tr[n].lazy + std::max(get(ql, qr, l, (l + r) >> 1, tr[n].ls),
                                 get(ql, qr, (l + r) >> 1, r, tr[n].rs));
  }

public:
  st(i64 n) : sz{n} { tr.resize(2); }
  void add(i64 ql, i64 qr, i64 val) { return add(ql, qr, val, 0, sz, 1); }
  i64 get(i64 ql, i64 qr) { return get(ql, qr, 0, sz, 1); }
};

struct point {
  i64 x, y;
  i32 id;
};

void solve() {
  i64 h, w, n;
  cin >> w >> h >> n;
  h *= 2, w *= 2;
  vector<point> points(n);
  for (i32 i = 0; i < n; ++i) {
    f64 x, y;
    cin >> x >> y;
    points[i].x = x * 2;
    points[i].y = y * 2;
    points[i].id = i;
  }
  st tr(w + 1);
  std::sort(all(points), [](point const &lhs, point const &rhs) -> bool {
    return lhs.y < rhs.y;
  });
  vi64 ans(n);
  auto borders = [&](i64 x1, i64 y1, i64 x2, i64 y2) -> bool {
    return x1 < 0 || x1 >= w || y1 < 0 || y1 >= h || x2 < 0 || x2 >= w ||
           y2 < 0 || y2 >= h;
  };

  for (i32 i = 0; i < n; ++i) {
    i64 l = 0, r = 1e13;
    auto [x, y, id] = points[i];
    while (r - l > 1) {
      i64 m = (l + r) >> 1;
      borders(x - m, y - m, x + m - 1, y + m - 1) ||
              tr.get(x - m, x + m) > y - m
          ? r = m
          : l = m;
    }
    tr.add(x - l, x + l, 2 * l);
    ans[id] = l;
  }
  for (i32 i = 0; i < n; ++i) {
    cout << ans[i] << '\n';
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
// решение на неявном ДО, проходит ТЛ 2 сек, но на оригинальной задаче с РОИ
// ограничение было 1.5 сек существует решение на обычном ДО, которое работает
// существенно быстрее