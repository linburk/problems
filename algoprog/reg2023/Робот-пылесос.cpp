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

struct event_rect {
    i32 x, y1, y2;
    bool event;
};

struct segment_tree final {
private:
    struct node {
        i32 val = 0;
        i32 cnt = 0;
        i32 bonus = 0;
        i32 DEFAULT = 0;
    };
    vector<node> tree;
    i32 size;
    void relax(i32 n, i32 ls, i32 rs) {
        tree[n].val = tree[ls].val + tree[rs].val;
    }
    void push(i32 n, i32 ls, i32 rs) {
        if (tree[n].bonus) {
            tree[ls].bonus = tree[rs].bonus = tree[n].bonus;
            tree[ls].cnt += tree[n].bonus;
            tree[rs].cnt += tree[n].bonus;
            tree[ls].val = (tree[ls].cnt > 0) * tree[ls].DEFAULT;
            tree[rs].val = (tree[rs].cnt > 0) * tree[rs].DEFAULT;
            tree[n].bonus = 0;
        }
    }
    void p_update(i32 ql, i32 qr, i32 cnt, i32 l, i32 r, i32 n) {
        if (l >= qr || r <= ql) return;
        if (ql <= l && r <= qr) {
            tree[n].cnt += cnt;
            tree[n].bonus += cnt;
            tree[n].val = (tree[n].cnt > 0) * tree[n].DEFAULT;
            return;
        }
        i32 m = (l+r)>>1, ls = n<<1, rs = n<<1|1;
        push(n, ls, rs);
        p_update(ql, qr, cnt, l, m, ls);
        p_update(ql, qr, cnt, m, r, rs);
        relax(n, ls, rs);
    }
    
    i32 p_get(i32 ql, i32 qr, i32 l, i32 r, i32 n) {
        if (l >= qr && r <= ql) return 0;
        if (ql <= l && r <= qr) {
            return tree[n].val;
        }
        i32 m = (l+r)>>1, ls = n<<1, rs = n<<1|1;
        push(n, ls, rs);
        return p_get(ql, qr, l, m, ls) +  p_get(ql, qr, m, r, rs);
    }
    void p_build(vi32 const &a, i32 l, i32 r, i32 n) {
        if (l == r-1) {
            tree[n].DEFAULT = a[l+1] - a[l];
            return;
        }
        i32 m = (l+r) >> 1, ls = n<<1, rs = n<<1|1;
        p_build(a, l, m, ls);
        p_build(a, m, r, rs);
        tree[n].DEFAULT = tree[ls].DEFAULT + tree[rs].DEFAULT;
    }
public:
    segment_tree (i32 n, vi32 const &&a) {
        size = n;
        tree.resize(4*size);
        p_build(a, 0, size, 1);
    }
    
    void update(i32 ql, i32 qr, i32 cnt) {
        return p_update(ql, qr, cnt, 0, size, 1);
    }
    
    i32 get(i32 ql, i32 qr) {
        return p_get(ql, qr, 0, size, 1);
    }
    
    
};

void solve() {
    i32 k, n;
    cin >> k >> n;
    vector<event_rect> rects;
    rects.reserve(2 * n + 2);
    i32 x1 = 0, x2 = k, y1 = 0, y2 = k;
    rects.push_back({x1, y1, y2, 0});
    rects.push_back({x2, y1, y2, 1});
    for (i32 i = 1; i <= n; ++i) {
        char C;
        i32 d;
        cin >> C >> d;
        i32 px1 = x1, px2 = x2, py1 = y1, py2 = y2;
        if (C == 'E') {
            x1 += d, x2 += d;
            rects.push_back({px2, y1, y2, 0});
            rects.push_back({x2, y1, y2, 1});
        }
        if (C == 'W') {
            x1 -= d, x2 -= d;
            rects.push_back({x1, y1, y2, 0});
            rects.push_back({px1, y1, y2, 1});
        }
        if (C == 'N') {
            y1 += d, y2 += d;
            rects.push_back({x1, py2, y2, 0});
            rects.push_back({x2, py2, y2, 1});
        }
        if (C == 'S') {
            y1 -= d, y2 -= d;
            rects.push_back({x1, y1, py1, 0});
            rects.push_back({x2, y1, py1, 1});
        }
    }
    std::sort(all(rects), [](event_rect const &a, event_rect const &b) -> bool {
        if (a.x == b.x) return a.event > b.event;
        return a.x < b.x;
    });
    mpi32 compressed;
    si32 allY;
    for (auto [x, y1, y2, event] : rects) {
        allY.insert(y1);
        allY.insert(y2);
    }
    for (auto Y : allY) {
        compressed[Y] = (i32)compressed.size();
    }
    segment_tree tree((i32)compressed.size()-1, vi32(all(allY)));
    i64 ans = 0;
    for (i32 i = 0; i < rects.size(); ++i) {
        if (i)
        ans += (tree.get(0, (i32)compressed.size()-1)) * (rects[i].x - rects[i-1].x);
        tree.update(compressed[rects[i].y1], compressed[rects[i].y2], rects[i].event ? -1 : 1);
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