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

void bfs(int s, vector<vector<int> > &graph, vector<int> &dist)
{
	queue<int> q;
	dist[s] = 0;
	q.push(s);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (auto i : graph[v]) {
			if (dist[i] + 1 > dist[v]) {
				dist[i] = dist[v] + 1;
				q.push(i);
			}
		}
	}
}

void solve()
{
	int n, s;
	cin >> n >> s;
	s--;
	vector<vector<int> > graph(n);
	vector<int> dist(n, 1e8);
	for (int i = 0; i < n - 1; ++i) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		graph[a].pb(b);
		graph[b].pb(a);
	}
	bfs(s, graph, dist);
	int max = s;
	vector<int> ans;
	for (int i = 0; i < n; i++) {
		if (dist[i] > dist[max])
			max = i;
	}
	for (int i = 0; i < n; i++) {
		if (dist[i] == dist[max])
			ans.push_back(i + 1);
	}
	for (auto i : ans)
		cout << i << " ";
}

int32_t main()
{
#ifndef __APPLE__
	$FASTSTREAM
#endif
	solve();
}
