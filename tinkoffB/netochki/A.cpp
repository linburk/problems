#include <bits/stdc++.h>
#include <climits>

#define LOCAL__ 1 && __APPLE__
#define REDIRECT__ 1 && __APPLE__

/* clang-format off */
#define all(cont) cont.begin(), cont.end()
using std::string;
#if REDIRECT__
std::ifstream cin; std::ofstream cout;
#else
using std::cin, std::cout;
#endif
/* aliases */
using i8 = std::int8_t; using i16 = std::int16_t; using i32 = std::int32_t; using i64 = std::int64_t;
using u8 = std::uint8_t; using u16 = std::uint16_t; using u32 = std::uint32_t; using u64 = std::uint64_t; using f64 = long double; using f32 = float;
using pi32 = std::pair<i32, i32>; using vpi32 = std::vector<pi32>; using vvpi32 = std::vector<vpi32>; using pi64 = std::pair<i64, i64>; using vpi64 = std::vector<pi64>; using vvpi64 = std::vector<vpi64>; using pu32 = std::pair<u32, u32>; using pu64 = std::pair<u64, u64>;
using vi32 = std::vector<i32>; using vvi32 = std::vector<vi32>; using vi64 = std::vector<i64>; using vvi64 = std::vector<vi64>; using vu64 = std::vector<u64>; using vvu64 = std::vector<vu64>;
using vb = std::vector<bool>; using vvb = std::vector<vb>; using vc = std::vector<char>; using vvc = std::vector<vc>;
using si32 = std::set<i32>; using spi32 = std::set<pi32>; using si64 = std::set<i64>; using spi64 = std::set<pi64>;
using mpi32 = std::map<i32, i32>; using umpi32 = std::unordered_map<i32, i32>; using mpi64 = std::map<i64, i64>; using umpi64 = std::unordered_map<i64, i64>;
#if __GNUC__ && ( __x86_64__ || __arm64__ )
using i128 = __int128; using u128 = unsigned __int128;
using pi128 = std::pair<i128, i128>; using vpi128 = std::vector<pi128>; using vvpi128 = std::vector<vpi128>;
using vi128 = std::vector<i128>; using vvi128 = std::vector<vi128>;
using si128 = std::set<i128>; using spi128 = std::set<pi128>;
using mpi128 = std::map<i128, i128>; using umpi128 = std::unordered_map<i128, i128>;
#endif
template <typename T> using v = std::vector<T>;
template <typename T, typename cmp = std::less<T>> using s = std::set<T, cmp>;
template <typename T, typename V> using p = std::pair<T, V>;
template <typename T, typename V, typename cmp = std::less<T>> using m = std::map<T, V>;
template <typename T, typename V> using um = std::unordered_map<T, V>;
template <int N, typename T> struct tensor : public std::vector<tensor<N-1, T> > {
    template <typename ...Args> tensor(int n = 0, Args... args) : std::vector<tensor<N-1, T> >(n, tensor<N-1, T>(args...)) {}
};
template <typename T> struct tensor<1, T> : public std::vector<T> {
    tensor(int n = 0, T const& val = T()) : std::vector<T>(n, val) {}
};
/* in/out op. overloadings */
#if __GNUC__ && (__x86_64__ || __arm64__)
std::istream &operator>>(std::istream &is, i128 &rhs) {
    std::string in;
    is >> in;
    i128 p = 1;
    rhs = 0;
    for (i64 i = in.size() - 1; i >= 0; --i, p *= 10) {
        rhs += p * (in[i] - '0');
    }
    return is;
}
std::ostream &operator<<(std::ostream &os, i128 const &rhs){
    std::string res;
    for (i128 tmp = (rhs < 0 ? -rhs : rhs); tmp; tmp /= 10)
        res += '0' + tmp % 10;
    if (rhs < 0) res += '-';
    if (rhs == 0) res += '0';
    for (auto i = res.rbegin(); i != res.rend(); ++i)
        os << *i;
    return os;
}
#endif
std::istream &operator>>(std::istream &is, bool &rhs) { i32 in; is >> in; rhs = in; return is; }
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
/* functions */
#if __cplusplus >= 202002L
void print(auto &&...args) { ((cout << args), ...); }
void input(auto &&...args) { ((cin >> args), ...); }
#endif
template <typename T> void inline unique(std::vector<T> &cont) { cont.erase(std::unique(cont.begin(), cont.end()), cont.end()); }
std::mt19937_64 ru64(142);
/* clang-format on */

#define PRECALCULATE__ 0
#define MULTITEST__ 0

struct solution {
    vi32 mid;
    p<i32, vi32> appealing(i32 n)
    {
        std::uniform_real_distribution<f64> r01(0, 1);
        vi32 a(n);
        std::iota(all(a), 0);
        std::shuffle(all(a), ru64);
        if (mid.size())
            a = mid;
        vi32 cl(2 * n), cr(2 * n);
        i32 cost_c = 0;
        for (i32 i = 0; i < n; ++i) {
            cost_c += cl[i + a[i]] + cr[n - 1 - i + a[i]];
            ++cl[i + a[i]];
            ++cr[n - 1 - i + a[i]];
        }
        auto recalc = [&](i32 i, i32 j) -> i32 {
            i32 cost_n = cost_c;
            --cl[i + a[i]];
            --cr[n - 1 - i + a[i]];
            cost_n -= cl[i + a[i]] + cr[n - 1 - i + a[i]];
            --cl[j + a[j]];
            --cr[n - 1 - j + a[j]];
            cost_n -= cl[j + a[j]] + cr[n - 1 - j + a[j]];
            std::swap(a[i], a[j]);
            cost_n += cl[i + a[i]] + cr[n - 1 - i + a[i]];
            ++cr[n - 1 - i + a[i]];
            ++cl[i + a[i]];
            cost_n += cl[j + a[j]] + cr[n - 1 - j + a[j]];
            ++cr[n - 1 - j + a[j]];
            ++cl[j + a[j]];
            return cost_n;
        };
        f64 t = 1.0;
        f64 q = 0.999;
        for (i32 k = 0; k < n * n; ++k, t *= q) {
            if (k == n)
                mid = a;
            i32 i = ru64() % n;
            i32 j = ru64() % n;
            i32 cost_n = recalc(i, j);
            if (cost_n == 0)
                return { cost_n, a };
            if (cost_n < cost_c || std::exp((cost_c - cost_n) / t) > r01(ru64)) {
                cost_c = cost_n;
            } else {
                recalc(i, j);
            }
        }
        return { cost_c, a };
    }
    auto operator()(i32 n_test = 0) -> void // solve
    {
        i32 n;
        cin >> n;
        for (;;) {
            auto [c, a] = appealing(n);
            if (c == 0) {
                for (auto&& i : a)
                    ++i;
                cout << a << '\n';
                return;
            }
        }
    }
    void static precalculate();
};

auto main(i32 argc, char* argv[], char* envp[]) -> i32 /* clang-format off */ {
    cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
    std::setlocale(LC_ALL, "Russian");
#if REDIRECT__
    cin.open("/Users/dmitrii/xcode_solution/xcode_solution/input.txt");
    cout.open("/Users/dmitrii/xcode_solution/xcode_solution/output.txt");
#endif
#if PRECALCULATE__
    solution::precalculate();
#endif
#if MULTITEST__
    i32 t; cin >> t; for (i32 i = 0; i < t; i++) {
        solution solve; solve(i);
    }
#else
    solution solve; solve();
#endif
#if REDIRECT__
    cin.close();
    cout.close();
#endif
    return 0;
} /* clang-format on */
