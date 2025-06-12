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
#define pb(x) push_back(x)
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

void floyd(vector<vector<ll> > &gr){
    for (int k = 0; k < gr.size(); k++){
        for (int i = 0; i < gr.size(); i++){
            for (int j = 0; j < gr.size(); j++){
                if (gr[i][k] < 1e10 and gr[k][j] < 1e10)
                    gr[i][j] = min(gr[i][j], gr[i][k] + gr[k][j]);
            }
        }
    }
    for (int i = 0; i < gr.size(); i++){
        for (int j = 0; j < gr.size(); j++){
            for (int k = 0; k < gr.size(); k++){
                if (gr[i][k] < 1e10 and gr[k][j] < 1e10 and gr[k][k] < 0)
                    gr[i][j] = -1e10;
            }
        }
    }
    for (int i = 0; i < gr.size(); i++){
        for (int j = 0; j < gr.size(); j++){
            if (gr[i][j] == -1e10)
                cout << 2 << " ";
            else if (gr[i][j] == 1e10)
                cout << 0 << " ";
            else
                cout << 1 << " ";
        }
        cout << endl;
    }
}

void solve() {
    int n;
    cin >> n;
    vector<vector<ll> > gr(n, vector<ll>(n));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> gr[i][j];
            if (gr[i][j] == 0 and i != j)
                gr[i][j] = 1e10;
        }
    }
    floyd(gr);
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