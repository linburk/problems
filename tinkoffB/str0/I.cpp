#include <iostream>
#include <vector>
#include <map>
#include <string>

int main()
{
    using i64 = long long;
    using pi64 = std::pair<i64, i64>;
    const int mod1 = 1E9+7;
    const int mod2 = 1E9+3;
    const short p1 = 13;
    const short p2 = 47;
    std::vector<pi64> pow(300001);
    pow[0] = {1, 1};
    for (int i = 0; i < 300000; ++i)
        pow[i + 1] = {pow[i].first * p1 % mod1, pow[i].second * p2 % mod2}; 
    int t;
    std::cin >> t;
for (; t--; ) {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> table(n);
    for (int i = 0; i < n; ++i)
        std::cin >> table[i];
    std::map<pi64, int> count;
    int max_r = 0;
    int ri = 0, rj = 0;
    for (int i = 0; i < m; ++i) {
        std::vector<pi64> pref_hash(n);
        std::vector<pi64> suff_hash(n);
        for (int j = 0; j < n - 1; ++j)
            pref_hash[j + 1] = {(pref_hash[j].first + (table[j][i] == '0' ? 1 : 2) * pow[j].first % mod1) % mod1, 
                                (pref_hash[j].second + (table[j][i] == '0' ? 1 : 2) * pow[j].second % mod2) % mod2};
        for (int j = n - 1; j > 0; --j)
            suff_hash[j - 1] = {(suff_hash[j].first + (table[j][i] == '0' ? 1 : 2) * pow[j].first % mod1) % mod1,
                                (suff_hash[j].second + (table[j][i] == '0' ? 1 : 2) * pow[j].second % mod2) % mod2};
        for (int j = 0; j < n; ++j) {
            pi64 hash = {(((pref_hash[j].first + (table[j][i] == '0' ? 2 : 1) * pow[j].first % mod1) % mod1) + suff_hash[j].first) % mod1,
                        (((pref_hash[j].second + (table[j][i] == '0' ? 2 : 1) * pow[j].second % mod2) % mod2) + suff_hash[j].second) % mod2};
            ++count[hash];
            if (count[hash] > max_r) {
                max_r = count[hash];
                ri = i, rj = j;
            }
        }
    }
    std::cout << max_r << '\n';
    std::string ans(n, '0');
    for (int j = 0; j < n; ++j) {
        if (j == rj) {
            if (table[j][ri] == '0')
                ans[j] = '1';
        } else {
            if (table[j][ri] == '1')
                ans[j] = '1';
        }
    }
    std::cout << ans << '\n';
}
}
