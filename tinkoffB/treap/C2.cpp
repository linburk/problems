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
            val = sum = val_;
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
        tr[n].sum = sum(tr[n].l) + tr[n].val + sum(tr[n].r);
    }
    auto split(int k, int n) -> pair<int, int>
    {
        if (!n)
            return { 0, 0 };
        if (size(tr[n].l) < k) {
            auto [l, r] = split(k - size(tr[n].l) - 1, tr[n].r);
            tr[n].r = l;
            update(n);
            update(r);
            return { n, r };
        } else {
            auto [l, r] = split(k, tr[n].l);
            tr[n].l = r;
            update(n);
            update(l);
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
    int root0 = 0, root1 = 0;
    auto next_node()
    {
        int v;
        v = static_cast<int>(tr.size());
        tr.push_back(node(0));
        return v;
    }
    int sz = 0;
    auto segment(int l, int r)
    {
        pair<int, int> odd;
        pair<int, int> even;
        odd = { l >> 1, r >> 1 };
        even = { (l + 1) >> 1, (r + 1) >> 1 };
        return pair { even, odd };
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
        ++sz;
        sz % 2 ? root0 = merge(root0, v) : root1 = merge(root1, v);
    }
    auto swap(int l, int r)
    {
        auto [f, s] = segment(l, r);
        auto [l0, r0] = f;
        auto [l1, r1] = s;
        assert(l0 < r0);
        assert(l1 < r1);
        auto [ln0, rtn0] = split(l0, root0);
        auto [mn0, rn0] = split(r0 - l0, rtn0);
        auto [ln1, rtn1] = split(l1, root1);
        auto [mn1, rn1] = split(r1 - l1, rtn1);
        root0 = merge(ln0, mn1);
        root0 = merge(root0, rn0);
        root1 = merge(ln1, mn0);
        root1 = merge(root1, rn1);
    }
    auto sum(int l, int r)
    {
        auto [f, s] = segment(l, r);
        auto [l0, r0] = f;
        auto [l1, r1] = s;
        i64 res = 0;
        if (l0 < r0) {
            auto [ln, rtn] = split(l0, root0);
            auto [mn, rn] = split(r0 - l0, rtn);
            res += sum(mn);
            root0 = merge(ln, mn);
            root0 = merge(root0, rn);
        }
        if (l1 < r1) {
            auto [ln, rtn] = split(l1, root1);
            auto [mn, rn] = split(r1 - l1, rtn);
            res += sum(mn);
            root1 = merge(ln, mn);
            root1 = merge(root1, rn);
        }
        return res;
    }
};

void test()
{
    int n = 16;
    treap tr;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        tr.push_back(i + 1);
        a[i] = i + 1;
    }
    auto swap = [&](int l, int r) {
        tr.swap(l, r);
        for (int i = l; i < r; i += 2) {
            std::swap(a[i], a[i + 1]);
        }
    };
    auto sum = [&](int l, int r) {
        int res = 0;
        for (int i = l; i < r; ++i) {
            res += a[i];
        }
        assert(res == tr.sum(l, r));
    };
    swap(0, n);
    sum(1, 11);
    for (int i = 0; i < n; ++i) {
        int l = ru32() % n;
        int r = ru32() % (n - l) + l + 1;
        sum(l, r);
    }
    cout << "\n";
}

int main()
{
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
#ifdef __APPLE__
    std::freopen(std::getenv("FINPATH"), "r", stdin);
    std::freopen(std::getenv("FOUTPATH"), "w", stdout);
#endif
#if 1
    for (int n, c = 0; cin >> n; ++c) {
        if (n == 0)
            break;
        treap tr;
        int m;
        cin >> m;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            tr.push_back(x);
        }
        cout << "Swapper " << c + 1 << ":\n";
        for (int i = 0; i < m; ++i) {
            int t, l, r;
            cin >> t >> l >> r;
            --l;
            if (t == 1) {
                tr.swap(l, r);
            } else {
                cout << tr.sum(l, r) << "\n";
            }
        }
        cout << "\n";
    }
#else
    test();
#endif
}
