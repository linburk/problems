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
#define $FASTSTREAM   \
	std::cin.tie(0);  \
	std::cout.tie(0); \
	std::ios_base::sync_with_stdio(false);

namespace tools
{

template <typename T> T gcd(T a, T b)
{
	while (b > 0) {
		a %= b;
		std::swap(a, b);
	}
	return a;
}

template <typename T> T lcm(T a, T b)
{
	return a * b / gcd(a, b);
}

template <typename T>
std::istream &operator>>(std::istream &is, std::vector<T> &array)
{
	for (auto &i : array) {
		is >> i;
	}
	return is;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &array)
{
	for (const auto &i : array) {
		os << i << " ";
	}
	return os;
}

template <typename T>
std::istream &operator>>(std::istream &is, std::vector<std::vector<T> > &matrix)
{
	for (auto &i : matrix)
		for (auto &j : i)
			is >> j;
	return is;
}

template <typename T>
std::ostream &operator<<(std::ostream &os,
						 const std::vector<std::vector<T> > &matrix)
{
	for (const auto &i : matrix) {
		for (const auto &j : i)
			os << j << " ";
		os << "\n";
	}
	return os;
}

} // namespace tools
using namespace tools;
vector<pair<int, int> > moves{ { 0, 1 }, { 1, 0 }, { -1, 0 }, { 0, -1 } };
int bfs(int n, int m, vector<vector<bool> > &graph)
{
	vector<vector<int> > dist(n, vector<int>(m, 1e9));
	dist[0][0] = 0;
	queue<pair<int, int> > q;
	q.push({ 0, 0 });
	while (!q.empty()) {
		auto &[x, y] = q.front();
		q.pop();
		for (auto &[dx, dy] : moves) {
			if (x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < m) {
				if (dist[x + dx][y + dy] > dist[x][y] + 1 &&
					!graph[x + dx][y + dy]) {
					dist[x + dx][y + dy] = dist[x][y] + 1;
					q.push({ x + dx, y + dy });
				}
			}
		}
	}
	return (dist[n - 1][m - 1] == 1e9 ? -1 : dist[n - 1][m - 1]);
}
void solve()
{
	int n, m;
	cin >> n >> m;
	vector<vector<bool> > graph(n, vector<bool>(m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char c;
			cin >> c;
			if (c == '#')
				graph[i][j] = 1;
		}
	}
	cout << bfs(n, m, graph);
}

int32_t main()
{
	setlocale(LC_ALL, "Russian");
#ifndef __APPLE__
	$FASTSTREAM
#endif
	solve();
	return 0;
}
