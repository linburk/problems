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
    int n, m, q;
    cin >> n >> m >> q;
    vector<i64> a(n);
    for (auto&& i : a)
        cin >> i;
    vector<vector<int>> gr(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        gr[a].push_back(b);
        gr[b].push_back(a);
    }
    int block = 555;
    vector<bool> big(n);
    vector<vector<int>> gr_big(n);
    vector<i64> big_add(n);
    for (int i = 0; i < n; ++i) {
        if (gr[i].size() > block) {
            big[i] = 1;
            for (auto to : gr[i]) {
                gr_big[to].push_back(i);
            }
        }
    }
    for (int i = 0; i < q; ++i) {
        char c;
        cin >> c;
        if (c == '+') {
            int v, x;
            cin >> v >> x;
            --v;
            if (big[v]) {
                big_add[v] += x;
            } else
                for (auto to : gr[v]) {
                    a[to] += x;
                }
        } else {
            int v;
            cin >> v;
            --v;
            i64 rs = a[v];
            for (auto to : gr_big[v])
                rs += big_add[to];
            cout << rs << "\n";
        }
    }
}
