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

}
struct sparse_table {
    vector<vpi32> table;
    void build(vi32 const &a) {
        for (i32 i = 0; i < a.size(); ++i) {
            table[0][i].first = a[i];
            table[0][i].second = i;
        }
        for (i32 k = 1; k < table.size(); ++k) {
            for (i32 i = 0; i < table[0].size() - (1<<k) + 1; ++i) {
                table[k][i] = std::max(table[k-1][i], table[k-1][i+(1<<(k-1))]);
            }
        }
    }
    pi32 get_max(i32 lq, i32 rq) {
        i32 len = 31-__builtin_clz(rq-lq);
        return std::max(table[len][lq], table[len][rq-(1<<len)]);
    }
    sparse_table(vi32 const &a) {
        table.resize(64 - __builtin_clzll(a.size()), vpi32(a.size()));
        build(a);
    }
};
void solve() {
    i32 n, q;
    cin >> n >> q;
    vi32 a(n);
    cin >> a;
    sparse_table t(a);
    for (i32 i = 0; i < q; ++i) {
        i32 res = 0;
        i32 p, k;
        cin >> p >> k;
        --p; --k;
        if (p-k >= 0) {
            if (k == 0 || t.get_max(p-k, p+1).second == p-k && (p-k-1<0 || a[p-k-1] >= t.get_max(p-k+1, p+1).first)) {
                ++res;
            }
            else if (p-k-1 < 0 || (a[p-k-1] >= t.get_max(p-k, p+1).first)) {
                res += t.get_max(p-k, p+1).second - (p-k);
            }
        }
        if (k && p+k < n) {
            if (t.get_max(p, p+k+1).second == p+k && (p+k+1>=n || a[p+k+1] >= t.get_max(p, p+k).first)) {
                res++;
            }
            else if (p+k+1 >= n || (a[p+k+1] >= t.get_max(p, p+k+1).first)) {
                res += (p+k) - t.get_max(p, p+k+1).second;
            }

        }
        cout << res << "\n";
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
#if 0
    i32 t;
    std::cin >> t;
    for (i32 i = 0; i < t; i++)
#endif
    solve();
    return 0;
}