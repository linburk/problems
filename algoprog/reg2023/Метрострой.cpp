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
#define LINEBR
std::mt19937_64 rng(std::chrono::steady_clock().now().time_since_epoch().count());
template <typename T, typename V>
std::istream &operator>>(std::istream &is, std::pair<T, V> &rhs) {
    is >> rhs.first >> rhs.second;
    return is;
}
template <typename T, typename V, char SEP = ' '>
std::ostream &operator<<(std::ostream &os, std::pair<T, V> const &rhs) {
    os << rhs.first << SEP << rhs.second;
    return os;
}
template <char SEP = ' '>
void debug(auto&&...args) {
    ((std::cout << args << SEP), ...);
#ifdef LINEBR
    std::cout << "\n";
#endif
}
#if __cplusplus >= 202002L
template <typename T, char SEP = ' '> requires std::ranges::input_range<T>
std::ostream &operator<<(std::ostream &os, const T &cont) {
    for (const auto &i : cont) {
        os << i << SEP;
    }
#ifdef LINEBR
    os << '\n';
#endif
    return os;
}
template <typename T> requires std::ranges::output_range<T, std::ranges::range_value_t<T>>
std::istream &operator>>(std::istream &is, T &rhs) {
    for (auto &i : rhs) {
        is >> i;
    }
    return is;
}
#else // only vector
template <typename T, char SEP = ' '>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &cont) {
    for (const auto &i : cont) {
        os << i << SEP;
    }
#ifdef LINEBR
    os << "\n";
#endif
    return os;
}
template <typename T>
std::istream &operator>>(std::istream &is, std::vector<T> &rhs) {
    for (auto &i : rhs) {
        is >> i;
    }
    return is;
}
#endif
}

struct engine {
    i64 a, b, z;
};

bool check(i64 m, i64 p, vector<engine> const &a) {
    i64 res = 0;
    for (auto const &[a, b, z] : a) {
        res += a * (std::min(z, m)) + b * (std::max(0ll, m-z));
    }
    return res >= p;
}

void solve() {
    i64 n, p;
    cin >> n >> p;
    vector<engine> a(n);
    for (auto &[a, b, z] : a) cin >> z >> a >> b;
    i64 l = 0, r = 1e12;
    while (r-l>1) {
        i64 m = (l+r)>>1;
        check(m, p, a) ? r = m : l = m;
    }
    cout << r << "\n";
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