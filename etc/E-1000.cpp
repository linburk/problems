#include <functional>
#include <iostream>
#include <vector>

using i32 = int;
using i64 = long long;
using std::cin, std::cout, std::vector, std::pair;

i32 virt_sz;
struct st {
private:
    struct nd {
        i32 val = 0;
        i32 ls = -1, rs = -1;
    };
    i32 real_sz;
    vector<nd> tr;
    void add(i32 i, i32 val, i32 l, i32 r, i32 n)
    {
        tr[n].val += val;
        if (l == r - 1)
            return;
        i32 m = (l + r) >> 1;
        if (i < m) {
            if (tr[n].ls == -1) {
                tr[n].ls = tr.size();
                tr.push_back(nd());
            }
            add(i, val, l, m, tr[n].ls);
        } else {
            if (tr[n].rs == -1) {
                tr[n].rs = tr.size();
                tr.push_back(nd());
            }
            add(i, val, m, r, tr[n].rs);
        }
    }
    i32 get(i32 ql, i32 qr, i32 l, i32 r, i32 n)
    {
        if (l >= qr || r <= ql || n == -1)
            return 0;
        if (ql <= l && r <= qr)
            return tr[n].val;
        i32 m = (l + r) >> 1;
        return get(ql, qr, l, m, tr[n].ls) + get(ql, qr, m, r, tr[n].rs);
    }
    void merge(st& t, i32 l, i32 r, i32 n)
    {
        if (n == -1)
            return;
        if (l == r - 1) {
            add(real_sz - t.size() + l, t.tr[n].val, 0, virt_sz, 0);
            return;
        }
        i32 m = (l + r) >> 1;
        merge(t, l, m, t.tr[n].ls);
        merge(t, m, r, t.tr[n].rs);
    }

public:
    st()
    {
        real_sz = 0;
        tr.resize(1);
    }
    void merge(st& t)
    {
        merge(t, 0, virt_sz, 0);
    }
    void up()
    {
        add(real_sz, 1, 0, virt_sz, 0);
        ++real_sz;
    }
    i32 size()
    {
        return real_sz;
    }
    i32 get(i32 ql, i32 qr)
    {
        return get(real_sz - qr, real_sz - ql, 0, virt_sz, 0);
    }
};

void solve()
{
    i32 n;
    cin >> n;
    vector<vector<i32>> gr(n);
    for (i32 i = 1; i < n; ++i) {
        i32 u, v;
        cin >> u >> v;
        --u, --v;
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    virt_sz = n + 1;
    i64 res = 0;
    std::function<st(i32, i32)> dfs = [&](i32 v, i32 p) {
        st cur;
        for (auto to : gr[v]) {
            if (to == p)
                continue;
            auto son = dfs(to, v);
            if (son.size() > cur.size())
                std::swap(son, cur);
            for (i32 d = 0; d < son.size(); ++d) {
                res += (2LL * d + 1) * son.get(d, d + 1) * cur.get(d, cur.size());
                res += (2LL * d + 1) * cur.get(d, d + 1) * son.get(d + 1, son.size());
            }
            cur.merge(son);
        }
        cur.up();
        return cur;
    };
    dfs(0, 0);
    cout << res << '\n';
}

i32 main()
{
#ifndef __APPLE__
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#else
    std::freopen("/Users/dmitrii/xcode_solution/xcode_solution/input.txt", "r", stdin);
    std::freopen("/Users/dmitrii/xcode_solution/xcode_solution/output.txt", "w", stdout);
#endif
    i32 t;
    cin >> t;
    for (; t--;) {
        solve();
    }
    return 0;
}
