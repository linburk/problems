#include <bits/stdc++.h>
#include <climits>
namespace /* clang-format off */ {
namespace /* aliases */ {
#define all(cont) cont.begin(), cont.end()
using i8 = std::int8_t; using i16 = std::int16_t; using i32 = std::int32_t; using i64 = std::int64_t;
using u8 = std::uint8_t; using u16 = std::uint16_t; using u32 = std::uint32_t; using u64 = std::uint64_t; using f64 = long double;
using pi32 = std::pair<i32, i32>; using vpi32 = std::vector<pi32>; using vvpi32 = std::vector<vpi32>; using pi64 = std::pair<i64, i64>;  using vpi64 = std::vector<pi64>; using vvpi64 = std::vector<vpi64>;
using vi32 = std::vector<i32>; using vvi32 = std::vector<vi32>; using vi64 = std::vector<i64>; using vvi64 = std::vector<vi64>;
using vb = std::vector<bool>; using vvb = std::vector<vb>; using vc = std::vector<char>; using vvc = std::vector<vc>;
using si32 = std::set<i32>; using spi32 = std::set<pi32>; using si64 = std::set<i64>; using spi64 = std::set<pi64>;
using mpi32 = std::map<i32, i32>; using umpi32 = std::unordered_map<i32, i32>; using mpi64 = std::map<i64, i64>;  using umpi64 = std::unordered_map<i64, i64>;
}
namespace /* in/out op. overloadings */ {
template <typename T, typename V> std::istream &operator>>(std::istream &is, std::pair<T, V> &p) { is >> p.first >> p.second; return is; }
template <typename T> std::istream &operator>>(std::istream &is, std::vector<T> &cont) { for (auto &i : cont) { is >> i; } return is; }
template <typename T, typename V, char SEP1 = ' ', char SEP2 = '\n'> std::ostream &operator<<(std::ostream &os, std::pair<T, V> const &p) { os << p.first << SEP1 << p.second << SEP2; return os; }
template <typename T, char SEP1 = '\0', char SEP2 = '\n'> std::ostream &operator<<(std::ostream &os, const std::vector<T> &cont) { for (const auto &i : cont) { os << i; if (SEP1) os << SEP1; } os << SEP2; return os; }
}
namespace /* functions */ {
template <char SEP = ' '> void debug(auto&&...args) { ((std::cout << args << SEP), ...); std::cout << "\n"; }
template <typename T> void inline unique(std::vector<T> &cont) { cont.erase(std::unique(cont.begin(), cont.end()), cont.end()); }
std::mt19937_64 randu64(std::chrono::steady_clock().now().time_since_epoch().count());
}
using std::vector, std::string, std::pair, std::cin, std::cout;
} /* clang-format on */
#define REDIRECT 1 && __APPLE__
#define MULTITEST 1
const i32 SZ = 4E6 + 1;
class st {
    struct node {
        i32 pref, suff, val;
        i32 sz;
    };
    vector<node> tree;
    i32 size;
    void relax(node& n, node& ls, node& rs)
    {
        n.sz = ls.sz + rs.sz;
        n.pref = ls.pref;
        n.suff = rs.suff;
        if (ls.sz == ls.pref)
            n.pref += rs.pref;
        if (rs.sz == rs.suff)
            n.suff += ls.suff;
        n.val = std::max({ ls.val, rs.val, ls.suff + rs.pref });
    }
    void p_build(i32 l, i32 r, i32 n)
    {
        if (l == r - 1) {
            tree[n].pref = tree[n].suff = tree[n].val = tree[n].sz = 1;
            return;
        }
        i32 m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
        p_build(l, m, ls);
        p_build(m, r, rs);
        relax(tree[n], tree[ls], tree[rs]);
    }
    void p_update(i32 pos, i32 val, i32 l, i32 r, i32 n)
    {
        if (l > pos || r <= pos)
            return;
        if (l == r - 1) {
            tree[n].val = tree[n].pref = tree[n].suff = val;
            return;
        }
        i32 m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
        p_update(pos, val, l, m, ls);
        p_update(pos, val, m, r, rs);
        relax(tree[n], tree[ls], tree[rs]);
    }
    node p_get(i32 lq, i32 rq, i32 l, i32 r, i32 n)
    {
        if (lq >= r || rq <= l)
            return { 0, 0, 0, 0 };
        if (lq <= l && r <= rq) {
            return tree[n];
        }
        i32 m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
        node ql = p_get(lq, rq, l, m, ls);
        node qr = p_get(lq, rq, m, r, rs);
        node res;
        relax(res, ql, qr);
        return res;
    }

public:
    st(i32 sz)
        : size(sz)
    {
        tree.resize(4 * size);
        p_build(0, size, 1);
    }
    void update(i32 pos, i32 val) { return p_update(pos, val, 0, size, 1); }
    i32 get(i32 lq, i32 rq) { return p_get(lq, rq, 0, size, 1).val; }
} tree(SZ);

void solve()
{
    i32 n;
    cin >> n;
    vi32 a(n);
    cin >> a;
    std::stack<i32> added;
    for (i32 i = 0; i < n; ++i)
        tree.update(a[i] - 1, 0);
    i32 m;
    cin >> m;
    for (; m--;) {
        char op;
        i32 x;
        cin >> op >> x;
        if (op == '+')
            added.push(x);
        if (op == '+' || op == '-') {
            tree.update(x - 1, op == '-');
        }
        if (op == '?') {
            i32 l = 0, r = SZ;
            while (r - l > 1) {
                i32 m = (l + r) >> 1;
                tree.get(0, m) >= x ? r = m : l = m;
            }
            cout << r + 1 - x << " ";
        }
    }
    cout << "\n";
    for (auto i : a)
        tree.update(i - 1, 1);
    while (added.size()) {
        tree.update(added.top() - 1, 1);
        added.pop();
    }
}

#define PRECALCULATE 0
void precalc();
i32 main(i32 argc, char* argv[]) /* clang-format off */ {
    std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false); setlocale(LC_ALL, "Russian");
#if REDIRECT
    std::freopen("/Users/dmitrii/Documents/Code/Code/input.txt", "r", stdin);
    std::freopen("/Users/dmitrii/Documents/Code/Code/output.txt", "w", stdout);
#endif
#if PRECALCULATE
    precalc();
#endif
#if MULTITEST
    i32 t; std::cin >> t; for (i32 i = 0; i < t; i++)
#endif
    solve();
    return 0;
} /* clang-format on */
