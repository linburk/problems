#include <algorithm>
#include <array>
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
    i64 n;
    cin >> n;
    i64 st = 0;
    for (int i = 2; st < n; ++i) {
        if (__builtin_popcount(i) == 1) {
            st += i;
        } else {
            st += i;
            if (st != n)
                st += i;
        }
    }
    cout << (n == st ? "LOSE" : "WIN") << "\n";
}
