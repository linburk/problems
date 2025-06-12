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
    while (a.length() != b.length()){
        if (a.size() < b.size())
            a.insert(a.begin(), '0');
        else
            b.insert(b.begin(), '0');
    }
    vector<int> val1(1000, 0), val2(1000, 0);
    for (int i = 0; i < a.length(); i++){
        val1[i] = a[a.size() - i - 1] - '0';
        val2[i] = b[b.size() - i - 1] - '0';
    }
    vector<int> valres(1000, 0);
    for (int i = 0; i < 1000; i++){
        for (int j = 0; j < 1000; j++){
            valres[i + j] += val1[j] * val2[i];
        }
    }
    for (int i = 0; i < 1000; i++){
        valres[i + 1] += valres[i] / 10;
        valres[i] %= 10;
    }
    string ans;
    for (int i = 0; i < 1000; i++){
        ans += to_string(valres[i]);
    }
    std::reverse(ans.begin(), ans.end());
    while (ans[0] == '0' and ans.size() > 1)
        ans.erase(ans.begin());
    cout << ans;
}

int32_t main() {
    setlocale(LC_ALL, "Russian");
#ifndef __APPLE__
    $FASTSTREAM
#endif
    solve();
    return 0;
}