#include <iostream>
#include <vector>
#include <map>
#include <string>

using i64 = long long;
using pi64 = std::pair<i64, i64>;

int main() { 
    std::string str;
    std::cin >> str;
    i64 res = 0;
    int mod1 = 1E9 + 7;
    int mod2 = (1LL << 31) - 1;
    int p1 = 41;
    int p2 = 29;
    std::vector<pi64> hash(str.size() + 1);
    std::vector<pi64> pow(str.size() + 1);
    pow[0] = {1, 1};
    for (int i = 1; i <= str.size(); ++i) {
        pow[i].first = (pow[i - 1].first * p1) % mod1;
        pow[i].second = (pow[i - 1].second * p2) % mod2;
    }
    hash[0] = {1, 1};
    for (int i = 0; i < str.size(); ++i) {
        hash[i + 1].first = (hash[i].first * p1 % mod1 + str[i] - 'a') % mod1; 
        hash[i + 1].second = (hash[i].second * p2 % mod2 + str[i] - 'a') % mod2;  
    }
    auto substr = [&] (int i, int len) -> pi64 {
        return {
            (hash[i + len].first - hash[i].first * pow[len].first % mod1 + mod1) % mod1,
            (hash[i + len].second - hash[i].second * pow[len].second % mod2 + mod2) % mod2
        };
    };
    for (int k = 1; k < str.size(); ++k) {
        std::map<pi64, int> ss;
        for (int i = 0; i <= str.size() - k; ++i)
            ++ss[substr(i, k)];
        for (auto [f, s] : ss)
             res += (str.size() - k + 1 - s) * s;
    }
    std::cout << res / 2 << '\n';
}
