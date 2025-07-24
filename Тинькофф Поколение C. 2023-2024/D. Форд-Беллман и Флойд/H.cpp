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

void floyd(vector<vector<ld> > &dist, int s, int e)
{
	for (int k = 0; k < dist.size(); k++) {
		for (int i = 0; i < dist.size(); i++) {
			for (int j = 0; j < dist.size(); j++) {
				if (dist[i][k] != -1e9 && dist[k][j] != -1e9) {
					if (dist[i][j] < dist[i][k] * dist[k][j]) {
						dist[i][j] = dist[i][k] * dist[k][j];
					}
				}
			}
		}
	}
	cout << setprecision(7) << fixed << 1 - dist[s][e];
}

void solve()
{
	int n, m;
	cin >> n >> m;
	int s, e;
	cin >> s >> e;
	s--;
	e--;
	vector<vector<ld> > dist(n, vector<ld>(n, -1e9));
	for (int i = 0; i < m; i++) {
		int a, b;
		ld c;
		cin >> a >> b >> c;
		a--;
		b--;
		dist[a][b] = 1 - c / 100;
		dist[b][a] = 1 - c / 100;
	}
	floyd(dist, s, e);
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
