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
#if __GNUC__
using i128 = __int128; using u128 = unsigned __int128;
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
#if __GNUC__
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

struct dsu {
  v<i32> rank, anc;
  using mpi32 = m<i32, i32>;
  using pi32 = p<i32, i32>;
  v<mpi32> val;
  v<pi32> res;
  dsu(v<i32> const &c) {
    i32 n = static_cast<i32>(c.size());
    rank.resize(n);
    anc.resize(n);
    val.resize(n);
    res.resize(n);
    for (i32 i = 0; i < n; ++i)
      val[i] = {{c[i], 1}}, res[i] = {1, c[i]};
    std::iota(all(anc), 0);
  }
  i32 leader(i32 a) {
    return anc[a] == a ? a : anc[a] = leader(anc[a]);
  }
  void merge(mpi32 &a, pi32 &p_r, mpi32 const &b) {
    for (auto [f, s] : b) {
      a[f] += s;
      if (a[f] > p_r.first) {
        p_r.first = a[f];
        p_r.second = f;
      }
      else if (a[f] == p_r.first) {
        p_r.second += f;
      }
    }
  }
  void unite(i32 a, i32 b) {
    a = leader(a), b = leader(b);
    if (rank[a] > rank[b]) std::swap(a, b);
    rank[b] = std::max(rank[a] + 1, rank[b]);
    anc[a] = b;
    merge(val[b], res[b], val[a]);
  }
  i32 get(i32 a) {
    return res[leader(a)].second;
  }
};

struct {
  void solve() {
    i32 n;
    cin >> n;
    v<v<i32> > gr(n);
    v<i32> c(n);
    cin >> c;
    dsu d(c);
    for (i32 i = 1; i < n; ++i) {
      i32 x, y;
      cin >> x >> y;
      gr[x - 1].push_back(y - 1);
      gr[y - 1].push_back(x - 1);
    }
    v<i32> res(n);
    std::function<void(i32, i32)> dfs = [&] (i32 v, i32 p) {
      for (auto to : gr[v])
        if (to != p) {
          dfs(to, v);
          d.unite(v, to);
        }
      res[v] = d.get(v);
    };
    dfs(0, 0);
    cout << res;
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