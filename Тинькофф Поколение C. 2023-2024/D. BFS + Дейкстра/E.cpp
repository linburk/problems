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

void dijkstra(vector<vector<pair<int, int> > > &graph, int start, int finish)
{
	vector<ll> distance(graph.size(), 1e12), past(graph.size());
	set<pair<int, int> > q;
	distance[start] = 0;
	q.insert({ distance[start], start });
	past[start] = -1;
	while (!q.empty()) {
		int vertex = q.begin()->second;
		q.erase(q.begin());
		for (auto &[j, c] : graph[vertex]) {
			if (distance[vertex] + c < distance[j]) {
				q.erase({ distance[j], j });
				distance[j] = distance[vertex] + c;
				past[j] = vertex;
				q.insert({ distance[j], j });
			}
		}
	}

	if (distance[finish] >= 1e12) {
		cout << -1;
		return;
	} else {
		vector<int> result;
		int vertex = finish;
		while (vertex != -1) {
			result.push_back(vertex + 1);
			vertex = past[vertex];
		}
		cout << distance[finish] << " " << result.size() << endl;
		for (int i = result.size() - 1; i >= 0; i--)
			cout << result[i] << " ";
		return;
	}
}
void solve()
{
	int n, m, start, finish;
	cin >> n >> m >> start >> finish;
	vector<vector<pair<int, int> > > graph(n);
	for (int i = 0; i < m; i++) {
		int a, b, x;
		cin >> a >> b >> x;
		a--;
		b--;
		graph[a].pb(make_pair(b, x));
		graph[b].pb(make_pair(a, x));
	}
	start--;
	finish--;
	dijkstra(graph, start, finish);
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
