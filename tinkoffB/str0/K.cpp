#include <iostream>
#include <functional>
#include <vector>
#include <set>

struct trie
{
    int const static bit_c = 31;
    struct node
    {
        int to[2];
        int count = 0;
    };
    std::vector<node> tr;
    trie() { tr.resize(1); }
    void dfs(int x, bool oper, int pos = 0, int n = 0) {
        oper ? ++tr[n].count : --tr[n].count;
        if (pos == bit_c + 1)
            return;
        int bit = (x & (1 << (bit_c - pos))) >> (bit_c - pos);
        if (!tr[n].to[bit]) {
            tr[n].to[bit] = tr.size();
            tr.push_back(node());
        }
        dfs(x, oper, pos + 1, tr[n].to[bit]);
    }
    int count(int x, int y, int pos = 0, int n = 0, int res = 0) {
        if (pos == bit_c + 1)
            return res;
        int bit = ((x & (1 << (bit_c - pos))) >> (bit_c - pos)) ^ ((y & (1 << (bit_c - pos))) >> (bit_c - pos));
        if (tr[n].to[bit ^ 1] && tr[tr[n].to[bit ^ 1]].count)
            return count(x, y, pos + 1, tr[n].to[bit ^ 1], res ^ (1 << (bit_c - pos)));
        else
            return count(x, y, pos + 1, tr[n].to[bit], res);
    }
};

int main()
{
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    int t;
    std::cin >> t;
for (; t--; )
{
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<int, int> > > gr(n);
    for (int i = 0; i < n - 1; ++i) {
        int v, u, w;
        std::cin >> v >> u >> w;
        --v, --u;
        gr[v].push_back({u, w});
        gr[u].push_back({v, w});
    }
    int add = 0;
    std::vector<int> dp(n);
    std::vector<int> depth(n, -1);
    std::function<void(int, int)> dfs = [&] (int v, int pr) {
        depth[v] = depth[pr] + 1;
        for (auto [to, w] : gr[v]) {
            if (to == pr) continue;
            dp[to] = dp[v] ^ w;
            dfs(to, v);
        }
    };
    dfs(0, 0);
    trie tr_odd, tr_even;
    for (int i = 0; i < n; ++i) {
        if (depth[i] & 1)
            tr_odd.dfs(dp[i], 1);
        else
            tr_even.dfs(dp[i], 1);
    }
    for (int i = 0; i < m; ++i) {
        char cmd;
        std::cin >> cmd;
        if (cmd == '^') {
            int y;
            std::cin >> y;
            add ^= y;
        }
        if (cmd == '?') {
            int v, x;
            std::cin >> v >> x;
            --v;
            x ^= dp[v];
            if (depth[v] & 1) {
                x ^= add;
                tr_odd.dfs(dp[v], 0);
            } else {
                tr_even.dfs(dp[v], 0);
            }
            int res = std::max(tr_odd.count(x, add), tr_even.count(x, 0));
            std::cout << res << '\n';
            if (depth[v] & 1)
                tr_odd.dfs(dp[v], 1);
            else
                tr_even.dfs(dp[v], 1);
        }
    }
}
}
