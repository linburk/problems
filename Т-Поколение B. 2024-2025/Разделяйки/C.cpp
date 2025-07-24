#pragma GCC target("avx2")
#pragma GCC optimize("unroll-loops")

#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using std::cin, std::cout;
using std::string;
using u32 = unsigned int;
using u64 = unsigned long long;

void mult(const u32* __restrict a, const u32* __restrict b, u32* res, int n)
{
    if (n <= 64) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                res[i + j] += a[i] * b[j];
            }
        }
    } else {
        int mid = n / 2;
        alignas(64) u32 btmp[n], E[n];
        std::memset(btmp, 0, n * sizeof(u32));
        std::memset(E, 0, n * sizeof(u32));
        auto atmp = btmp + mid;
        for (int i = 0; i < mid; i++) {
            atmp[i] = a[i] + a[i + mid];
            btmp[i] = b[i] + b[i + mid];
        }
        mult(atmp, btmp, E, mid);
        mult(a + 0, b + 0, res, mid);
        mult(a + mid, b + mid, res + n, mid);
        for (int i = 0; i < mid; i++) {
            const auto tmp = res[i + mid];
            res[i + mid] += E[i] - res[i] - res[i + 2 * mid];
            res[i + 2 * mid] += E[i + mid] - tmp - res[i + 3 * mid];
        }
    }
}

const int n = 2 << 17;
alignas(64) u32 a[n] = { 0 };
alignas(64) u32 b[n] = { 0 };
alignas(64) u32 c[2 * n] = { 0 };
int k = 2;

string operator*(string f, string s)
{
    std::reverse(f.begin(), f.end());
    std::reverse(s.begin(), s.end());
    f += "00";
    s += "00";
    for (int i = 0; i + k < f.size(); i += k) {
        string sb = f.substr(i, k);
        std::reverse(sb.begin(), sb.end());
        a[i / k] = std::stoul(sb);
    }
    for (int i = 0; i + k < s.size(); i += k) {
        string sb = s.substr(i, k);
        std::reverse(sb.begin(), sb.end());
        b[i / k] = std::stoul(sb);
    }
    mult(a, b, c, n);
    int p10 = 1;
    for (int i = 0; i < k; ++i)
        p10 *= 10;
    for (int i = 0; i < n; ++i) {
        c[i + 1] += c[i] / p10;
        c[i] %= p10;
    }
    string res;
    for (int i = 0; i < n; ++i) {
        string sb = std::to_string(c[i]);
        std::reverse(sb.begin(), sb.end());
        while (sb.size() < k)
            sb += '0';
        res += sb;
    }
    while (res.size() > 1 && res.back() == '0')
        res.pop_back();
    std::reverse(res.begin(), res.end());
    return res;
}

int main()
{
#ifdef __APPLE__
    std::freopen(std::getenv("FINPATH"), "r", stdin);
    std::freopen(std::getenv("FOUTPATH"), "w", stdout);
#endif
    std::memset(::a, 0, n * sizeof(u32));
    std::memset(::b, 0, n * sizeof(u32));
    std::memset(c, 0, 2 * n * sizeof(u32));
    string f, s;
    cin >> f >> s;
    bool sign = f[0] == '-' ^ s[0] == '-';
    if (f[0] == '-')
        f[0] = '0';
    if (s[0] == '-')
        s[0] = '0';
    auto res = f * s;
    if (sign && res[0] != '0')
        cout << '-';
    cout << res << "\n";
}
