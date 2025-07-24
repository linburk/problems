#include <algorithm>
#include <array>
#include <deque>
#include <functional>
#include <iostream>
#include <vector>

using std::cin, std::cout;
using std::vector, std::array, std::deque, std::pair;

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
    int g = 0;
    bool z = 1;
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        z &= a == 1;
        g ^= a;
    }
    g ^= z;
    cout << (g ? "FIRST" : "SECOND") << "\n";
}
