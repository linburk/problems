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

void bfs(vector<vector<int> > &table) {
  vector<vector<int> > dist(table.size(), vector<int>(table[0].size(), 1e9));
  dist[1][1] = 0;
  queue<pair<int, int> > q;
  q.push({1, 1});
  while (!q.empty()) {
    auto &[x, y] = q.front();
    q.pop();

    int dx = 0;

    while (table[dx + x + 1][y] != 1) {
      dx++;
      if (table[x + dx][y] == 2) {
        cout << dist[x][y] + 1;
        return;
      }
    }
    if (dist[x + dx][y] > dist[x][y] + 1) {
      dist[x + dx][y] = dist[x][y] + 1;
      q.push({x + dx, y});
    }
    while (table[dx + x - 1][y] != 1) {
      dx--;
      if (table[x + dx][y] == 2) {
        cout << dist[x][y] + 1;
        return;
      }
    }
    if (dist[x + dx][y] > dist[x][y] + 1) {
      dist[x + dx][y] = dist[x][y] + 1;
      q.push({x + dx, y});
    }
    if (table[x + dx][y] == 2) {
      cout << dist[x + dx][y];
      return;
    }

    int dy = 0;

    while (table[x][y + dy + 1] != 1) {
      dy++;
      if (table[x][y + dy] == 2) {
        cout << dist[x][y] + 1;
        return;
      }
    }
    if (dist[x][y + dy] > dist[x][y] + 1) {
      dist[x][y + dy] = dist[x][y] + 1;
      q.push({x, y + dy});
    }

    while (table[x][y + dy - 1] != 1) {
      dy--;
      if (table[x][y + dy] == 2) {
        cout << dist[x][y] + 1;
        return;
      }
    }
    if (dist[x][y + dy] > dist[x][y] + 1) {
      dist[x][y + dy] = dist[x][y] + 1;
      q.push({x, y + dy});
    }
  }
}

void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<int> > table(n + 2, vector<int>(m + 2, 1));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> table[i][j];
    }
  }
  bfs(table);
}

int32_t main() {
  setlocale(LC_ALL, "Russian");
#ifndef __APPLE__
  $FASTSTREAM
#endif
  solve();
  return 0;
}