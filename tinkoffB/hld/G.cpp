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
    cin >> in;
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
std::mt19937_64 ru64(std::chrono::steady_clock().now().time_since_epoch().count());
/* clang-format on */

#define PRECALCULATE__ 0
#define MULTITEST__ 0

struct st {
    vi32 tr;
    i32 sz;
    st() { }
    st(vi32& a)
    {
        sz = a.size();
        tr.resize(2 * sz);
        for (i32 i = 0; i < sz; ++i) {
            tr[i + sz] = a[i];
        }
        for (i32 i = sz - 1; i > 0; --i) {
            tr[i] = std::max(tr[i << 1], tr[i << 1 | 1]);
        }
    }
    i32 get(i32 l, i32 r)
    {
        l += sz, r += sz;
        i32 rs = INT_MIN;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                rs = std::max(rs, tr[l++]);
            if (r & 1)
                rs = std::max(rs, tr[--r]);
        }
        return rs;
    }
    void upd(i32 i, i32 val)
    {
        i += sz;
        tr[i] = val;
        for (i >>= 1; i; i >>= 1) {
            tr[i] = std::max(tr[i << 1], tr[i << 1 | 1]);
        }
    }
};

struct solution {
    i32 const bit = 17;
    i32 n, k;
    st tr;
    vvi32 gr;
    vvi32 up;
    vi32 sz;
    vi32 w;
    vi32 head;
    vi32 in, out, d;
    vi32 tour;
    i32 t = 0;
    void dfs0(i32 v, i32 p)
    {
        if (v)
            gr[v].erase(std::find(all(gr[v]), p));
        d[v] = d[p] + 1;
        up[v][0] = p;
        for (i32 i = 1; i < bit; ++i)
            up[v][i] = up[up[v][i - 1]][i - 1];
        for (auto to : gr[v]) {
            dfs0(to, v);
            sz[v] += sz[to];
        }
        std::sort(all(gr[v]), [this](i32 a, i32 b) {
            return sz[a] > sz[b];
        });
    }
    void dfs1(i32 v)
    {
        in[v] = t++;
        tour.push_back(w[v]);
        if (gr[v].size()) {
            head[gr[v][0]] = head[v];
            dfs1(gr[v][0]);
        }
        for (i32 j = 1; j < gr[v].size(); ++j) {
            i32 to = gr[v][j];
            head[to] = to;
            dfs1(to);
        }
        out[v] = t;
    }
    i32 lca(i32 a, i32 b)
    {
        if (d[a] <= d[b])
            std::swap(a, b);
        for (i32 i = bit - 1; i >= 0; --i) {
            if (d[up[a][i]] >= d[b])
                a = up[a][i];
        }
        if (a == b)
            return a;
        for (i32 i = bit - 1; i >= 0; --i) {
            if (up[a][i] != up[b][i])
                a = up[a][i], b = up[b][i];
        }
        return up[a][0];
    }
    i32 get_path(i32 a, i32 b)
    {
        i32 rs = INT_MIN;
        for (; d[head[a]] > d[b]; a = up[head[a]][0])
            rs = std::max(rs, tr.get(in[head[a]], in[a] + 1));
        rs = std::max(rs, tr.get(in[b], in[a] + 1));
        return rs;
    }
    i32 get(i32 a, i32 b)
    {
        i32 ab = lca(a, b);
        return std::max(get_path(a, ab), get_path(b, ab));
    }
    void upd(i32 v, i32 val)
    {
        tr.upd(in[v], val);
    }
    auto operator()() -> void // solve
    {
        cin >> n;
        gr.resize(n);
        w.resize(n);
        cin >> w;
        for (i32 i = 1; i < n; ++i) {
            i32 u, v;
            cin >> u >> v;
            --u, --v;
            gr[u].push_back(v);
            gr[v].push_back(u);
        }
        sz.resize(n, 1);
        up.resize(n, vi32(bit));
        in.resize(n);
        out.resize(n);
        head.resize(n);
        d.resize(n);
        dfs0(0, 0);
        dfs1(0);
        tr = st(tour);
        cin >> k;
        for (i32 i = 0; i < k; ++i) {
            char c;
            cin >> c;
            if (c == '!') {
                i32 v, h;
                cin >> v >> h;
                --v;
                upd(v, h);
            } else {
                i32 u, v;
                cin >> u >> v;
                --u, --v;
                cout << get(u, v) << '\n';
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
#endif
    solution solve; solve();
#if MULTITEST__
    }
#endif
#if REDIRECT__
    cin.close();
    cout.close();
#endif
    return 0;
} /* clang-format on */
