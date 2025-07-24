#include <algorithm>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

using i32 = int;
using i64 = long long;
using std::cin, std::cout, std::vector, std::pair;

struct dsu {
    vector<i32> ar, rk;
    struct log {
        i32 a, b, rkb, ara;
    };
    i32 sz;
    vector<log> ch;
    dsu(i32 n)
    {
        sz = n;
        ar.resize(n);
        rk.resize(n);
        std::iota(ar.begin(), ar.end(), 0);
    }
    i32 leader(i32 a)
    {
        return ar[a] == a ? a : leader(ar[a]);
    }
    void unite(i32 a, i32 b, bool fl = 0)
    {
        a = leader(a), b = leader(b);
        if (a == b)
            return;
        if (rk[a] > rk[b])
            std::swap(a, b);
        if (fl) {
            ch.push_back({ .a = a,
                .b = b,
                .rkb = rk[b],
                .ara = ar[a] });
        }
        --sz;
        rk[b] = std::max(rk[b], rk[a] + 1);
        ar[a] = b;
    }
    void roll()
    {
        for (; ch.size(); ch.pop_back()) {
            auto [a, b, rkb, ara] = ch.back();
            rk[b] = rkb;
            ar[a] = ara;
            ++sz;
        }
    }
};

struct edge {
    i32 a, b, k;
};

bool operator<(edge const& lhs, edge const& rhs)
{
    if (lhs.k == rhs.k) {
        if (lhs.a == rhs.a) {
            return lhs.b < rhs.b;
        }
        return lhs.a < rhs.a;
    }
    return lhs.k < rhs.k;
}

void solve()
{
    i32 n, q;
    cin >> n >> q;
    i32 BSZ = 700;
    vector<pair<i32, dsu>> bk {
        { 0, dsu(n) }
    };
    std::set<edge> eg;
    auto rebuild = [&] {
        bk.erase(bk.begin() + 1, bk.end());
        i32 c = BSZ;
        i32 lk = -1;
        for (auto [a, b, k] : eg) {
            if (c >= BSZ && lk != k) {
                bk.push_back({ k, bk.back().second });
                c = 0;
            }
            bk.back().second.unite(a, b);
            bk.back().first = k;
            ++c;
            lk = k;
        }
    };
    auto add = [&](edge e) {
        eg.insert(e);
        for (i32 i = 1; i < bk.size(); ++i) {
            if (e.k <= bk[i].first) {
                bk[i].second.unite(e.a, e.b);
            }
        }
    };
    auto ans = [&](i32 p) -> i32 {
        i32 i = 0;
        for (; i < bk.size(); ++i) {
            if (bk[i].second.sz <= p) {
                --i;
                break;
            }
        }
        if (i == bk.size())
            --i;
        i32 ck = bk[i].first;
        for (auto st = eg.upper_bound(edge { .a = 0, .b = 0, .k = ck }); bk[i].second.sz > p && st != eg.end(); st = next(st)) {
            auto [a, b, k] = *st;
            bk[i].second.unite(a, b, 1);
            ck = k;
        }
        bool r = bk[i].second.sz == p;
        bk[i].second.roll();
        return r ? ck : -1;
    };
    for (i32 i = 0, c = 0; i < q; ++i) {
        char t;
        cin >> t;
        if (t == '+') {
            i32 a, b, k;
            cin >> a >> b >> k;
            --a, --b;
            add({ a, b, k });
            if (++c == BSZ) {
                rebuild();
                c = 0;
            }
        } else {
            i32 p;
            cin >> p;
            if (p == n) {
                cout << "0\n";
            } else {
                cout << ans(p) << "\n";
            }
        }
    }
}

i32 main()
{
#ifndef __APPLE__
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
#else
    std::freopen("/Users/dmitrii/xcode_solution/xcode_solution/input.txt", "r", stdin);
    std::freopen("/Users/dmitrii/xcode_solution/xcode_solution/output.txt", "w", stdout);
#endif
    solve();
    return 0;
}
