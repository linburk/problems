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

template <typename T>
std::istream &operator>>(std::istream &is, std::pair<T, T> &p)
{
	is >> p.first >> p.second;
	return is;
}

} // namespace tools
using namespace tools;

struct edge {
	int from;
	int to;
	int weight;
};

void ford(vector<edge> &edges, int n, int k, int s, int f)
{
	vector<vector<int> > dist(n, vector<int>(k + 1, 1e9));
	dist[s][0] = 0;
	for (int i = 0; i < k; i++) {
		for (auto &[from, to, weight] : edges) {
			if (dist[to][i + 1] > dist[from][i] + weight) {
				dist[to][i + 1] = dist[from][i] + weight;
			}
		}
	}
	int ans = 1e9;
	for (int i = 0; i <= k; i++) {
		if (dist[f][i] < ans)
			ans = dist[f][i];
	}
	cout << (ans == 1e9 ? -1 : ans);
}

void solve()
{
	int n, m, k, s, f;
	cin >> n >> m >> k >> s >> f;
	s--;
	f--;
	vector<edge> edges;
	for (int i = 0; i < m; i++) {
		edge E;
		cin >> E.from >> E.to >> E.weight;
		E.from--;
		E.to--;
		edges.push_back(E);
	}
	ford(edges, n, k, s, f);
}

int32_t main()
{
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
