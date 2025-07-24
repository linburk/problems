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

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int> > matrix(n, vector<int>(m));
    vector<vector<pair<int, int> > > count(n, vector<pair<int, int> >(m, {0, 0}));
    cin >> matrix;

    for (int j = 0; j < m; j++){
        int l = 0, r = 0;
        int cnted = 0;
        int cnt = 0;
        for (; r < k; r++){
            if (matrix[r][j] == 1){
                cnt++;
            }
        }
        while (l < n){
            if (matrix[l][j] == 1) {
                count[l][j].first = cnt;
                count[l][j].second = cnted;
                cnted++;
                cnt--;
            }
            if (r < n){
                if (matrix[r][j] == 1){
                    cnt++;
                }
                r++;
            }
            l++;
        }
    }

    int score = 0, actions = 0;

    for (int j = 0; j < m; j++){
        pair<int, int> maxrow = {-1, -1};
        for (int i = 0; i < n; i++){
            if (count[i][j].first > maxrow.first){
                maxrow = count[i][j];
            }
        }
        score += maxrow.first;
        actions += maxrow.second;
    }
    cout << score << " " << actions;
    int deb = 0;
}

int32_t main() {
    setlocale(LC_ALL, "Russian");
#ifndef __APPLE__
    $FASTSTREAM
#endif
//    int t;
//    cin >> t;
//    for (int i = 0; i < t; i++)
    solve();
    return 0;
}