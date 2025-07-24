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

struct edge{
    int to;
    ll whenfrom;
    ll whento;
};

void ford(vector<vector<edge> > &gr, int s, int f, int n){
    vector<ll> time(n, 1e10);
    vector<bool> inqueue(n, 0);
    queue<int> q;
    q.push(s);
    time[s] = 0;
    while (!q.empty()){
        int v = q.front();
        q.pop();
        inqueue[v] = 0;
        for (auto [to, whenfrom, whento] : gr[v]){
            if (whenfrom >= time[v] and time[to] > whento){
                time[to] = whento;
                if (!inqueue[to]) {
                    q.push(to);
                    inqueue[to] = 1;
                }
            }
        }
    }
    cout << time[f];
}


void solve() {
    int n, s, f, k;
    cin >> n >> s >> f >> k;
    vector<vector<edge> > gr(n);
    for (int i = 0; i < k; i++){
        int a;
        edge E;
        cin >> a >> E.whenfrom >> E.to >> E.whento;
        a--; E.to--;
        gr[a].push_back(E);
    }
    ford(gr, s - 1, f - 1, n);
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