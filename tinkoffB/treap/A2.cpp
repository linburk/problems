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

std::mt19937 ru32(42);

struct treap {
private:
    struct node {
        int val;
        int size = 1;
        int l = 0, r = 0;
    };
    vector<node> tr;
    int size(int n) { return n ? tr[n].size : 0; }
    int val(int n) { return n ? tr[n].val : 0; }
    void update(int n) { n ? tr[n].size = size(tr[n].l) + 1 + size(tr[n].r) : 0; }
    pair<int, int> split(int k, int n)
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
    int merge(int l, int r)
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
    int root = 0;

public:
    treap()
    {
        tr.resize(1);
    }
    void push_back(int x)
    {
        tr.push_back(node());
        tr.back().val = x;
        root = merge(root, tr.size() - 1);
    }
    void move(int l, int r)
    {
        auto [ln, rtn] = split(l, root);
        auto [mn, rn] = split(r - l, rtn);
        ln = merge(mn, ln);
        root = merge(ln, rn);
    }
    int get(int i)
    {
        auto [ln, rtn] = split(i, root);
        auto [mn, rn] = split(1, rtn);
        int res = tr[mn].val;
        ln = merge(ln, mn);
        root = merge(ln, rn);
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
    int n, m;
    cin >> n >> m;
    treap tr;
    for (int i = 0; i < n; ++i)
        tr.push_back(i + 1);
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        --l;
        tr.move(l, r);
    }
    for (int i = 0; i < n; ++i) {
        cout << tr.get(i) << " ";
    }
    cout << "\n";
}
