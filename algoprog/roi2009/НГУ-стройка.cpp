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

struct event{
    int z;
    int type;
    int index;
    ll square;
};
bool comp(event a, event b){
    if (a.z == b.z){
        return a.type < b.type;
    }
    return a.z < b.z;
}
void solve() {
    int n, w, l;
    cin >> n >> w >> l;
    ll sq = w * l;
    vector<event> events;
    for (int i = 0; i < n; i++){
        int x1, x2, y1, y2, z1, z2;
        cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
        ll square = abs(x2 - x1) * abs(y2 - y1);
        events.push_back({z1, 1, i, square});
        events.push_back({z2, -1, i, -square});
    }
    sort(all(events), comp);
    vector<bool> ans(n, 0);
    vector<bool> cur(n, 0);
    ll cursq = 0;
    int curcnt = 0;
    int mincnt = 1e9;
    for (auto i : events){
        curcnt += i.type;
        cursq += i.square;
        cur[i.index] = (cur[i.index] + 1) % 2;
        if (cursq == sq){
            if (mincnt > curcnt){
                mincnt = curcnt;
                ans = cur;
            }
        }
    }
    if (mincnt == 1e9) {
        cout << "NO";
        return;
    }
    cout << "YES" << endl << mincnt << endl;
    for (int i = 0; i < n; i++){
        if (ans[i])
            cout << i + 1 << " ";
    }
}

int32_t main() {
    setlocale(LC_ALL, "Russian");
#ifndef __APPLE__
    $FASTSTREAM
#endif
    solve();
    return 0;
}