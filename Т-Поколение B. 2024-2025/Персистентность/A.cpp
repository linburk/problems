#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using std::cin, std::cout, std::string;
using std::vector, std::pair;

struct node {
    int prev = 0;
    long long sum = 0;
};
vector<node> snow { node() };

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
    for (int i = 0; i < n; ++i) {
        int idx, m;
        cin >> idx >> m;
        if (m == 0) {
            snow.push_back(snow[snow[idx].prev]);
        } else {
            snow.push_back(snow[idx]);
            snow.back().sum += m;
            snow.back().prev = idx;
        }
    }
    long long res = 0;
    for (int i = 0; i < n + 1; ++i) {
        res += snow[i].sum;
    }
    cout << res << '\n';
}
