#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <climits>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

using u8 = unsigned char;
using i32 = int;
using i64 = long long;
using u64 = unsigned long long;

using std::cin, std::cout;
using std::vector, std::array, std::deque, std::pair, std::string, std::bitset;

int main()
{
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
#ifdef __APPLE__
    std::freopen(std::getenv("FINPATH"), "r", stdin);
    std::freopen(std::getenv("FOUTPATH"), "w", stdout);
#endif
    int n, k;
    cin >> n >> k;
    if (n == 1) {
        cout << "0\n";
        return 0;
    }
    vector<int> gr_a(n / 2);
    vector<int> gr_b(n / 2);
    vector<int> gr_bb((n + 1) / 2);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char c;
            cin >> c;
            if (c == '0')
                continue;
            if (i < n / 2) {
                if (j < n / 2) {
                    gr_a[i] |= 1 << j;
                } else {
                    gr_b[i] |= 1 << (j - n / 2);
                }
            } else if (j >= n / 2) {
                gr_bb[i - n / 2] |= 1 << (j - n / 2);
            }
        }
    }
    vector<int> f(1 << gr_bb.size());
    int b = 0;
    for (int i = 1; i < f.size(); ++i) {
        if (i == (1 << (b + 1)))
            ++b;
        f[i] = std::max(f[i ^ (1 << b)], f[i & gr_bb[b]] + 1);
    }
    int rs = 0;
    std::function<void(int, int, int, int)> rec = [&](int v, int clq, int add, int part) {
        if (v == gr_a.size()) {
            rs = std::max(__builtin_popcount(clq) + f[part], rs);
            return;
        }
        rec(v + 1, clq, add, part);
        if (add >> v & 1)
            rec(v + 1, clq | (1 << v), add & gr_a[v], part & gr_b[v]);
    };
    rec(0, 0, (1 << gr_a.size()) - 1, (1 << gr_bb.size()) - 1);
    cout << std::setprecision(10) << std::fixed << k * k * (rs - 1) / 2.L / rs << "\n";
}
