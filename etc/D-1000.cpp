#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using i64 = long long;
using std::cin, std::cout, std::vector;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<i64> a(n), b(m);
    for (auto&& i : a)
        cin >> i;
    for (auto&& i : b)
        cin >> i;
    if (n < m) {
        std::swap(n, m);
        std::swap(a, b);
    }
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    vector<i64> pr_a(n / 2 + 1), pr_b(m / 2 + 1);
    for (int i = 0; i < n / 2; ++i) {
        pr_a[i + 1] = pr_a[i] + a[n - i - 1] - a[i];
    }
    for (int i = 0; i < m / 2; ++i) {
        pr_b[i + 1] = pr_b[i] + b[m - i - 1] - b[i];
    }
    int max_k = 0;
    vector<i64> res;
    for (int i = 1, pj = 0;; ++i, ++max_k) {
        i64 c = -1;
        int mj = -1;
        for (int j = std::max(0, pj - 2); j <= std::min({ i, n / 2, pj + 2 }); ++j) {
            if (j + 2 * (i - j) <= m && (i - j) + 2 * j <= n && (i - j) <= m) {
                if (pr_a[j] + pr_b[i - j] > c) {
                    c = pr_a[j] + pr_b[i - j];
                    mj = j;
                }
            }
        }
        if (c == -1)
            break;
        pj = mj;
        res.push_back(c);
    }
    cout << max_k << "\n";
    for (int i = 0; i < max_k; ++i) {
        cout << res[i] << " \n"[i == max_k - 1];
    }
}

int main()
{
#ifdef __APPLE__
    std::freopen("/Users/dmitrii/xcode_solution/xcode_solution/input.txt", "r", stdin);
    std::freopen("/Users/dmitrii/xcode_solution/xcode_solution/output.txt", "w", stdout);
#endif
    int t;
    cin >> t;
    for (; t--;)
        solve();
    return 0;
}
