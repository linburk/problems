#include <bits/stdc++.h>
#include <climits>

#define LOCAL 1 && __APPLE__
#define ALTERSTREAM 1 && __APPLE__
#define PRECALCULATE 0
#define MULTITEST 0

namespace /* clang-format off */ {
#define all(cont) cont.begin(), cont.end()
using std::vector, std::string, std::pair;
#if ALTERSTREAM
std::ifstream cin; std::ofstream cout;
#else
using std::cin, std::cout;
#endif
namespace /* aliases */ {
using i8 = std::int8_t; using i16 = std::int16_t; using i32 = std::int32_t; using i64 = std::int64_t;
using u8 = std::uint8_t; using u16 = std::uint16_t; using u32 = std::uint32_t; using u64 = std::uint64_t; using f64 = long double; using f32 = float;
using pi32 = std::pair<i32, i32>; using vpi32 = std::vector<pi32>; using vvpi32 = std::vector<vpi32>; using pi64 = std::pair<i64, i64>;  using vpi64 = std::vector<pi64>; using vvpi64 = std::vector<vpi64>;
using vi8 = std::vector<i8>; using vvi8 = std::vector<vi8>; using vi32 = std::vector<i32>; using vvi32 = std::vector<vi32>; using vi64 = std::vector<i64>; using vvi64 = std::vector<vi64>;
using vb = std::vector<bool>; using vvb = std::vector<vb>; using vc = std::vector<char>; using vvc = std::vector<vc>;
using si32 = std::set<i32>; using spi32 = std::set<pi32>; using si64 = std::set<i64>; using spi64 = std::set<pi64>;
using mpi32 = std::map<i32, i32>; using umpi32 = std::unordered_map<i32, i32>; using mpi64 = std::map<i64, i64>;  using umpi64 = std::unordered_map<i64, i64>;
}
namespace /* in/out op. overloadings */ {
template <typename T, typename V> std::istream &operator>>(std::istream &is, std::pair<T, V> &p) { is >> p.first >> p.second; return is; }
template <typename T> std::istream &operator>>(std::istream &is, std::vector<T> &cont) { for (auto &i : cont) { is >> i; } return is; }
template <typename T, typename V, char SEP = ' ', char ENDL = '\n'> std::ostream &operator<<(std::ostream &os, std::pair<T, V> const &p) {
#if LOCAL
  os << "<" << p.first << ", " << p.second << ">"; return os;
#else
  os << p.first << SEP << p.second << ENDL; return os;
#endif
}
template <typename T, char SEP = ' ', char ENDL = '\n'> std::ostream &operator<<(std::ostream &os, const std::vector<T> &cont) {
#if LOCAL
  os << "[";
  for (auto b = cont.begin(), e = cont.end(); b != e; ++b) os << *b << (b + 1 == e ? "" : ", "); os << "]"; return os;
#else
  for (auto b = cont.begin(), e = cont.end(); b != e; ++b) os << *b << (b + 1 == e ? ENDL : SEP); return os;
#endif
}
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

struct pers_st {
  i32 const INF = 1E9;
private:
  struct node {
    i32 val;
    i32 pos;
    i32 l_s = 0, r_s = 0;
    operator pi32() { return pi32{val, pos}; }
  };
  vector<node> tr;
  vi32 rt;
  i32 sz;
  void merge(node &n, node const &l, node const &r) {
    if (l.val > r.val) {
      n.val = l.val;
      n.pos = l.pos;
    } else {
      n.val = r.val;
      n.pos = r.pos;
    }
  }
private:
  i32 build(i32 l, i32 r) {
    tr.push_back(node());
    i32 n = static_cast<i32>(tr.size()) - 1;
    if (l == r-1) {
      tr[n].val = INF;
      tr[n].pos = l;
      return n;
    }
    i32 m = (l + r) >> 1;
    tr[n].l_s = build(l, m);
    tr[n].r_s = build(m, r);
    merge(tr[n], tr[tr[n].l_s], tr[tr[n].r_s]);
    return n;
  }
  i32 update(i32 i, i32 val, i32 l, i32 r, i32 n) {
    tr.push_back(tr[n]);
    n = static_cast<i32>(tr.size()) - 1;
    i32 m = (l + r) >> 1;
    if (l == r - 1) {
      tr[n].val = val;
      tr[n].pos = i;
      return n;
    }
    if (i < m)
      tr[n].l_s = update(i, val, l, m, tr[n].l_s);
    else
      tr[n].r_s = update(i, val, m, r, tr[n].r_s);
    merge(tr[n], tr[tr[n].l_s], tr[tr[n].r_s]);
    return n;
  }
  node get(i32 ql, i32 qr, i32 l, i32 r, i32 n) {
    if (l >= qr || r <= ql) return {-1, -1};
    if (ql <= l && r <= qr) return tr[n];
    i32 m = (l + r) >> 1;
    node L = get(ql, qr, l, m, tr[n].l_s);
    node R = get(ql, qr, m, r, tr[n].r_s);
    node res; merge(res, L, R);
    return res;
  }
public:
  pers_st (i32 sz_): sz{sz_} {
    tr.reserve(2E7 + 2E6); // Ð¼ÐµÐ³Ð°-Ð²Ð°Ð¶Ð½Ð°Ñ ÑÑÑÐ¾ÑÐºÐ°
    rt.reserve(1E6);
    tr.resize(1);
    rt.push_back(build(0, sz));
  }
  i32 update(i32 i, i32 val) {
    rt.push_back(update(i, val, 0, sz, rt.back()));
    return rt.back();
  }
  pi32 get(i32 ql, i32 qr, i32 vers) {
    return get(ql, qr, 0, sz, vers);
  }
};

struct {
  i32 const maxelem = 5e5+1;
  void precalculate();
  void solve() {
    i32 n;
    cin >> n;
    vi32 a(n);
    cin >> a;
    vi32 next_pos(maxelem, -1);
    vi32 vers(n, 1);
    pers_st st(n);
    for (i32 i = n - 1; i >= 0; --i) {
      if (next_pos[a[i]] != -1) {
        st.update(i, next_pos[a[i]]);
        vers[i] = st.update(next_pos[a[i]], next_pos[a[i]]);
      }
      else if (i + 1 < n)
        vers[i] = vers[i + 1];
      next_pos[a[i]] = i;
    }
    i32 q;
    cin >> q;
    for (i32 i = 0; i < q; ++i) {
      i32 l, r;
      cin >> l >> r; --l;
      pi32 g = st.get(l, r, vers[l]);
      if (g.first >= r) {
        cout << a[g.second] << '\n';
      } else {
        cout << "0\n";
      }
    }
    
  }
} solution;

i32 main(i32 argc, char *argv[], char *envp[]) /* clang-format off */ {
  std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
  std::setlocale(LC_ALL, "Russian");
#if ALTERSTREAM
  cin.open(std::getenv("FINPATH"));
  cout.open(std::getenv("FOUTPATH"));
#endif
#if PRECALCULATE
  solution.precalculate();
#endif
#if MULTITEST
  i32 t; std::cin >> t; for (i32 i = 0; i < t; i++)
#endif
  solution.solve();
#if ALTERSTREAM
  cin.close();
  cout.close();
#endif
  return 0;
} /* clang-format on */
