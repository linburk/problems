#include <bits/stdc++.h>
#include <climits>

#define LOCAL__ 1 && __APPLE__
#define REDIRECT__ 1 && __APPLE__
#define PRECALCULATE__ 0
#define MULTITEST__ 0

namespace /* clang-format off */ {
#define all(cont) cont.begin(), cont.end()
using std::string;
#if REDIRECT__
std::ifstream cin; std::ofstream cout;
#else
using std::cin, std::cout;
#endif
namespace /* aliases */ {
using i8 = std::int8_t; using i16 = std::int16_t; using i32 = std::int32_t; using i64 = std::int64_t;
using u8 = std::uint8_t; using u16 = std::uint16_t; using u32 = std::uint32_t; using u64 = std::uint64_t;  using f64 = long double; using f32 = float;
using pi32 = std::pair<i32, i32>; using vpi32 = std::vector<pi32>; using vvpi32 = std::vector<vpi32>; using pi64 = std::pair<i64, i64>; using vpi64 = std::vector<pi64>; using vvpi64 = std::vector<vpi64>; using pu32 = std::pair<u32, u32>; using pu64 = std::pair<u64, u64>;
using vi32 = std::vector<i32>; using vvi32 = std::vector<vi32>; using vi64 = std::vector<i64>; using vvi64 = std::vector<vi64>; using vu64 = std::vector<u64>; using vvu64 = std::vector<vu64>;
using vb = std::vector<bool>; using vvb = std::vector<vb>; using vc = std::vector<char>; using vvc = std::vector<vc>;
using si32 = std::set<i32>; using spi32 = std::set<pi32>; using si64 = std::set<i64>; using spi64 = std::set<pi64>;
using mpi32 = std::map<i32, i32>; using umpi32 = std::unordered_map<i32, i32>; using mpi64 = std::map<i64, i64>;  using umpi64 = std::unordered_map<i64, i64>;
#if __GNUC__ && ( __x86_64__ || __arm64__ )
using i128 = __int128; using u128 = unsigned __int128;
using pi128 = std::pair<i128, i128>; using vpi128 = std::vector<pi128>; using vvpi128 = std::vector<vpi128>;
using vi128 = std::vector<i128>; using vvi128 = std::vector<vi128>;
using si128 = std::set<i128>; using spi128 = std::set<pi128>;
using mpi128 = std::map<i128, i128>; using umpi128 = std::unordered_map<i128, i128>;
#endif
template <typename T> using v = std::vector<T>;
template <typename T> using s = std::set<T>;
template <typename T, typename V> using p = std::pair<T, V>;
template <typename T, typename V> using m = std::map<T, V>;
template <typename T, typename V> using um = std::unordered_map<T, V>;
}
namespace /* in/out op. overloadings */ {
template <typename T, typename V> std::istream &operator>>(std::istream &is, std::pair<T, V> &p) { is >> p.first >> p.second; return is; }
template <typename T> std::istream &operator>>(std::istream &is, std::vector<T> &cont) { for (auto &i : cont) { is >> i; } return is; }
template <typename T, typename V, char SEP = ' ', char ENDL = '\n'> std::ostream &operator<<(std::ostream &os, std::pair<T, V> const &p) {
#if LOCAL__
  os << "<" << p.first << ", " << p.second << ">";
  return os;
#else
  os << p.first << SEP << p.second << ENDL;
  return os;
#endif
}
template <typename T, char SEP = ' ', char ENDL = '\n'> std::ostream &operator<<(std::ostream &os, const std::vector<T> &cont) {
#if LOCAL__
  os << "[";
  for (auto b = cont.begin(), e = cont.end(); b != e; ++b)
    os << *b << (b + 1 == e ? "" : ", "); os << "]";
  return os;
#else
  for (auto b = cont.begin(), e = cont.end(); b != e; ++b)
    os << *b << (b + 1 == e ? ENDL : SEP);
  return os;
#endif
}
#if __GNUC__ && (__x86_64__ || __arm64__)
std::istream &operator>>(std::istream &is, i128 &rhs) {
  i64 res; is >> res; rhs = res; // btw, no sense to in nmbr mr than 20 chars
  return is;
}
std::ostream &operator<<(std::ostream &os, i128 const &rhs){
  std::string res;
  for (i128 tmp = (rhs < 0 ? -rhs : rhs); tmp; tmp /= 10)
    res += '0' + tmp % 10;
  if (rhs < 0) res += '-';
  for (auto i = res.rbegin(); i != res.rend(); ++i)
    os << *i;
  return os;
}
#endif
}
namespace /* functions */ {
#if __cplusplus >= 202002L
void print(auto &&...args) { ((cout << args), ...); }
void input(auto &&...args) { ((cin >> args), ...); }
#endif
template <typename T> void inline unique(std::vector<T> &cont) { cont.erase(std::unique(cont.begin(), cont.end()), cont.end()); }
std::mt19937_64 ru64(std::chrono::steady_clock().now().time_since_epoch().count());
}
} /* clang-format on */

#pragma GCC optimize("unrool-loops")
#pragma GCC target("avx2,avx,sse4.2,sse4.1")

