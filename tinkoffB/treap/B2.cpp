#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <vector>

using std::cin, std::cout, std::string;
using std::vector, std::queue, std::array, std::pair;

using i64 = long long;

std::mt19937 ru32(42);

struct treap {
private:
    struct node {
        i64 val;
        i64 sum;
        int size = 1;
        int l = 0, r = 0;
        node(i64 val_)
        {
            val = val_;
            sum = 1ll * val * val;
        }
    };
    vector<node> tr;
    auto size(int n) { return n ? tr[n].size : 0; }
    auto val(int n) { return n ? tr[n].val : 0; }
    auto sum(int n) { return n ? tr[n].sum : 0; }
    auto update(int n)
    {
        if (!n)
            return;
        tr[n].size = size(tr[n].l) + 1 + size(tr[n].r);
        tr[n].sum = sum(tr[n].l) + tr[n].val * tr[n].val + sum(tr[n].r);
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
    vector<int> pool;
    int root = 0;
    auto next_node()
    {
        int v;
        if (!pool.empty()) {
            v = pool.back();
            pool.pop_back();
        } else {
            v = static_cast<int>(tr.size());
            tr.push_back(node(0));
        }
        return v;
    }

public:
    treap()
    {
        tr.resize(1, node(0));
    }
    auto push_back(int x)
    {
        int v = next_node();
        tr[v] = node(x);
        root = merge(root, v);
    }
    auto insert(int i, i64 x)
    {
        auto [ln, rn] = split(i, root);
        int v = next_node();
        tr[v] = node(x);
        root = merge(ln, v);
        root = merge(root, rn);
    }
    auto erase(int i)
    {
        auto [ln, rtn] = split(i, root);
        auto [mn, rn] = split(1, rtn);
        pool.push_back(mn);
        root = merge(ln, rn);
    }
    auto add(int i, i64 x)
    {
        auto [ln, rtn] = split(i, root);
        auto [mn, rn] = split(1, rtn);
        tr[mn] = node(val(mn) + x);
        root = merge(ln, mn);
        root = merge(root, rn);
    }
    auto at(int i)
    {
        auto [ln, rtn] = split(i, root);
        auto [mn, rn] = split(1, rtn);
        i64 res = val(mn);
        root = merge(ln, mn);
        root = merge(root, rn);
        return res;
    }
    auto value()
    {
        return sum(root);
    }
    auto size()
    {
        return size(root);
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
    int n, _;
    cin >> n >> _;
    treap tr;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        tr.push_back(x);
    }
    int k;
    cin >> k;
    cout << tr.value() << "\n";
    for (int i = 0; i < k; ++i) {
        int e, v;
        cin >> e >> v;
        --v;
        i64 val = tr.at(v);
        tr.erase(v);
        if (e == 2) {
            tr.insert(v, val / 2);
            tr.insert(v + 1, (val + 1) / 2);
        } else {
            if (v == 0) {
                tr.add(v, val);
            } else if (v == tr.size()) {
                tr.add(v - 1, val);
            } else {
                tr.add(v - 1, val / 2);
                tr.add(v, (val + 1) / 2);
            }
        }
        //        for (int i = 0; i < tr.size(); ++i) {
        //            cout << tr.at(i) << " ";
        //        }
        //        cout << "\n";
        cout << tr.value() << "\n";
    }
}
