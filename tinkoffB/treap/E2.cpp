#pragma GCC optimize("unroll-loops,Ofast")
#pragma GCC target("avx2,avx,sse4.2,sse4.1,sse4,sse3,sse2,sse")

#include <algorithm>
#include <bitset>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using std::cin, std::cout, std::string;
using std::vector, std::pair, std::bitset;

using i64 = long long;

std::mt19937 ru32(42);

struct treap {
private:
    struct node {
        int val;
        bitset<10000> sval;
        int size = 1;
        int l = 0, r = 0;
        node() { val = -1; }
        node(i64 val_)
        {
            val = val_;
            sval[val] = 1;
        }
    };
    vector<node> tr;
    int root = 0;
    auto size(int n) { return n ? tr[n].size : 0; }
    auto val(int n) { return tr[n].val; }
    auto& sval(int n) const { return tr[n].sval; }
    auto update(int n)
    {
        if (!n)
            return;
        tr[n].size = size(tr[n].l) + 1 + size(tr[n].r);
        tr[n].sval = sval(tr[n].l) | sval(tr[n].r);
        tr[n].sval[tr[n].val] = 1;
    }
    auto split(int k, int n) -> pair<int, int>
    {
        if (!n)
            return { 0, 0 };
        if (size(tr[n].l) < k) {
            auto [l, r] = split(k - size(tr[n].l) - 1, tr[n].r);
            tr[n].r = l;
            update(n);
            return { n, r };
        } else {
            auto [l, r] = split(k, tr[n].l);
            tr[n].l = r;
            update(n);
            return { l, n };
        }
    }
    auto merge(int l, int r)
    {
        if (!l)
            return r;
        if (!r)
            return l;
        if (size(l) > ru32() % (size(l) + size(r))) {
            tr[l].r = merge(tr[l].r, r);
            update(l);
            return l;
        } else {
            tr[r].l = merge(l, tr[r].l);
            update(r);
            return r;
        }
    }
    auto add_node()
    {
        int v;
        v = static_cast<int>(tr.size());
        tr.push_back(node());
        return v;
    }
    int pos(int n, int k)
    {
        if (tr[n].val == k) {
            return size(tr[n].l);
        }
        if (sval(tr[n].l)[k]) {
            return pos(tr[n].l, k);
        } else {
            return size(tr[n].l) + 1 + pos(tr[n].r, k);
        }
    }
    vector<int> ans;
    void dfs(int n)
    {
        if (!n)
            return;
        if (tr[n].l)
            dfs(tr[n].l);
        ans.push_back(tr[n].val);
        if (tr[n].r)
            dfs(tr[n].r);
    }

public:
    treap() { tr.resize(1); }
    auto push_back(int x)
    {
        int v = add_node();
        tr[v] = node(x);
        root = merge(root, v);
    }
    auto swap(int l1, int r1, int l2, int r2)
    {
        auto [ln, rnt1] = split(l1, root);
        auto [mn1, rnt2] = split(r1 - l1, rnt1);
        auto [mn, rnt3] = split(l2 - r1, rnt2);
        auto [mn2, rn] = split(r2 - l2, rnt3);
        root = merge(ln, mn2);
        root = merge(root, mn);
        root = merge(root, mn1);
        root = merge(root, rn);
    }
    auto find(int k)
    {
        return pos(root, k);
    }
    auto at(int i)
    {
        auto [ln, rnt] = split(i, root);
        auto [mn, rn] = split(3, rnt);
        dfs(mn);
        auto res = ans;
        ans.clear();
        root = merge(ln, mn);
        root = merge(root, rn);
        return res;
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
#if 1
    int n, q;
    cin >> n >> q;
    treap tr;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        tr.push_back(x - 1);
    }
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int l1, r1, l2, r2;
            cin >> l1 >> r1 >> l2 >> r2;
            --l1, --l2;
            tr.swap(l1, r1, l2, r2);
        } else {
            int x;
            cin >> x;
            --x;
            int j = tr.find(x);
            auto ans = tr.at(j + 1);
            for (auto k : ans)
                cout << k + 1 << " ";
            for (int j = 0; j < 3 - ans.size(); ++j)
                cout << "-1 ";
            cout << "\n";
        }
    }
#else
    test();
#endif
}