struct st {
private:
  struct node {
    i64 val;
  };
  v<node> tr;
  i32 sz;
  void build(vi32 &a) {
    for (i32 i = 0; i < a.size(); ++i)
      tr[sz + i].val = a[i];
    for (i32 i = sz - 1; i > 0; --i) {
      tr[i].val = tr[i << 1].val + tr[i << 1 | 1].val;
    }
  }
public:
  void upd(i32 pos, i32 x) {
    pos += sz;
    tr[pos].val = x;
    for (pos >>= 1; pos; pos >>= 1)
      tr[pos].val = tr[pos << 1].val + tr[pos << 1 | 1].val;
  }
  i64 get(i32 ql, i32 qr) {
    i64 res = 0;
    ql += sz, qr += sz;
    for (; ql < qr; ql >>= 1, qr >>= 1) {
      if (ql & 1) res += tr[ql++].val;
      if (qr & 1) res += tr[--qr].val;
    }
    return res;
  }
public:
  st() {}
  st(vi32 &a): sz{static_cast<i32>(a.size())} {
    tr.resize(2 * sz);
    build(a);
  }
};

struct {
  struct hld_t {
    i32 up_c = 21;
    vvi32 &gr;
    vi32 &a;
    vi32 tour;
    vi32 sz;
    vi32 pos;
    vi32 depth;
    vvi32 up;
    vi32 start;
    st tr;
    hld_t(vvi32 &gr_, vi32 &a_): gr{gr_}, a{a_} {
      i32 n = static_cast<i32>(gr.size());
      pos.resize(n);
      depth.resize(n);
      start.resize(n);
      sz.resize(n, 1);
      up.resize(n, vi32(up_c));
      dfs1(0, 0);
      dfs2(0, 0);
      tr = st{tour};
    }
    i32 lca(i32 a, i32 b) {
      if (depth[a] < depth[b]) std::swap(a, b);
      for (i32 i = up_c - 1; i >= 0; --i)
        if (depth[up[a][i]] >= depth[b])
          a = up[a][i];
      if (a == b) return a;
      for (i32 i = up_c - 1; i >= 0; --i)
        if (up[b][i] != up[a][i])
          b = up[b][i], a = up[a][i];
      return up[a][0];
    }
    void dfs1(i32 v, i32 p) {
      i32 heavy = 0;
      up[v][0] = p;
      for (i32 i = 1; i < up_c; ++i)
        up[v][i] = up[up[v][i - 1]][i - 1];
      depth[v] = depth[p] + 1;
      for (i32 i = 0; i < gr[v].size(); ++i) {
        i32 to = gr[v][i];
        if (to != p) {
          dfs1(to, v);
          sz[v] += sz[to];
          if (gr[v][heavy] == p || sz[to] > sz[gr[v][heavy]])
            heavy = i;
        }
      }
      std::swap(gr[v][0], gr[v][heavy]);
    }
    void dfs2(i32 v, i32 p) {
      pos[v] = static_cast<i32>(tour.size());
      tour.push_back(a[v]);
      for (auto to : gr[v]) {
        if (to != p) {
          if (2 * sz[to] >= sz[v])
            start[to] = start[v];
          else
            start[to] = to;
          dfs2(to, v);
        }
      }
    }
    i64 get_path(i32 a, i32 b) {
      i64 res = 0;
      for (; depth[start[a]] > depth[b];) {
        res += tr.get(pos[start[a]], pos[a] + 1);
        a = up[start[a]][0];
      }
      res += tr.get(pos[b], pos[a] + 1);
      return res;
    }
    i64 get(i32 a, i32 b) {
      i64 res = 0;
      i32 ab = lca(a, b);
      res += get_path(a, ab);
      res += get_path(b, ab);
      res -= tr.get(pos[ab], pos[ab] + 1);
      return res;
    }
    void upd(i32 a, i32 x) {
      tr.upd(pos[a], x);
    }
  };
  void solve() {
    i32 n, m;
    cin >> n;
    vi32 v(n);
    cin >> v;
    vvi32 gr(n);
    for (i32 i = 1; i < n; ++i) {
      i32 a, b;
      cin >> a >> b;
      gr[a - 1].push_back(b - 1);
      gr[b - 1].push_back(a - 1);
    }
    cin >> m;
    hld_t hld(gr, v);
    for (i32 i = 0; i < m; ++i) {
      char c;
      cin >> c;
      if (c == '?') {
        i32 x, y;
        cin >> x >> y;
        cout << hld.get(x - 1, y - 1) << '\n';
      }
      if (c == '!') {
        i32 a, x;
        cin >> a >> x;
        hld.upd(a - 1, x);
      }
    }
  }
  void precalculate();
} solution;

i32 main(i32 argc, char *argv[], char *envp[]) /* clang-format off */ {
  cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
  std::setlocale(LC_ALL, "Russian");
#if REDIRECT__
  cin.open(std::getenv("FINPATH"));
  cout.open(std::getenv("FOUTPATH"));
#endif
#if PRECALCULATE__
  solution.precalculate();
#endif
#if MULTITEST__
  i32 t; cin >> t; for (i32 i = 0; i < t; i++)
#endif
  solution.solve();
#if REDIRECT__
  cin.close();
  cout.close();
#endif
  return 0;
} /* clang-format on */

