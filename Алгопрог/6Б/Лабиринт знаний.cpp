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
    int from;
    int to;
    int weight;
};
void ford(vector<edge> &edges, vector<vector<int> > &gr, int n){
    vector<ll> dist(n, -1e10);
    dist[0] = 0;
    for (int i = 0; i < n - 1; i++) {
        for (auto [from, to, weight]: edges) {
            if (dist[from] != -1e10 && dist[to] < dist[from] + weight) {
                dist[to] = dist[from] + weight;
            }
        }
    }
    if (dist[n - 1] == -1e10) {
        cout << ":(";
        exit(0);
    }
    vector<int> cycle;
    for (auto [from, to, weight]: edges) {
        if (dist[from] != -1e10 && dist[to] < dist[from] + weight) {
            dist[to] = dist[from] + weight;
            cycle.push_back(to);
        }
    }
    vector<bool> used(n, 0);
    for (auto cur : cycle){
        queue<int> q;
        q.push(cur);
        while (!q.empty()){
            int v = q.front();
            q.pop();
            for (auto to : gr[v]){
                if (!used[to]) {
                    q.push(to);
                    used[to] = 1;
                }
            }
        }
    }
    if (used[n - 1]){
        cout << ":)";
        exit(0);
    }
    cout << dist[n - 1];
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<edge> edges;
    vector<vector<int> > gr(n);
    for (int i = 0; i < m; i++){
        edge E;
        cin >> E.from >> E.to >> E.weight;
        E.from--; E.to--;
        edges.push_back(E);
        gr[E.from].push_back(E.to);
    }
    ford(edges, gr, n);
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