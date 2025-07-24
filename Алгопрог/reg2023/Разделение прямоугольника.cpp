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
    os << "\n";
    return os;
}
void debug(auto&&...args) {
    ((std::cout << args << " "), ...);
    std::cout << "\n";
}
}

void solve() {
    i64 a, b, k, m;
    cin >> a >> b >> k >> m;
    // h + w = k
    // w = k - h
    // (h+1)(w+1)=m
    // (h+1)(k-h+1)=m
    // h+1-h^2-h+kh+k=m
    // -h^2+kh+k-m+1=0
    // h^2-kh+(m-k-1)=0
    i64 D = k * k - 4 * (m-k-1);
    if (D < 0) cout << "-1\n";
    else {
        i64 h1 = ((f64)k + sqrt(D)) / 2;
        i64 h2 = ((f64)k - sqrt(D)) / 2;
        i64 w1 = k - h1;
        i64 w2 = k - h2;
        if ((h1 + 1)*(w1 + 1) != m || h1 >= a || w1 >= b) h1 = -1e9, w1 = -1e9;
        if ((h2 + 1)*(w2 + 1) != m || h2 >= a || w2 >= b) h2 = -1e9, w2 = -1e9;
        if ((h1 < 0 && h2 < 0) || (w1 < 0 && w2 < 0)) {
            cout << "-1\n";
        } else {
            h1 < 0 ? h1 = 1e9 : 0;
            h2 < 0 ? h2 = 1e9 : 0;
            w1 < 0 ? w1 = 1e9 : 0;
            w2 < 0 ? w2 = 1e9 : 0;
            i64 mind = std::min({h1, h2, w1, w2});
            cout << mind << " " << k - mind << "\n";
        }
    }
    
    
}

i32 main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    setlocale(LC_ALL, "Russian");
#ifdef __APPLE__
    std::freopen("/Users/dmitrii/Documents/Code/Code/input.txt", "r", stdin);
    std::freopen("/Users/dmitrii/Documents/Code/Code/output.txt", "w", stdout);
#endif
#if 1
    i32 t;
    std::cin >> t;
    for (i32 i = 0; i < t; i++)
#endif
    solve();
    return 0;
}