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
void dijkstra(vector<vector<pair<int, int> > > &gr, int s, int e)
{
	vector<int> past(gr.size(), -1);
	vector<int> dist(gr.size(), 1e9);
	dist[s] = 0;
	set<pair<int, int> > q;
	q.insert({ dist[s], s });
	while (!q.empty()) {
		int v = q.begin()->second;
		q.erase(q.begin());
		for (auto &[to, l] : gr[v]) {
			if (dist[to] > dist[v] + l) {
				q.erase({ dist[to], to });
				past[to] = v;
				dist[to] = dist[v] + l;
				q.insert({ dist[to], to });
			}
		}
	}
	if (dist[e] != 1e9) {
		int x, y, d;
		d = dist[e];
		y = past[e];
		int v = past[e];
		vector<int> vertexes;
		while (v != -1) {
			vertexes.pb(v);
			v = past[v];
		}
		x = vertexes[vertexes.size() - 2];
		cout << x + 1 << " " << y + 1 << " " << d;
	} else {
		cout << -1;
	}
}

void solve()
{
	int n, m;
	cin >> n >> m;
	vector<int> laims, xendas;
	for (int i = 0; i < n; i++) {
		int v;
		cin >> v;
		if (v == 1) {
			laims.pb(i);
		}
		if (v == 2) {
			xendas.pb(i);
		}
	}
	vector<vector<pair<int, int> > > gr(n + 2);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--;
		b--;
		gr[a].push_back({ b, c });
		gr[b].push_back({ a, c });
	}
	for (auto i : laims) {
		gr[n].push_back({ i, 0 });
	}
	for (auto i : xendas) {
		gr[i].push_back({ n + 1, 0 });
	}
	dijkstra(gr, n, n + 1);
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
