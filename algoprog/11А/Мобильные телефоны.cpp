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
using std::vector, std::string, std::pair, std::cin, std::cout;
// clang-format off
std::mt19937_64 rng(std::chrono::steady_clock().now().time_since_epoch().count());
template <typename T, typename V> std::istream &operator>>(std::istream &is, std::pair<T, V> &p) { is >> p.first >> p.second; return is; }
template <typename T, typename V, char SEP = ' '> std::ostream &operator<<(std::ostream &os, std::pair<T, V> const &p) { os << p.first << SEP << p.second; return os; }
template <char SEP = ' '> void debug(auto&&...args) { ((std::cout << args << SEP), ...); std::cout << "\n"; }
template <typename T, char SEP = ' '> std::ostream &operator<<(std::ostream &os, const std::vector<T> &cont) { for (const auto &i : cont) { os << i; } os << "\n"; return os; }
template <typename T> std::istream &operator>>(std::istream &is, std::vector<T> &cont) { for (auto &i : cont) { is >> i; } return is; }
// clang-format on
}

struct f_tree2 {
    vvi32 tree;
    i32 sz;
    f_tree2(i32 n): sz(n) { tree.resize(n+1, vi32(n+1)); }
    void add(i32 x, i32 y, i32 val) {
        for (i32 i=x;i<=sz;i+=i&-i) {
            for (i32 j=y;j<=sz;j+=j&-j) {
                tree[i][j] += val;
            }
        }
    }
    i32 sum(i32 x, i32 y) {
        i32 res = 0;
        for (i32 i=x;i>0;i-=i&-i) {
            for (i32 j=y;j>0;j-=j&-j){
                res += tree[i][j];
            }
        }
        return res;
    }
    i32 sum(i32 x1, i32 y1, i32 x2, i32 y2) {
        return sum(x2, y2) - sum(x2, y1-1) - sum(x1-1, y2) + sum(x1-1, y1-1);
    }
};

void solve() {
    i32 n;
    char c;
    cin >> c >> n; cin.get();
    f_tree2 tr(n);
    for (;cin >> c && c != '3';) {
        if (c == '1') {
            i32 x, y, v;
            cin >> x >> y >> v;
            tr.add(x+1, y+1, v);
        }
        if (c == '2') {
            i32 x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << tr.sum(x1+1, y1+1, x2+1, y2+1) << '\n';
        }
        cin.get();
    }
    // ÑÐ¾ Ð¶Ðµ ÑÐ°Ð¼Ð¾Ðµ Ð´ÐµÑÐµÐ²Ð¾, ÑÐ¾Ð»ÑÐºÐ¾ Ð² Ð¿ÑÐµÐ´ÑÐ´ÑÑÐµÐ¹ Ð·Ð°Ð´Ð°ÑÐµ Ð½Ðµ Ð¿ÑÐ¾ÑÐ¾Ð´Ð¸Ñ
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