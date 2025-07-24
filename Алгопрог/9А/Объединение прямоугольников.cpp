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

struct rect {
    i64 x, y1, y2;
    i8 event;
};

struct segment_tree final {
private:
    struct node {
        i64 val = 0;
        i32 cnt = 0;
        i32 bonus = 0;
    };
    vector<node> tree;
    i32 size;
    void relax(node &n, node &ls, node &rs) {
        if (ls.cnt == rs.cnt) {
            n.cnt = ls.cnt;
            n.val = ls.val + rs.val;
        } else if (ls.cnt < rs.cnt) {
            n.cnt = ls.cnt;
            n.val = ls.val;
        } else {
            n.cnt = rs.cnt;
            n.val = rs.val;
        }
    }
    void push(i32 n, i32 ls, i32 rs) {
        if (tree[n].bonus) {
            tree[n].cnt += tree[n].bonus;
            if (rs < tree.size()) {
                tree[ls].bonus += tree[n].bonus;
                tree[rs].bonus += tree[n].bonus;
            }
            tree[n].bonus = 0;
        }
    }
    void p_update(i32 lq, i32 rq, i32 val, i32 l, i32 r, i32 n) {
        i32 m = (l+r)>>1, ls = n<<1, rs = n<<1|1;
        push(n, ls, rs);
        if (l >= rq || lq >= r) return;
        if (lq <= l && r <= rq) {
            tree[n].bonus += val;
            push(n, ls, rs);
            return;
        }
        p_update(lq, rq, val, l, m, ls);
        p_update(lq, rq, val, m, r, rs);
        relax(tree[n], tree[ls], tree[rs]);

    }
    void p_build(vi64 const &a, i32 l, i32 r, i32 n) {
        i32 m = (l+r)>>1, ls = n<<1, rs = n<<1|1;
        if (l == r-1) {
            tree[n].val = a[l];
            return;
        }
        p_build(a, l, m, ls);
        p_build(a, m, r, rs);
        relax(tree[n], tree[ls], tree[rs]);
    }
public:
    segment_tree(vi64 const &a) {
        size = (i32)a.size();
        tree.resize(4*size);
        p_build(a, 0, size, 1);
    }
    void update(i32 lq, i32 rq, i32 val) {
        return p_update(lq, rq, val, 0, size, 1);
    }
    i64 get() {
        push(1, 2, 3);
        return tree[1].val;
    }
};

void solve() {
    i32 n;
    cin >> n;
    vector<rect> events;
    si64 allY;
    events.reserve(2 * n);
    for (i32 i = 0; i < n; ++i) {
        i32 x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        events.push_back({x1, y1, y2, 1});
        events.push_back({x2, y1, y2, -1});
        allY.insert(y1); allY.insert(y2);
    }
    vi64 vY(all(allY));
    std::sort(all(events), [](rect const &a, rect const &b) -> bool {
        return a.x < b.x;
    });
    i64 allS = (vY.back() - vY.front()) * (events.back().x - events.front().x);
    std::map<i64, i32> code;
    for (i32 i = 0; i < vY.size(); ++i) {
        code[vY[i]] = i;
    }
    vi64 diff(2 * vY.size(), 0);
    for (i32 i = 0; i < vY.size()-1; ++i) {
        diff[i] = vY[i+1] - vY[i];
    }
    segment_tree tree(diff);
    for (i32 i = 0; i < events.size(); ++i) {
        if (i) allS -= tree.get() * (events[i].x - events[i-1].x);
        if (events[i].y2 > events[i].y1) tree.update(code[events[i].y1], code[events[i].y2], events[i].event);
    }
    cout << allS << "\n";
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