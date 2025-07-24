#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <deque>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

using i64 = long long;

using std::cin, std::cout;
using std::vector, std::array, std::deque, std::pair, std::function;

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
    vector<vector<int>> gr(n);
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        gr[a].push_back(b);
        gr[b].push_back(a);
    }
    vector<int> sz(n, 1);
    vector<i64> dp(n);
    function<void(int, int)> dfs = [&](int v, int p) {
        for (auto to : gr[v]) {
            if (to != p) {
                dfs(to, v);
                sz[v] += sz[to];
                dp[v] += dp[to];
            }
        }
        dp[v] += sz[v];
    };
    i64 rs = 0;
    function<void(int, int)> reroot = [&](int v, int p) {
        rs = std::max(rs, dp[v]);
        for (auto to : gr[v]) {
            if (to != p) {
                dp[v] -= dp[to] + sz[to];
                sz[v] -= sz[to];
                sz[to] += sz[v];
                dp[to] += dp[v] + sz[v];
                reroot(to, v);
                dp[to] -= dp[v] + sz[v];
                sz[to] -= sz[v];
                sz[v] += sz[to];
                dp[v] += dp[to] + sz[to];
            }
        }
    };
    dfs(0, 0);
    reroot(0, 0);
    cout << rs << "\n";
    return 0;
}
