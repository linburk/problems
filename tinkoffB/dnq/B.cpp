#include <iostream>
#include <list>
#include <numeric>
#include <unordered_map>
#include <vector>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,avx,sse4.2,sse4.1,sse4,sse3")

using std::cin, std::cout;
using std::vector, std::unordered_map, std::pair, std::list;

using u64 = unsigned long long;
using u32 = unsigned int;

struct dsu {
    vector<int> sz;
    vector<int> anc;
    int comp;
    struct state {
        int a, b, anc;
    };
    vector<state> ch;
    dsu(int n)
    {
        comp = n;
        sz.resize(n, 1);
        anc.resize(n);
        std::iota(anc.begin(), anc.end(), 0);
    }
    int leader(int v)
    {
        return v == anc[v] ? v : leader(anc[v]);
    }
    void unite(int a, int b)
    {
        a = leader(a), b = leader(b);
        if (sz[a] > sz[b])
            std::swap(a, b);
        if (a == b) {
            ch.push_back({ -1, -1, -1 });
            return;
        }
        ch.push_back(state { a, b, anc[a] });
        anc[a] = b;
        sz[b] += sz[a];
        --comp;
    }
    void pop()
    {
        auto [a, b, pr] = ch.back();
        ch.pop_back();
        if (a == -1)
            return;
        anc[a] = pr;
        sz[b] -= sz[a];
        ++comp;
    }
    dsu() { }
};

struct st {
    struct nd {
        bool qr = 0;
        list<u64> edges;
    };
    dsu d;
    vector<nd> tr;
    vector<int> ans;
    int sz;
    void add(int ql, int qr, u64 e, int l, int r, int n)
    {
        if (l >= qr || r <= ql)
            return;
        if (ql <= l && r <= qr) {
            tr[n].edges.push_back(e);
            return;
        }
        int m = (l + r) >> 1;
        add(ql, qr, e, l, m, n << 1);
        add(ql, qr, e, m, r, n << 1 | 1);
    }
    void set(int i, int l, int r, int n)
    {
        tr[n].qr = 1;
        if (l == r - 1)
            return;
        int m = (l + r) >> 1;
        if (i < m)
            set(i, l, m, n << 1);
        else
            set(i, m, r, n << 1 | 1);
    }
    void dfs(int l, int r, int n)
    {
        if (!tr[n].qr)
            return;
        for (auto e : tr[n].edges)
            d.unite(e >> 32, static_cast<u32>(e));
        if (l + 1 == r) {
            ans.push_back(d.comp);
        } else {
            int m = (l + r) >> 1;
            dfs(l, m, n << 1);
            dfs(m, r, n << 1 | 1);
        }
        for (int i = 0; i < tr[n].edges.size(); ++i)
            d.pop();
    }
    st(int n, int k)
    {
        sz = k;
        tr.resize(4 * sz);
        d = dsu(n);
    }
    void set(int i)
    {
        set(i, 0, sz, 1);
    }
    void add(int ql, int qr, u64 e)
    {
        return add(ql, qr, e, 0, sz, 1);
    }
    auto calc()
    {
        dfs(0, sz, 1);
        return ans;
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
    int n, k;
    cin >> n >> k;
    if (k == 0)
        return 0;
    unordered_map<u64, int> cur;
    cur.max_load_factor(0.25);
    st tr(n, k);
    for (int i = 0; i < k; ++i) {
        char c;
        cin >> c;
        if (c == '?') {
            tr.set(i);
        }
        if (c == '+') {
            u64 a, b;
            cin >> a >> b;
            --a, --b;
            if (a > b)
                std::swap(a, b);
            cur[a << 32 | b] = i;
        }
        if (c == '-') {
            u64 a, b;
            cin >> a >> b;
            --a, --b;
            if (a > b)
                std::swap(a, b);
            tr.add(cur[a << 32 | b], i + 1, a << 32 | b);
            cur[a << 32 | b] = -1;
        }
    }
    for (auto [f, s] : cur) {
        if (s != -1)
            tr.add(s, k, f);
    }
    auto ans = tr.calc();
    for (auto i : ans)
        cout << i << "\n";
}
