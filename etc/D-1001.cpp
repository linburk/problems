#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using std::cin, std::cout, std::vector, std::pair;
using i64 = long long;

int main()
{
    int t;
    cin >> t;
    for (; t--;) {
        int n;
        cin >> n;
        vector<vector<int>> gr(n);
        vector<int> a(n);
        vector<int> lim(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i] >> lim[i];
        }
        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            gr[u].push_back(v);
            gr[v].push_back(u);
        }
        i64 add = 0;
        std::function<void(int, int)> dfs = [&](int v, int p) {
            for (auto to : gr[v]) {
                if (to != p) {
                    dfs(to, v);
                    a[v] = std::min(lim[v], std::max(a[v], a[to]));
                    add += std::max(0, a[to] - a[v]);
                }
            }
        };
        dfs(0, 0);
        cout << a[0] + add << '\n';
    }
    return 0;
}
