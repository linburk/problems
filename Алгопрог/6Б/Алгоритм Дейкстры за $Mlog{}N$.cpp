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


void dijkstra(vector<vector<pair<int, int> > > &gr, int s){
    vector<ll> dist(gr.size(), 2009000999);
    dist[s] = 0;
    set<pair<ll, int> > q;
    q.insert({0, s});
    while (!q.empty()){
        auto [d, from] = *q.begin();
        q.erase(q.begin());
        for (auto &[to, w] : gr[from]){
            if (dist[to] > dist[from] + w){
                q.erase({dist[to], to});
                dist[to] = dist[from] + w;
                q.insert({dist[to], to});
            }
        }
    }
    cout << dist << endl;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int> > > gr(n);
    for (int i = 0; i < m; i++){
        int a, b, c;
        cin >> a >> b >> c;
        gr[a].push_back({b, c});
        gr[b].push_back({a, c});
    }
    int s;
    cin >> s;
    dijkstra(gr, s);
}

int32_t main() {
    setlocale(LC_ALL, "Russian");
#ifndef __APPLE__
    $FASTSTREAM
#endif
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
        solve();
    return 0;
}