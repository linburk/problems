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
    vector<int> a(3);
    for (auto&& i : a)
        cin >> i;
    vector<int> f(*std::max_element(a.begin(), a.end()) + 1);
    vector<int> used(f.size());
    for (int i = 1; i < f.size(); ++i) {
        for (int k = 1; k <= i - k; ++k)
            used[f[i - k]] = i;
        while (used[f[i]] == i)
            ++f[i];
    }
    int g = f[a[0]] ^ f[a[1]] ^ f[a[2]];
    if (g) {
        cout << "YES\n";
        for (int i = 0; i < 3; ++i) {
            for (int k = 1; k <= a[i] - k; ++k) {
                if ((g ^ f[a[i] - k] ^ f[a[i]]) == 0) {
                    for (int j = 0; j < 3; ++j)
                        cout << a[j] - (k * (i == j)) << " ";
                    return 0;
                }
            }
        }
    } else {
        cout << "NO\n";
    }
}
