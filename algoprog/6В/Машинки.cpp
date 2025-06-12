#include <bits/stdc++.h>
#include <climits>

#define all(cont) cont.begin(), cont.end()
#define funique(cont) cont.erase(unique(all(cont)), cont.end())

namespace {
using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using f64 = long double;
using pi32 = std::pair<i32, i32>;
using pi64 = std::pair<i64, i64>;
using pu64 = std::pair<u64, u64>;
using vpi32 = std::vector<pi32>;
using vpi64 = std::vector<pi64>;
using vi32 = std::vector<i32>;
using vi64 = std::vector<i64>;
using vvi32 = std::vector<vi32>;
using vvi64 = std::vector<vi64>;
using vvpi32 = std::vector<vpi32>;
using vvpi64 = std::vector<vpi64>;
using vb = std::vector<bool>;
using vc = std::vector<char>;
using vvb = std::vector<vb>;
using vvc = std::vector<vc>;
using si32 = std::set<i32>;
using si64 = std::set<i64>;
using spi32 = std::set<pi32>;
using spi64 = std::set<pi64>;
using mpi32 = std::map<i32, i32>;
using mpi64 = std::map<i64, i64>;
using umpi32 = std::unordered_map<i32, i32>;
using umpi64 = std::unordered_map<i64, i64>;
using std::vector, std::string, std::cin, std::cout;
}

namespace {
std::mt19937_64 rng(std::chrono::steady_clock().now().time_since_epoch().count());
template <typename T>
std::istream &operator>>(std::istream &is, std::vector<T> &array) {
    for (auto &i : array) {
        is >> i;
    }
    return is;
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &array) {
    for (const auto &i : array) {
        os << i << " ";
    }
//            os << "\n";
    return os;
}
void debug(auto&&...args) {
    ((std::cout << args << " "), ...);
    std::cout << "\n";
}
}

void out(i32 i, i32 j, i8 k, vector<vector<vector<i8> > > const &past, i8 act = 0) {
    i32 ni = std::max(0, k ? i : i-1), nj = std::max(!k ? j : j-1, 0);
    i8 nk = past[i][j][k];
    if (nk != 2) out(ni, nj, nk, past, (nk != k) | (ni != i) << 1 | (nj != j) << 2);
    if (act & 1) {
        cout << "Switch road from " << k+1 << " to " << !k+1 << "\n";
    }
    if (act & 2 | act & 4) cout << "Car " << (act & 2 ? i : j) + 1  << " from road " << (act & 2 ? 1 : 2) << "\n";
    
}

void solve() {
    i32 t, n, m;
    cin >> t >> n >> m;
    vi64 a(n), b(m);
    cin >> a >> b;
    vector<vector<vector<i64> > > dp(n+1, vector<vector<i64> >
                                     (m+1, vector<i64>(2, 1e9)));
    vector<vector<vector<i8> > > past(n+1, vector<vector<i8> >(m+1, vector<i8>(2, 2)));
    dp[0][0][0] = 0;
    for (i32 i = 0; i <= n; ++i) {
        for (i32 j = 0; j <= m; ++j) {
            if (i) {
                past[i][j][0] = dp[i-1][j][0] > dp[i-1][j][1] + t * (n-i+m-j+1);
                dp[i][j][0] = std::min(
                    dp[i-1][j][0],
                    dp[i-1][j][1] + t * (n-i+m-j+1)
                ) + a[i-1] * (n-i+m-j+1);
            }
            if (j) {
                past[i][j][1] = dp[i][j-1][1] < dp[i][j-1][0] + t * (n-i+m-j+1);
                dp[i][j][1] = std::min(
                    dp[i][j-1][1],
                    dp[i][j-1][0] + t * (n-i+m-j+1)
                ) + b[j-1] * (n-i+m-j+1);
            }
        }
    }
    i8 S = dp[n][m][0] > dp[n][m][1];
    cout << std::setprecision(5) << std::fixed << static_cast<f64>(std::min(dp[n][m][0], dp[n][m][1])) / (n+m) << "\n";
    out(n, m, S, past, 0);
    
}

i32 main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    setlocale(LC_ALL, "Russian");
#ifdef __APPLE__
    std::freopen("/Users/dmitrii/Documents/Code/Code/input.txt", "r", stdin);
    std::freopen("/Users/dmitrii/Documents/Code/Code/output.txt", "w", stdout);
#endif
#if 0
    i32 t;
    std::cin >> t;
    for (i32 i = 0; i < t; i++)
#endif
    solve();
    return 0;
}