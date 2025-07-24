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
const int maxgr = 1e5;
using namespace tools;
vector<int> bfs(int s, vector<vector<pair<int, int> > > &graph)
{
	vector<int> dist(graph.size(), 1e9);
	dist[s] = 0;
	deque<int> q;
	q.push_back(s);
	while (!q.empty()) {
		int v = q.front();
		q.pop_front();
		for (auto [j, d] : graph[v]) {
			if (dist[j] > dist[v] + d) {
				dist[j] = dist[v] + d;
				if (d == 1) {
					q.push_back(j);
				} else {
					q.push_front(j);
				}
			}
		}
	}
	return dist;
}
void solve()
{
	int n, m, s;
	cin >> n >> m >> s;
	s--;
	vector<vector<pair<int, int> > > graph(n);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--;
		b--;
		graph[a].pb(make_pair(b, c));
		graph[b].pb(make_pair(a, c));
	}
	vector<int> dist = bfs(s, graph);
	for (auto i : dist) {
		if (i == 1e9)
			cout << -1 << " ";
		else
			cout << i << " ";
	}
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
