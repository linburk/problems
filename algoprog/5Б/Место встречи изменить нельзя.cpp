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
    std::istream &operator>>(std::istream &is,
                             std::vector<std::vector<T> > &matrix) {
        for (auto &i : matrix)
            for (auto &j : i) is >> j;
        return is;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os,
                             const std::vector<std::vector<T> > &matrix) {
        for (const auto &i : matrix) {
            for (const auto &j : i) os << j << " ";
            os << "\n";
        }
        return os;
    }

    template <typename T>
    std::istream &operator>>(std::istream &is, std::pair<T, T> &p) {
        is >> p.first >> p.second;
        return is;
    }

}  // namespace tools
using namespace tools;
vector<ll> coords, velocity;
ld check(ld time){
    ld maxd1 = -1, maxd2 = -1;
    ld c1 = coords[0] + velocity[0] * time, c2 = coords[0] - velocity[0] * time;
    for (int i = 0; i < coords.size(); i++){
        ld x1 = coords[i] + velocity[i] * time, x2 = coords[i] - velocity[i] * time;
        maxd1 = max(maxd1, min(abs(c1 - x1), abs(c1 - x2)));
        maxd2 = max(maxd2, min(abs(c2 - x1), abs(c2 - x2)));
    }
    return min(maxd1, maxd2);
}

void solve() {
    ll n;
    cin >> n;
    coords.resize(n);
    velocity.resize(n);
    cin >> coords >> velocity;
    ld l = -1, r = 1e9;
    while (r - l > 1e-9){
        ld a = (l * 2 + r) / 3;
        ld b = (l + 2 * r) / 3;
        if (check(a) < check(b))
            r = b;
        else
            l = a;
    }
    cout << setprecision(7) << fixed << r;
}

int32_t main() {
    setlocale(LC_ALL, "Russian");
#ifndef __APPLE__
    $FASTSTREAM
#endif
    solve();
    return 0;
}