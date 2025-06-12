#include <stdio.h>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>

#ifdef __APPLE__
#include <fstream>
std::ifstream input("input.txt");
std::ofstream output("output.txt");
#define cin input
#define cout output
#endif

using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

#define endl '\n'
#define all(cont) cont.begin(), cont.end()
#define pb(x) emplace_back(x)
#define $FASTSTREAM \
  std::cin.tie(0);  \
  std::cout.tie(0); \
  std::ios_base::sync_with_stdio(false);

namespace tools {

    template<typename T>
    T gcd(T a, T b){
        while (b > 0){
            a %= b;
            std::swap(a, b);
        }
        return a;
    }

    template<typename T>
    T lcm(T a, T b) {
        return a * b / gcd(a, b);
    }

    template<typename T>
    std::istream &operator>>(std::istream &is, std::vector<T> &array){
        for (auto &i : array){
            is >> i;
        }
        return is;
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &array){
        for (const auto& i : array){
            os << i << " ";
        }
        return os;
    }

    template<typename T>
    std::istream &operator>>(std::istream &is, std::vector<std::vector<T> > &matrix) {
        for (auto &i: matrix)
            for (auto &j: i)
                is >> j;
        return is;
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const std::vector<std::vector<T> > &matrix) {
        for (const auto &i : matrix) {
            for (const auto &j: i)
                os << j << " ";
            os << "\n";
        }
        return os;
    }

} // namespace tools

using namespace tools;

void solve() {
    string a, b;
    getline(cin, a);
    getline(cin, b);
    size_t maxs = max(b.size(), a.size()) + 1;
    vector<int> ans(maxs + 1, 0);
    int da = maxs - a.size(), db = maxs - b.size();
    for (int i = a.size() - 1; i >= 0; i--){
        ans[i + da + 1] += a[i] - '0';
    }
    for (int i = b.size() - 1; i >= 0; i--){
        ans[i + db + 1] += b[i] - '0';
        if (ans[i + db + 1] > 9){
            ans[i + db + 1] -= 10;
            ans[i + db]++;
        }

    }
    int i = 0;
    while (ans[i] == 0)
        i++;
    for (; i < ans.size(); i++)
        cout << ans[i];
}

int32_t main() {
    setlocale(LC_ALL, "Russian");
#ifndef __APPLE__
    $FASTSTREAM
#endif
    solve();
    return 0;
}