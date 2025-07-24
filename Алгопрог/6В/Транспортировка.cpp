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

bool dijkstra(vector<vector<pair<int, pair<int, int> > > > &gr, int need){
    vector<pair<int, int> > dist(gr.size(), {0, 1e9});
    vector<bool> marks(gr.size(), 0);
    dist[0] = {1e9, 0};
    for (int i = 0; i < gr.size(); i++){
        int v = -1;
        for (int j = 0; j < gr.size(); j++){
            if (!marks[j] and (v == -1 or dist[j].second < dist[v].second)){
                v = j;
            }
        }
        if (v == -1)
            break;
        marks[v] = 1;
        for (auto &[to, w] : gr[v]){
            ll cr = min(w.first, dist[v].first), time = dist[v].second + w.second;
            if (cr >= need){
                if ((time < dist[to].second or dist[to].first < need) and time <= 1440) {
                    dist[to].first = cr;
                    dist[to].second = time;
                }
            }
        }
    }
    return dist[gr.size() - 1].first >= need;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, pair<int, int> > > > gr(n);
    for (int i = 0; i < m; i++){
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        a--; b--;
        d -= 3*1e6;
        d /= 100;
        if (d > 0){
            gr[a].push_back({b, {d, c}});
            gr[b].push_back({a, {d, c}});
        }
    }
    ll l = 0, r = 10000001;
    while (r - l > 1){
        int mid = (r + l) / 2;
        if (dijkstra(gr, mid))
            l = mid;
        else
            r = mid;
    }
    cout << l;
}

int32_t main() {
    setlocale(LC_ALL, "Russian");
#ifndef __APPLE__
    $FASTSTREAM
#endif
    solve();
    return 0;
}