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
std::istream &operator>>(std::istream &is, std::pair<T, V> &p) {
    is >> p.first >> p.second;
    return is;
}
template <typename T, typename V, char SEP = ' '>
std::ostream &operator<<(std::ostream &os, std::pair<T, V> const &p) {
    os << p.first << SEP << p.second;
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
std::istream &operator>>(std::istream &is, T &cont) {
    for (auto &i : cont) {
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
std::istream &operator>>(std::istream &is, std::vector<T> &cont) {
    for (auto &i : cont) {
        is >> i;
    }
    return is;
}
#endif
}

struct array324_t {
    u32 data = 0;
    struct bit4_reference {
        i8 ind;
        array324_t *ref;
        void operator=(i8 val) noexcept {
            ref->data ^= int(*this) << (ind*4);
            ref->data |= (val & 0xF) << (ind*4);
        }
        operator int() const {
            return const_cast<const array324_t&>(*ref)[ind];
        }
    };
    i8 const operator[](i8 ind) const noexcept {
        return (data >> (ind*4)) & 0xF;
    } // Ð¿Ð¾-ÑÐ¾ÑÐ¾ÑÐµÐ¼Ñ ÑÑÐ¾ Ð´Ð¾Ð»Ð¶Ð½Ð¾ Ð±ÑÑÑ Ð² bit4_reference...
    bit4_reference operator[](i8 ind) noexcept {
        return bit4_reference{ind, this};
    }
};
bool operator<(array324_t const &lhs, array324_t const &rhs) {
    return lhs.data < rhs.data;
}

void solve() {
    const int INV = 15;
    const int MOD = 1E9+7;
    i16 n, m;
    cin >> n >> m;
    array324_t a;
    for (i16 i = 0; i < 8; ++i) a[i] = INV;
    for (i16 i = 0; i < m; ++i) {
        i16 c;
        cin >> c;
        a[c-1] = 0;
    }
    std::map<array324_t, int> curr;
    std::map<array324_t, int> next;
    for (i16 i = 0; i < 8; ++i) {
        if (a[i] == INV) continue;
        array324_t cnt ;
        for (i16 j = 0; j < 8; ++j) {
            if (a[j] != INV) cnt[j] = j;
        }
        cnt[i] = 0;
        ++curr[cnt];
    }
    for (i16 i = 0; i < n-1; ++i) {
        for (auto const &[arr, cnt] : curr) {
            for (i8 j = 0; j < 8; ++j) {
                if (a[j] != INV && arr[j] == j) {
                    array324_t copy = arr;
                    for (i8 k = 0; k < 8; ++k) {
                        if (a[k] != INV) copy[k] = std::min(k, (i8)(copy[k] + 1));
                    }
                    copy[j] = 0;
                    next[copy] = (next[copy] + cnt) % MOD;
                }
            }
        }
        std::swap(curr, next);
        next.clear();
    }
    i32 ans = 0;
    for (auto const &[arr, cnt] : curr) {
        ans = (ans + cnt) % MOD;
    }
    cout << ans << "\n";
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