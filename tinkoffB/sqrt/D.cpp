#include <algorithm>
#include <array>
#include <cassert>
#include <deque>
#include <functional>
#include <iostream>
#include <numeric>
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
        gr[b].push_back(a);
    }
    vector<int> order(n);
    std::iota(order.begin(), order.end(), 0);
    auto cmp = [&](int a, int b) {
        return gr[a].size() < gr[b].size() || gr[a].size() == gr[b].size() && a < b;
    };
    std::sort(order.begin(), order.end(), cmp);
    for (auto v : order)
        std::sort(gr[v].begin(), gr[v].end(), cmp);
    int res = 0;
    vector<int> cnt(n);
    for (auto v : order) {
        for (auto to : gr[v])
            ++cnt[to];
        for (auto to : gr[v]) {
            if (cmp(v, to))
                break;
            for (auto w : gr[to]) {
                if (cmp(to, w))
                    break;
                res += cnt[w];
            }
        }
        for (auto to : gr[v])
            --cnt[to];
    }
    cout << res << "\n";
}
