#include <iostream>
#include <vector>

using i64 = long long;

using std::cin, std::cout;
using std::vector, std::pair;

vector<vector<pair<int, i64>>> gr;
vector<i64> dp;
vector<i64> sz;

void dfs1(int v, int p)
{
    for (auto [to, w] : gr[v]) {
        if (to != p) {
            dfs1(to, v);
            sz[v] += sz[to];
            dp[v] += dp[to] + w * sz[to];
        }
    }
}
void dfs2(int v, int p)
{
    for (auto [to, w] : gr[v]) {
        if (to != p) {
            dp[to] += dp[v] - dp[to] - w * sz[to] + w * (sz[v] - sz[to]);
            sz[to] = sz[v];
            dfs2(to, v);
        }
    }
}

int main()
{
    cin.tie(0);
    std::ios::sync_with_stdio(false);
    int n;
    cin >> n;
    gr.resize(n);
    dp.resize(n, 0);
    sz.resize(n, 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        --a, --b;
        gr[a].push_back({ b, w });
        gr[b].push_back({ a, w });
    }
    dfs1(0, -1);
    dfs2(0, -1);
    for (auto i : dp)
        cout << i << " ";
    return 0;
}
