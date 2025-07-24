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

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct st1d {
private:
  struct node {
    i32 val = 0;
  };
  i32 sz = 128;
  gp_hash_table<i32, node> tr;
  void add(i32 z, i64 val, i32 l, i32 r, i32 n) {
    if (l > z || r <= z)
      return;
    tr[n].val += val;
    if (l == r - 1)
      return;
    add(z, val, l, (l + r) >> 1, n << 1);
    add(z, val, (l + r) >> 1, r, n << 1 | 1);
  }
  i64 get(i32 lz, i32 rz, i32 l, i32 r, i32 n) {
    if (l >= rz || r <= lz)
      return 0;
    if (lz <= l && r <= rz)
      return tr[n].val;
    return get(lz, rz, l, (l + r) >> 1, n << 1) +
           get(lz, rz, (l + r) >> 1, r, n << 1 | 1);
  }

public:
  void add(i32 z, i32 val) { return add(z, val, 0, sz, 1); }
  i64 get(i32 lz, i32 rz) { return get(lz, rz, 0, sz, 1); }
};
struct st2d {
  struct node {
    st1d val;
  };
  i32 sz = 128;
  gp_hash_table<i32, node> tr;
  void add(i32 y, i32 z, i32 val, i32 l, i32 r, i32 n) {
    if (l > y || r <= y)
      return;
    tr[n].val.add(z, val);
    if (l == r - 1)
      return;
    add(y, z, val, l, (l + r) >> 1, n << 1);
    add(y, z, val, (l + r) >> 1, r, n << 1 | 1);
  }
  i64 get(i32 ly, i32 ry, i32 lz, i32 rz, i32 l, i32 r, i32 n) {
    if (l >= ry || r <= ly)
      return 0;
    if (ly <= l && r <= ry)
      return tr[n].val.get(lz, rz);
    return get(ly, ry, lz, rz, l, (l + r) >> 1, n << 1) +
           get(ly, ry, lz, rz, (l + r) >> 1, r, n << 1 | 1);
  }

public:
  void add(i32 y, i32 z, i32 val) { return add(y, z, val, 0, sz, 1); }
  i64 get(i32 ly, i32 ry, i32 lz, i32 rz) {
    return get(ly, ry, lz, rz, 0, sz, 1);
  }
};
struct st3d {
  struct node {
    st2d val;
  };
  i32 sz = 128;
  gp_hash_table<i32, node> tr;
  void add(i32 x, i32 y, i32 z, i32 val, i32 l, i32 r, i32 n) {
    if (l > x || r <= x)
      return;
    tr[n].val.add(y, z, val);
    if (l == r - 1)
      return;
    add(x, y, z, val, l, (l + r) >> 1, n << 1);
    add(x, y, z, val, (l + r) >> 1, r, n << 1 | 1);
  }
  i64 get(i32 lx, i32 rx, i32 ly, i32 ry, i32 lz, i32 rz, i32 l, i32 r, i32 n) {
    if (l >= rx || r <= lx)
      return 0;
    if (lx <= l && r <= rx)
      return tr[n].val.get(ly, ry, lz, rz);
    return get(lx, rx, ly, ry, lz, rz, l, (l + r) >> 1, n << 1) +
           get(lx, rx, ly, ry, lz, rz, (l + r) >> 1, r, n << 1 | 1);
  }

public:
  void add(i32 x, i32 y, i32 z, i32 val) { return add(x, y, z, val, 0, sz, 1); }
  i64 get(i32 lx, i32 rx, i32 ly, i32 ry, i32 lz, i32 rz) {
    return get(lx, rx, ly, ry, lz, rz, 0, sz, 1);
  }
};

void solve() {
  i32 n;
  cin >> n;
  st3d tr;
  while (1) {
    i32 c;
    cin >> c;
    if (c == 3)
      break;
    if (c == 2) {
      i32 x1, x2, y1, y2, z1, z2;
      cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
      cout << tr.get(x1, x2 + 1, y1, y2 + 1, z1, z2 + 1) << '\n';
    }
    if (c == 1) {
      i32 x, y, z, k;
      cin >> x >> y >> z >> k;
      tr.add(x, y, z, k);
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
  // задача на дерево Рябко)