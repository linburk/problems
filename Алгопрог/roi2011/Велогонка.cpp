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

    template <typename T>
    T gcd(T a, T b) {
        while (b > 0) {
            a %= b;
            std::swap(a, b);
        }
        return a;
    }

    template <typename T>
    T lcm(T a, T b) {
        return a * b / gcd(a, b);
    }

    template <typename T>
    std::istream &operator>>(std::istream &is, std::vector<T> &array) {
        for (auto &i : array) {
            is >> i;
        }
        return is;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &array) {
        for (const auto &i : array) {
            os << i << " ";
        }
        return os;
    }

    template <typename T>
    std::istream &operator>>(std::istream &is, std::vector<std::vector<T> > &matrix) {
        for (auto &i : matrix)
            for (auto &j : i) is >> j;
        return is;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const std::vector<std::vector<T> > &matrix) {
        for (const auto &i : matrix) {
            for (const auto &j : i) os << j << " ";
            os << "\n";
        }
        return os;
    }

    template <typename T>
    std::istream &operator>>(std::istream &is, std::pair<T, T> &p){
        is >> p.first >> p.second;
        return is;
    }

}  // namespace tools
using namespace tools;


ld check(ld x, vector<int> &coords, vector<int> &velocity){
    ld minx = 1e10, maxx = -1;
    for (int i = 0; i < coords.size(); i++){
        ld curd = velocity[i] * x + coords[i];
        if (curd > maxx)
            maxx = curd;
        if (curd < minx)
            minx = curd;
    }
    return maxx - minx;
}

void solve() {
    int n;
    cin >> n;
    vector<int> coords(n), velocity(n);
    for (int i = 0; i < n; i++)
        cin >> coords[i] >> velocity[i];
    ld l = 0, r = 1e9;
    for (int i = 0; i < 1000; i++){
        ld a = (2 * l + r) / 3;
        ld b = (l + 2 * r) / 3;
        if (check(b, coords, velocity) - check(a, coords, velocity) > 1e-9){
            r = b;
        }
        else
            l = a;
    }
    cout << setprecision(7) << fixed << (r + l) / 2 << " " << check((r + l) / 2, coords, velocity);

}

int32_t main() {
    setlocale(LC_ALL, "Russian");
#ifndef __APPLE__
    $FASTSTREAM
#endif
    solve();
    return 0;
}