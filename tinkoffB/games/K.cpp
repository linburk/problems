#include <algorithm>
#include <array>
#include <cassert>
#include <deque>
#include <functional>
#include <iostream>
#include <vector>

using std::cin, std::cout;
using std::vector, std::array, std::deque, std::pair;

using i64 = long long;

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
    vector<vector<int>> gr(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        gr[a].push_back(b);
    }
    vector<int> g(n);
    vector<bool> used(n);
    vector<int> c(n);
    int t = 0;
    std::function<void(int)> dfs = [&](int v) {
        ++t;
        used[v] = 1;
        for (auto to : gr[v]) {
            if (!used[to]) {
                dfs(to);
            }
        }
        for (auto to : gr[v]) {
            c[g[to]] = t;
        }
        while (c[g[v]] == t)
            ++g[v];
        ++t;
    };
    for (int i = 0; i < n; ++i) {
        if (!used[i])
            dfs(i);
        cout << g[i] << "\n";
    }
}
