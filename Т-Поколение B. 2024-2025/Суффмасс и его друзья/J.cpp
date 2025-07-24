#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <deque>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using i64 = long long;

using std::cin, std::cout;
using std::vector, std::array, std::deque, std::pair, std::function, std::string;

vector<int> f_z(string const& s)
{
    vector<int> z(s.size());
    for (int i = 1, l = 0, r = 0; i < s.size(); ++i) {
        if (i <= r)
            z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            r = i + z[i] - 1, l = i;
    }
    return z;
}

int rep(bool left, int len, int k1, int k2)
{
    return std::min(len, k1) - std::max(1, len - k2) + 1 - (std::min(len, k1) == len && left);
}

int main()
{
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
#ifdef __APPLE__
    std::freopen(std::getenv("FINPATH"), "r", stdin);
    std::freopen(std::getenv("FOUTPATH"), "w", stdout);
#endif
    auto gz = [](vector<int> const& z, int i) {
        return i >= 0 && i < z.size() ? z[i] : 0;
    };
    string s;
    while (cin >> s) {
        if (s == "0")
            break;
        i64 rs = 0;
        function<void(string)> rec = [&](string s) {
            int n = s.size();
            if (n == 1)
                return;
            int l_len = n / 2;
            int r_len = n - l_len;
            string l = s.substr(0, l_len);
            string r = s.substr(l_len);
            string rl(l.rbegin(), l.rend());
            string rr(r.rbegin(), r.rend());
            rec(l);
            rec(r);
            vector<int>
                z1 = f_z(rl),
                z2 = f_z(r + "#" + l),
                z3 = f_z(rl + "#" + rr),
                z4 = f_z(r);
            for (int m = 0; m < n; m++) {
                int len, k1, k2;
                if (m < l_len) {
                    len = l_len - m;
                    k1 = gz(z1, l_len - m);
                    k2 = gz(z2, r_len + 1 + m);
                } else {
                    len = m - l_len + 1;
                    k1 = gz(z3, l_len + 1 + r_len - 1 - (m - l_len));
                    k2 = gz(z4, (m - l_len) + 1);
                }
                if (k1 + k2 >= len) {
                    rs += rep(m < l_len, len, k1, k2);
                }
            }
        };
        rec(s);
        cout << rs << "\n";
    }
    return 0;
}
