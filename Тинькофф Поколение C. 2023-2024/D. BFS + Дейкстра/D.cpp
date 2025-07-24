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
void dijkstra(vector<pair<int, int> > &points, int s, int e)
{
	vector<int> dist(points.size(), 1e9);
	vector<bool> marks(points.size(), 0);
	dist[s] = 0;
	for (int i = 0; i < points.size(); i++) {
		int v = -1;
		for (int j = 0; j < points.size(); j++) {
			if (!marks[j] && (v == -1 || dist[j] < dist[v]))
				v = j;
		}
		if (v == -1)
			break;
		marks[v] = 1;
		for (int j = 0; j < points.size(); j++) {
			int len = pow(points[j].first - points[v].first, 2) +
					  pow(points[j].second - points[v].second, 2);
			if (dist[j] > dist[v] + len)
				dist[j] = dist[v] + len;
		}
	}
	cout << dist[e];
}
void solve()
{
	int n;
	cin >> n;
	vector<pair<int, int> > points(n);
	for (int i = 0; i < n; i++) {
		cin >> points[i].first >> points[i].second;
	}
	int s, t;
	cin >> s >> t;
	s--;
	t--;
	dijkstra(points, s, t);
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
