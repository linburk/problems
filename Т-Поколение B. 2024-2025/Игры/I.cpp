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
    int n;
    cin >> n;
    i64 f = 0;
    auto count = [&](i64 x) {
        switch (x % 4) {
        case 0:
            return x;
        case 1:
            return 1ll;
        case 2:
            return x + 1;
        case 3:
            return 0ll;
        default:
            return 0ll;
        }
    };
    vector<pair<i64, i64>> a;
    for (int i = 0; i < n; ++i) {
        i64 l, r;
        cin >> l >> r;
        a.push_back({ l, r });
        f ^= count(r) ^ count(l - 1);
    }
    if (f) {
        cout << "Win\n";
        int d = 63 - __builtin_clzll(f);
        for (auto [l, r] : a) {
            if ((1LL << d) & l) {
                i64 to = f ^ l;
                cout << l << " " << to << "\n";
                return 0;
            }
            if ((1LL << d) & r) {
                i64 to = f ^ r;
                cout << r << " " << to << "\n";
                return 0;
            }
            if ((l ^ (1 << d)) <= r) {
                cout << (l ^ (1 << d)) << " " << l << "\n";
                return 0;
            }
        }
        assert(0);
    } else {
        cout << "Lose\n";
    }
}
