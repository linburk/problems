#include <bitset>
#include <deque>
#include <functional>
#include <iostream>
#include <vector>

using std::cin, std::cout;
using std::vector, std::bitset, std::deque, std::pair;

int main()
{
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
#ifdef __APPLE__
    std::freopen(std::getenv("FINPATH"), "r", stdin);
    std::freopen(std::getenv("FOUTPATH"), "w", stdout);
#endif
    int n, r;
    cin >> n >> r;
    --r;
    vector<vector<pair<int, int>>> gr(n);
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        gr[a].push_back({ b, i });
        gr[b].push_back({ a, i });
    }
    vector<int> g(n);
    std::function<int(int, int)> dfs = [&](int v, int p) {
        for (auto [to, i] : gr[v]) {
            if (to != p)
                g[v] ^= dfs(to, v) + 1;
        }
        return g[v];
    };
    std::function<int(int, int, int)> dfs2 = [&](int v, int p, int s) {
        for (auto [to, i] : gr[v]) {
            if (i != p) {
                if (g[to] == (s ^ g[v]) - 1)
                    return i;
                int c = dfs2(to, i, (s ^ g[v] ^ (g[to] + 1)) - 1);
                if (c)
                    return c;
            }
        }
        return 0;
    };
    int rs = dfs(r, r);
    cout << (rs ? 1 : 2) << "\n";
    if (rs) {
        cout << dfs2(r, 0, 0) << "\n";
    }
}
