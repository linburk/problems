#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<int> z_func(std::string &s) {
    std::vector<int> z(s.size());
    for (int i = 1, l = 0, r = 0; i < s.size(); ++i) {
        if (i <= r)
            z[i] = std::min(r - i + 1, z[i - l]);
        for (; i + z[i] < s.size() && s[i + z[i]] == s[z[i]]; )
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}
int main()
{
    int n, m;
    std::cin >> n >> m;
    std::string s;
    std::cin >> s;
    std::vector<std::string> p(n);
    for (auto &&str : p)
        std::cin >> str;
    std::vector<std::vector<int> > pos(n);
    for (int i = 0; i < n; ++i) {
        std::string ns = p[i] + '#' + s;
        auto z = z_func(ns);
        for (int j = p[i].size(); j < ns.size(); ++j) {
            if (z[j] == p[i].size()) {
                pos[i].push_back(j - p[i].size() - 1);
            }
        }
    }
    for (int i = 0; i < n; ++i)
        std::sort(pos[i].begin(), pos[i].end());
    std::vector<int> dp(1 << n, s.size());
    dp[0] = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i))
                continue;
            auto n_pos = std::lower_bound(pos[i].begin(), pos[i].end(), dp[mask]);
            if (n_pos != pos[i].end())
                dp[mask ^ (1 << i)] = std::min(dp[mask ^ (1 << i)], *n_pos + static_cast<int>(p[i].size()));
        }
    }
    std::cout << (dp.back() == s.size() ? -1 : dp.back()) << '\n';
}
