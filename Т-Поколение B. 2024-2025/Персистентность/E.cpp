#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <vector>

using std::cin, std::cout;
using std::vector, std::pair, std::map;

using i64 = long long;

struct st {
private:
    struct nd {
        int val;
        int l = 0, r = 0;
    };
    vector<nd> tr;
    int sz;
    int upd(int i, int l, int r, int n)
    {
        tr.push_back(tr[n]);
        n = tr.size() - 1;
        if (l == r - 1) {
            tr[n].val = 1;
        } else {
            int m = (l + r) >> 1;
            if (i < m)
                tr[n].l = upd(i, l, m, tr[n].l);
            else
                tr[n].r = upd(i, m, r, tr[n].r);
            tr[n].val = tr[tr[n].l].val + tr[tr[n].r].val;
        }
        return n;
    }
    int get(int ql, int qr, int l, int r, int n)
    {
        if (l >= qr || r <= ql || !n)
            return 0;
        if (ql <= l && r <= qr)
            return tr[n].val;
        int m = (l + r) >> 1;
        return get(ql, qr, l, m, tr[n].l) + get(ql, qr, m, r, tr[n].r);
    }

public:
    st(int n)
    {
        sz = n;
        tr.resize(1);
    }
    int set(int i, int vers)
    {
        return upd(i, 0, sz, vers);
    }
    int get(int ql, int qr, int vers)
    {
        return get(ql, qr, 0, sz, vers);
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
    vector<int> a(n);
    for (auto&& i : a)
        cin >> i;
    int sz;
    {
        vector<int> b = a;
        std::sort(b.begin(), b.end());
        b.erase(std::unique(b.begin(), b.end()), b.end());
        std::map<int, int> match;
        for (int i = 0; i < b.size(); ++i) {
            match[b[i]] = i;
        }
        for (int i = 0; i < a.size(); ++i) {
            a[i] = match[a[i]];
        }
        sz = b.size();
    }
    st tr(n + 1);
    vector<int> last(sz, n);
    vector<int> vers(n + 1);
    for (int i = n - 1; i >= 0; --i) {
        vers[i] = tr.set(last[a[i]], vers[i + 1]);
        last[a[i]] = i;
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l;
        cout << r - l - tr.get(l, r, vers[l]) << "\n";
    }
}
