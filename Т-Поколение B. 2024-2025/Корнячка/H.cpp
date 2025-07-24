#include <algorithm>
#include <iostream>
#include <vector>

using i32 = int;
using i64 = long long;
using std::cin, std::cout, std::vector;

struct nd {
    i32 pr, nx, j;
};

i32 const JSZ = 512;
vector<nd> ls;

void ndswap(i32 x, i32 y)
{
    std::swap(ls[x].nx, ls[y].nx);
    ls[ls[y].nx].pr = y;
    ls[ls[x].nx].pr = x;
    i32 xj = x, yj = y;
    for (i32 i = 0; i < JSZ; ++i) {
        xj = ls[xj].nx;
        yj = ls[yj].nx;
    }
    for (i32 i = 0; i <= JSZ; ++i) {
        ls[x].j = xj;
        ls[y].j = yj;
        x = ls[x].pr;
        y = ls[y].pr;
        xj = ls[xj].pr;
        yj = ls[yj].pr;
    }
}
i32 up(i32 x, i32 j)
{
    for (; j >= JSZ; j -= JSZ)
        x = ls[x].j;
    for (; j--;)
        x = ls[x].nx;
    return x;
}

void solve()
{
    i32 n, q;
    cin >> n >> q;
    vector<i32> p(n);
    for (auto&& i : p) {
        cin >> i;
        --i;
    }
    ls.resize(n);
    vector<bool> used(n);
    for (i32 i = 0; i < n; ++i) {
        i32 v = i;
        if (!used[v]) {
            vector<i32> s;
            for (; !used[v]; v = ls[v].nx) {
                ls[v].nx = p[v];
                ls[ls[v].nx].pr = v;
                s.push_back(v);
                used[v] = 1;
            }
            s.push_back(v);
            for (i32 j = 0; j < JSZ; ++j) {
                v = ls[v].nx;
            }
            ls[s.back()].j = v;
            for (s.pop_back(); s.size(); s.pop_back()) {
                ls[s.back()].j = ls[ls[ls[s.back()].nx].j].pr;
            }
        }
    }
    for (i32 i = 0; i < q; ++i) {
        i32 t;
        cin >> t;
        if (t == 1) {
            i32 x, y;
            cin >> x >> y;
            ndswap(x - 1, y - 1);
        } else {
            i32 x, j;
            cin >> x >> j;
            cout << up(x - 1, j) + 1 << '\n';
        }
    }
}

i32 main()
{
#ifndef __APPLE__
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    solve();
    return 0;
}
