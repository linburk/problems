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

bool comp(pair<int, int> a, pair<int, int> b){
    if (a.first == b.first){
        if (a.second == -1){
            if (b.second == -2)
                return 1;
            return a.second < b.second;
        }
        if (b.second == -2){
            if (b.second == -1)
                return 0;
            return a.second > b.second;
        }
    }
    return a.first < b.first;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int> > segm;
    for (int i = 0; i < n; i++){
        int s, e;
        cin >> s >> e;
        segm.push_back({min(s, e), -1});
        segm.push_back({max(s, e), -2});
    }
    for (int i = 0; i < m; i++){
        int p;
        cin >> p;
        segm.push_back({p, i});
    }
    sort(all(segm), comp);
    vector<int> ans(m, 0);
    int cnt = 0;
    for (auto p : segm){
        if (p.second == -1)
            cnt++;
        else if (p.second == -2)
            cnt--;
        else
            ans[p.second] = cnt;
    }
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