#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

using i32 = int;
using i64 = long long;
using u64 = unsigned long long;

using std::cin, std::cout;
using std::vector, std::array, std::deque, std::pair, std::string;

std::mt19937 ru32(42);

struct treap {
    struct node {
        int val;
        int size = 1;
        int l = 0, r = 0;
        node() { }
        node(int val_)
        {
            val = val_;
        }
    };
    vector<node> tr;
    int root = 0;
    auto size(int n) { return n ? tr[n].size : 0; }
    auto val(int n) { return tr[n].val; }
    auto update(int n)
    {
        if (!n)
            return;
        tr[n].size = size(tr[n].l) + 1 + size(tr[n].r);
    }
    auto split(int k, int n) -> pair<int, int>
    {
        if (!n)
            return { 0, 0 };
        n = copy(n);
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
            l = copy(l);
            tr[l].r = merge(tr[l].r, r);
            update(l);
            return l;
        } else {
            r = copy(r);
            tr[r].l = merge(l, tr[r].l);
            update(r);
            return r;
        }
    }
    int copy(int n = 0)
    {
        tr.push_back(n ? tr[n] : node());
        return tr.size() - 1;
    }

public:
    treap()
    {
        tr.resize(1);
        tr.reserve(10E6);
    }
    auto push_back(int x)
    {
        int v = copy();
        tr[v] = node(x);
        root = merge(root, v);
    }
    auto move(int l1, int r1, int l2, int r2)
    {
        auto [ln, rt] = split(l1, root);
        auto [mn, rn] = split(r1 - l1, rt);
        root = merge(ln, merge(mn, rn));
        auto [ln2, rt2] = split(l2, root);
        auto [mn2, rn2] = split(r2 - l2, rt2);
        root = merge(ln2, merge(mn, rn2));
    }
    vector<int> res;
    void dfs(int n)
    {
        if (!n)
            return;
        dfs(tr[n].l);
        res.push_back(tr[n].val);
        dfs(tr[n].r);
    }
    vector<int> get()
    {
        res.clear();
        dfs(root);
        return res;
    }
};

struct query {
    int l1, r1, l2, r2;
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
    vector<query> q;
    for (int i = 0; i < m; ++i) {
        int count, from, to;
        cin >> count >> from >> to;
        --from, --to;
        q.push_back({ from, from + count, to, to + count });
    }
    treap tr;
    for (int i = 0; i < n; ++i)
        tr.push_back(i);
    int c = 0;
    while (!q.empty()) {
        auto [l1, r1, l2, r2] = q.back();
        q.pop_back();
        if (++c == 555) {
            vector<int> a = tr.get();
            tr.tr.clear();
            tr.tr.shrink_to_fit();
            tr = treap();
            for (auto i : a)
                tr.push_back(i);
            c = 0;
        }
        tr.move(l2, r2, l1, r1);
    }
    for (auto i : tr.get()) {
        cout << i + 1 << " ";
    }
}
