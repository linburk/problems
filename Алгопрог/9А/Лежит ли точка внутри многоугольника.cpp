#include <bits/stdc++.h>
#include <climits>
namespace /* clang-format off */ {
#define all(cont) cont.begin(), cont.end()
using i8 = std::int8_t; using i16 = std::int16_t; using i32 = std::int32_t; using i64 = std::int64_t;
using u8 = std::uint8_t; using u16 = std::uint16_t; using u32 = std::uint32_t; using u64 = std::uint64_t; using f64 = long double;
using pi32 = std::pair<i32, i32>; using vpi32 = std::vector<pi32>; using vvpi32 = std::vector<vpi32>; using pi64 = std::pair<i64, i64>;  using vpi64 = std::vector<pi64>; using vvpi64 = std::vector<vpi64>;
using vi32 = std::vector<i32>; using vvi32 = std::vector<vi32>; using vi64 = std::vector<i64>; using vvi64 = std::vector<vi64>;
using vb = std::vector<bool>; using vvb = std::vector<vb>; using vc = std::vector<char>; using vvc = std::vector<vc>;
using si32 = std::set<i32>; using spi32 = std::set<pi32>; using si64 = std::set<i64>; using spi64 = std::set<pi64>;
using mpi32 = std::map<i32, i32>; using umpi32 = std::unordered_map<i32, i32>; using mpi64 = std::map<i64, i64>;  using umpi64 = std::unordered_map<i64, i64>;
template <typename T, typename V> std::istream &operator>>(std::istream &is, std::pair<T, V> &p) { is >> p.first >> p.second; return is; }
template <typename T, typename V, char SEP = ' '> std::ostream &operator<<(std::ostream &os, std::pair<T, V> const &p) { os << p.first << SEP << p.second; return os; }
template <typename T, char SEP = ' '> std::ostream &operator<<(std::ostream &os, const std::vector<T> &cont) { for (const auto &i : cont) { os << i; } os << "\n"; return os; }
template <typename T> std::istream &operator>>(std::istream &is, std::vector<T> &cont) { for (auto &i : cont) { is >> i; } return is; }
template <char SEP = ' '> void debug(auto&&...args) { ((std::cout << args << SEP), ...); std::cout << "\n"; }
template <typename T> void inline unique(std::vector<T> &cont) { cont.erase(std::unique(cont.begin(), cont.end()), cont.end()); }
std::mt19937_64 randi64(std::chrono::steady_clock().now().time_since_epoch().count());
using std::vector, std::string, std::pair, std::cin, std::cout;
} /* clang-format on */
#define MULTITEST 0

struct point {
    i64 x, y;
};
i64 operator%(point const &a, point const &b) {
    return a.x * b.y - a.y * b.x;
};
i64 operator*(point const &a, point const &b) {
    return a.x * b.x + a.y * b.y;
}
f64 operator^(point const &a, point const &b) {
    return (f64)(a%b)/(a*b);
}

void solve() {
    f64 eps = 1e-5;
    i32 n;
    f64 ang = 0;
    point st;
    cin >> n >> st.x >> st.y;
    for (i32 i = 0; i < n; ++i) {
        point x;
        cin >> x.x >> x.y;
        ang += (st^x);
    }
    if (ang + eps > 0 && ang - eps < 0) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
    }
    
}

i32 main(i32 argc, char *argv[]) /* clang-format off */ {
    std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false); setlocale(LC_ALL, "Russian");
#ifdef __APPLE__
    std::freopen("/Users/dmitrii/Documents/Code/Code/input.txt", "r", stdin);
    std::freopen("/Users/dmitrii/Documents/Code/Code/output.txt", "w", stdout);
#endif
#if MULTITEST
    i32 t; std::cin >> t; for (i32 i = 0; i < t; i++)
#endif
    solve();
    return 0;
} /* clang-format on */