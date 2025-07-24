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
#define PRECALCULATE 0
#define MULTITEST 0

struct persistent_st {
private:
  struct node {
    i32 val = 0;
    i32 ls = 0, rs = 0;
    node() {}
    node(node const &n) { this->ls = n.ls, this->rs = n.rs, this->val = n.val; }
  };
  vector<node> tr;
  vector<i32> roots;
  i32 sz;

private:
  i32 build(i32 l, i32 r) {
    i32 n = static_cast<i32>(tr.size());
    tr.push_back(node());
    if (l == r - 1)
      return n;
    i32 m = (l + r) >> 1;
    tr[n].ls = build(l, m);
    tr[n].rs = build(m, r);
    return n;
  }
  i32 add(i32 i, i32 val, i32 l, i32 r, i32 n) {
    i32 n_n = static_cast<i32>(tr.size());
    tr.push_back(node(tr[n]));
    if (l == r - 1) {
      tr[n_n].val += val;
      return n_n;
    }
    i32 m = (l + r) >> 1;
    i < m ? tr[n_n].ls = add(i, val, l, m, tr[n_n].ls)
          : tr[n_n].rs = add(i, val, m, r, tr[n_n].rs);
    tr[n_n].val = tr[tr[n_n].ls].val + tr[tr[n_n].rs].val;
    return n_n;
  }
  i32 get(i32 ql, i32 qr, i32 l, i32 r, i32 n) {
    if (l >= qr || r <= ql)
      return 0;
    if (ql <= l && r <= qr)
      return tr[n].val;
    i32 m = (l + r) >> 1;
    return get(ql, qr, l, m, tr[n].ls) + get(ql, qr, m, r, tr[n].rs);
  }

public:
  persistent_st(i32 sz) : sz{sz} { roots.push_back(build(0, sz)); }
  void add(i32 i, i32 val) {
    return roots.push_back(add(i, val, 0, sz, roots.back()));
  }
  i32 get_last_version() { return static_cast<i32>(roots.size()) - 1; }
  i32 get(i32 ql, i32 qr, i32 v) { return get(ql, qr, 0, sz, roots[v]); }
};

struct query {
  i32 l, r, i;
};

struct {
  void solve() {
    i32 n, m;
    cin >> n >> m;
    vi32 a(m), b(n), order;
    vb used(n + 1);
    cin >> a >> b;
    std::reverse(all(b));
    for (auto i : a) {
      if (used[i])
        order.push_back(i);
      else
        for (;;) {
          i32 k = b.back();
          used[k] = 1;
          b.pop_back();
          order.push_back(k);
          if (k == i)
            break;
        }
    }
    vi32 ans(order.size());
    vvi32 pos(n + 1);
    vector<query> q;
    for (i32 i = 0; i < order.size(); ++i) {
      pos[order[i]].push_back(i);
    }
    for (i32 i = 1; i <= n; ++i) {
      for (i32 j = 0; j < (i32)pos[i].size() - 1; ++j) {
        q.push_back({pos[i][j], pos[i][j + 1], pos[i][j]});
      }
      if (pos[i].size())
        ans[pos[i][pos[i].size() - 1]] = n;
    }
    vi32 count(n + 1);
    persistent_st tr(static_cast<i32>(order.size()));
    vi32 prev_pos(n + 1, -1);
    vi32 version(order.size());
    for (i32 i = static_cast<i32>(order.size()) - 1; i >= 0; --i) {
      if (prev_pos[order[i]] != -1) {
        tr.add(prev_pos[order[i]], 1);
      }
      prev_pos[order[i]] = i;
      version[i] = tr.get_last_version();
    }
    for (auto &&[l, r, ind] : q) {
      i32 g = tr.get(l, r + 1, version[l]);
      ans[ind] = (r - l + 1) - g;
    }
    cout << order.size() << '\n' << ans;
  }
} solution;

i32 main(i32 argc, char *argv[], char *envp[]) /* clang-format off */ {
  std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false); setlocale(LC_ALL, "Russian");
#if REDIRECT
  char const *FINPATH = std::getenv("FINPATH"), *FOUTPATH = std::getenv("FOUTPATH");
  std::freopen(FINPATH, "r", stdin); std::freopen(FOUTPATH, "w", stdout);
#endif
#if PRECALCULATE
  solution.precalc();
#endif
#if MULTITEST
  i32 t; std::cin >> t; for (i32 i = 0; i < t; i++)
#endif
  solution.solve();
  return 0;
} /* clang-format on */
