#include <bits/stdc++.h>
#include <climits>

#define LOCAL 1 && __APPLE__
#define REDIRECT 1 && __APPLE__
#define PRECALCULATE 0
#define MULTITEST 0

namespace /* clang-format off */ {
#define all(cont) cont.begin(), cont.end()
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
  std::cout << "[";
  for (auto b = cont.begin(), e = cont.end(); b != e; ++b) os << *b << (b + 1 == e ? "" : ", "); std::cout << "]"; return os;
#else
  for (auto b = cont.begin(), e = cont.end(); b != e; ++b) os << *b << (b + 1 == e ? ENDL : SEP); return os;
#endif
}
}
namespace /* functions */ {
#if __cplusplus >= 202002L
void print(auto&&...args) { ((std::cout << args), ...); }
void input(auto&&... args) { ((std::cin >> args), ...); }
#endif
template <typename T> void inline unique(std::vector<T> &cont) { cont.erase(std::unique(cont.begin(), cont.end()), cont.end()); }
std::mt19937_64 ru64(std::chrono::steady_clock().now().time_since_epoch().count());
}
using std::vector, std::string, std::pair, std::cin, std::cout;
} /* clang-format on */

struct {
  vvi32 gr;
  vi32 order;
  vi32 used;
  vi32 cycle_num;
  vi32 st;
  vvpi32 cycle_dp;
  i32 cycle_cnt = -1;
  pi32 dfs_dp(i32 v) {
    used[v] = 1;
    if (gr[v].size() == 0) {
      return {1, 0};
    }
    pi32 ans{1, 0};
    for (auto to : gr[v]) {
      if (cycle_num[to] != -1)
        continue;
      pi32 t = dfs_dp(to);
      ans.first += t.second;
      ans.second += std::max(t.first, t.second);
    }
    return ans;
  }
  void ts(i32 v) {
    if (used[v])
      return;
    used[v] = 1;
    for (auto to : gr[v])
      ts(to);
    order.push_back(v);
  }
  void cf(i32 v) {
    if (used[v]) {
      cycle_num[v] = ++cycle_cnt;
      for (; st.back() != v; st.pop_back()) {
        cycle_num[st.back()] = cycle_cnt;
      }
      st.pop_back();
      return;
    }
    used[v] = 1;
    st.push_back(v);
    for (auto to : gr[v]) {
      cf(to);
    }
    if (cycle_num[v] == -1)
      st.pop_back();
  }
  void solve() {
    i32 n;
    cin >> n;
    gr.resize(n);
    used.resize(n);
    cycle_num.resize(n, -1);
    for (i32 i = 0; i < n; ++i) {
      i32 to;
      cin >> to;
      if (to == -1)
        continue;
      gr[to - 1].push_back(i);
    }
    for (i32 i = 0; i < n; ++i) {
      ts(i);
    }
    std::reverse(all(order));
    used.assign(n, 0);
    for (i32 i = 0; i < n; ++i) {
      if (!used[order[i]])
        cf(order[i]);
    }
    cycle_dp.resize(cycle_cnt + 1);
    used.assign(n, 0);
    i64 res = 0;
    for (i32 i = 0; i < n; ++i) {
      if (used[order[i]])
        continue;
      pi32 t = dfs_dp(order[i]);
      if (cycle_num[order[i]] == -1) {
        res += std::max(t.first, t.second);
      } else {
        cycle_dp[cycle_num[order[i]]].push_back(t);
      }
    }
    for (i32 i = 0; i <= cycle_cnt; ++i) {
      auto dp2 = [](vpi32 &one) -> i32 {
        vpi32 dp(one.size() + 1);
        for (i32 j = 1; j <= one.size(); ++j) {
          dp[j].first =
              dp[j - 1].second + std::max(one[j - 1].first, one[j - 1].second);
          dp[j].second =
              std::max(dp[j - 1].first, dp[j - 1].second) + one[j - 1].second;
        }
        return std::max(dp.back().first, dp.back().second);
      };
      i32 r = 0;
      pi32 t;
      t = cycle_dp[i].back();
      cycle_dp[i].pop_back();
      r = std::max(r, dp2(cycle_dp[i]) + t.second);
      cycle_dp[i].push_back(t);
      t = cycle_dp[i].front();
      cycle_dp[i].erase(cycle_dp[i].begin());
      r = std::max(r, dp2(cycle_dp[i]) + t.second);
      res += r;
    }
    cout << res << '\n';
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
