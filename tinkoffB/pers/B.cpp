#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using std::cin, std::cout, std::string;
using std::vector, std::pair;

struct st {
    struct nd {
        int val;
        int l = 0, r = 0;
    };
    vector<nd> tr;
    int sz;
    int upd(int i, int val, int l, int r, int n)
    {
        tr.push_back(tr[n]);
        n = tr.size() - 1;
        if (l == r - 1) {
            tr[n].val = val;
            return n;
        }
        int m = (l + r) >> 1;
        if (i < m) {
            tr[n].l = upd(i, val, l, m, tr[n].l);
        } else {
            tr[n].r = upd(i, val, m, r, tr[n].r);
        }
        return n;
    }
    int get(int i, int l, int r, int n)
    {
        if (!n)
            return 0;
        if (l == r - 1) {
            return tr[n].val;
        }
        int m = (l + r) >> 1;
        if (i < m)
            return get(i, l, m, tr[n].l);
        else
            return get(i, m, r, tr[n].r);
    }
    st(int n)
    {
        sz = n;
        tr.resize(1);
    }
    int upd(int i, int val, int vers)
    {
        return upd(i, val, 0, sz, vers);
    }
    int get(int i, int vers)
    {
        return get(i, 0, sz, vers);
    }
};

int main()
{
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
#ifdef __APPLE__
    std::freopen(std::getenv("FINPATH"), "r", stdin);
    std::freopen(std::getenv("FOUTPATH"), "w", stdout);
#endif
    int n;
    cin >> n;
    st tr(n);
    vector<int> vers(1);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        vers[0] = tr.upd(i, x, vers.back());
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        string s;
        cin >> s;
        if (s == "get") {
            int v, j;
            cin >> v >> j;
            --v;
            --j;
            cout << tr.get(j, vers[v]) << "\n";
        } else {
            int v, j, x;
            cin >> v >> j >> x;
            --v;
            --j;
            vers.push_back(tr.upd(j, x, vers[v]));
        }
    }
}
