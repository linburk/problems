#include <algorithm>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

using i64 = long long;
using std::cin, std::cout, std::vector, std::pair;

struct st {
private:
    struct nd {
        int pos = -1;
        int val = -1;
    };
    vector<nd> tr;
    int sz;
    nd merge(nd l, nd r)
    {
        if (r.val != -1)
            return r;
        else
            return l;
    }
    void upd(int i, int val, int l, int r, int n)
    {
        if (l == r - 1) {
            tr[n].val = val;
            tr[n].pos = l;
            return;
        }
        upd(i, val, l, (l + r) >> 1, n << 1);
        upd(i, val, (l + r) >> 1, r, n << 1 | 1);
        tr[n] = merge(tr[n << 1], tr[n << 1 | 1]);
    }
    nd get(int ql, int qr, int l, int r, int n)
    {
        if (l >= qr || r <= ql) {
            return nd {};
        }
        if (ql <= l && r <= qr) {
            return tr[n];
        }
        nd L = get(ql, qr, l, (l + r) >> 1, n << 1);
        nd R = get(ql, qr, (l + r) >> 1, r, n << 1 | 1);
        return merge(L, R);
    }

public:
    st(int n)
    {
        sz = n;
        tr.resize(4 * sz);
    }
    pair<int, int> get(int ql, int qr)
    {
        nd res = get(ql, qr, 0, sz, 1);
        return { res.pos, res.val };
    }
    void upd(int i, int val)
    {
        return upd(i, val, 0, sz, 1);
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> gr(n);
    vector<int> w(n);
    int u_c;
    {
        vector<int> vals(n);
        for (int i = 0; i < n; ++i) {
            cin >> w[i];
            vals[i] = w[i];
        }
        std::sort(vals.begin(), vals.end());
        vals.erase(std::unique(vals.begin(), vals.end()), vals.end());
        u_c = vals.size();
        std::unordered_map<int, int> code;
        for (int i = 0; i < vals.size(); ++i) {
            code[vals[i]] = i;
        }
        for (int i = 0; i < n; ++i) {
            w[i] = code[w[i]];
        }
    }
    vector<pair<int, int>> v(n);
    vector<pair<int, int>> up(n);
    vector<int> w_up(u_c, -1);
    for (int i = 0; i < n; ++i) {
        v[i] = { w[i], i };
    }
    std::sort(v.begin(), v.end());
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    st tr(u_c);
    std::function<void(int, int)> dfs = [&](int v, int p) {
        auto t = tr.get(w[v], w[v] + 1);
        auto r = tr.get(0, w[v] + 1);
        up[v] = { r.first, r.second };
        tr.upd(w[v], v);
        for (auto to : gr[v]) {
            if (to != p) {
                dfs(to, v);
            }
        }
        tr.upd(w[v], t.second);
    };
    dfs(0, 0);
    for (int i = n - 1; i >= 0; --i) {
        auto [cw, u] = v[i];
        if (up[u].first != cw - 1) {
            for (int j = 0; j < n; ++j) {
                if (w[j] == cw - 1) {
                    cout << j + 1 << "\n";
                    return;
                }
            }
        } else if (w_up[cw] != -1 && w_up[cw] != up[u].second) {
            cout << up[u].second + 1 << "\n";
            return;
        } else {
            w_up[cw] = up[cw].second;
        }
    }
    cout << "0\n";
}

int main()
{
#ifndef __APPLE__
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    int t;
    cin >> t;
    for (; t--;) {
        solve();
    }
}
