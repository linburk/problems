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

int dijkstra(vector<vector<pair<int, pair<int, int> > > > &gr, int startdist, int start, int finish){
    vector<int> dist(gr.size(), 1e9);
    dist[start] = startdist;
    set<pair<int, int> > q;
    q.insert({dist[start], start});
    while (!q.empty()){
        int v = q.begin()->second;
        q.erase(q.begin());
        if (v == finish)
            break;
        for (auto [to, timing] : gr[v]){
            auto [c, time] = timing;
            int timewait = (c - dist[v] % c) % c + time;
            if (dist[to] > dist[v] + timewait){
                q.erase({dist[to], to});
                dist[to] = dist[v] + timewait;
                q.insert({dist[to], to});
            }
        }
    }
    return dist[finish];
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<pair<int, pair<int, int> > > > gr(n);
    for (int i = 0; i < k; i++){
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        a--; b--;
        gr[a].push_back({b, {c, d}});
    }
    int m;
    cin >> m;
    vector<int> control(m);
    cin >> control;
    int begin = 0;
    for (int i = 0; i < m - 1; i++){
        begin = dijkstra(gr, begin, control[i] - 1, control[i + 1] - 1);
        if (begin == 1e9){
            cout << -1;
            exit(0);
        }
    }
    cout << begin;
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