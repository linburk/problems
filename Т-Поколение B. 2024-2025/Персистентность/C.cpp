#include <algorithm>
#include <cassert>
#include <random>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <bitset>

using std::cin, std::cout, std::string;
using std::vector, std::pair, std::bitset;

using i64 = long long;

struct st {
private:
    struct nd {
        int val;
        int l = 0, r = 0;
    };
    vector<nd> tr;
    int sz;
    int upd(int i, int val, int l, int r, int n) {
        tr.push_back(tr[n]);
        n = tr.size() - 1;
        if (l == r - 1) {
            tr[n].val = val;
        } else {
            int m = (l + r) >> 1;
            if (i < m)
                tr[n].l = upd(i, val, l, m, tr[n].l);
            else
                tr[n].r = upd(i, val, m, r, tr[n].r);
        }
        return n;
    }
    int get(int i, int l, int r, int n) {
        if (l == r - 1)
            return tr[n].val;
        int m = (l + r) >> 1;
        if (i < m)
            return get(i, l, m, tr[n].l);
        else
            return get(i, m, r, tr[n].r);
    }
public:
    st(int n) { sz = n; tr.resize(1); }
    int upd(int i, int val, int vers) {
        return upd(i, val, 0, sz, vers);
    }
    int get(int i, int vers) {
        return get(i, 0, sz, vers);
    }
};

struct state {
    int l, r;
    int vers;
};

int main() {
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
#ifdef __APPLE__
    std::freopen(std::getenv("FINPATH"), "r", stdin);
    std::freopen(std::getenv("FOUTPATH"), "w", stdout);
#endif
    int n;
    cin >> n;
    st tr(n);
    vector<state> vers;
    vers.push_back({0, 0, 0});
    for (int i = 0; i < n; ++i) {
        int t, v;
        cin >> t >> v;
        auto [l, r, idx] = vers[v];
        if (t > 0) {
            int x;
            cin >> x;
            idx = tr.upd(r, x, idx);
            vers.push_back({l, ++r, idx});
        } else {
            cout << tr.get(l, idx) << "\n";
            vers.push_back({++l, r, idx});
        }
    }
}

