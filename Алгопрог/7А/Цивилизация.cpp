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
vector<pair<int, int> > moves{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
void bfs(vector<vector<int> > &gr, int x1, int y1, int x2, int y2){
    vector<vector<int> > dist(gr.size(), vector<int>(gr[0].size(), 1e5));
    vector<vector<pair<int, int> > > past(gr.size(), vector<pair<int, int> >(gr[0].size(), {-1, -1}));
    vector<vector<int> > used(gr.size(), vector<int>(gr[0].size(), 0));
    queue<pair<int, int> > q[3];
    q[0].push({x1, y1});
    dist[x1][y1] = 0;
    int p = 0, k = 1;
    while (k >= 1){
        while (q[p % 3].empty())
            p++;
        auto &[x, y] = q[p % 3].front();
        q[p % 3].pop();
        k--;
        if (used[x][y])
            continue;
        used[x][y] = 1;
        for (auto [dx, dy] : moves){
            dx = x + dx; dy = y + dy;
            int cost = gr[dx][dy];
            if (cost == 0)
                continue;
            if (dist[x][y] + cost < dist[dx][dy]){
                dist[dx][dy] = dist[x][y] + cost;
                past[dx][dy] = {dx - x, dy - y};
                q[dist[dx][dy] % 3].push({dx, dy});
                k++;
            }
        }
    }
    if (past[x2][y2] == make_pair(-1, -1)){
        cout << -1;
        return;
    }
    string ans;
    cout << dist[x2][y2] << endl;
    pair<int, int> pos = {x2, y2};
    pair<int, int> move = past[x2][y2];
    while (pos != make_pair(x1, y1)){
        for (auto &[dx, dy] : moves){
            if (move == make_pair(dx, dy)){
                if (dy == 1){
                    ans.push_back('E');
                }
                if (dy == -1){
                    ans.push_back('W');
                }
                if (dx == 1){
                    ans.push_back('S');
                }
                if (dx == -1){
                    ans.push_back('N');
                }
                pos.first -= dx;
                pos.second -= dy;
                move = past[pos.first][pos.second];
                continue;
            }
        }
    }
    for (int i = ans.size() - 1; i >= 0; i--)
        cout << ans[i];
}


void solve() {
    int n, m, x1, y1, x2, y2;
    cin >> n >> m >> x1 >> y1 >> x2 >> y2;
    vector<vector<int> > gr(n + 2, vector<int>(m + 2, 0));
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            char c;
            cin >> c;
            if (c == '.')
                gr[i][j] = 1;
            if (c == 'W')
                gr[i][j] = 2;

        }
    }
    bfs(gr, x1, y1, x2, y2);
}

int32_t main() {
    setlocale(LC_ALL, "Russian");
#ifndef __APPLE__
    $FASTSTREAM
#endif
    solve();
    return 0;
}