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
vector<pair<int, int> > moves{ { 2, 1 }, { 2, -1 }, { -2, 1 }, { -2, -1 },
							   { 1, 2 }, { 1, -2 }, { -1, 2 }, { -1, -2 } };
void bfs(int n, pair<int, int> f, pair<int, int> s)
{
	vector<vector<pair<int, int> > > h1(10000), h2(10000);
	vector<vector<int> > d1(n, vector<int>(n, 1e5)), d2(n, vector<int>(n, 1e5));
	h1[0].pb(f);
	h2[0].pb(s);
	d1[f.first][f.second] = 0;
	d2[s.first][s.second] = 0;
	for (int i = 0; i < 10000; i++) {
		for (int j = 0; j < h1[i].size(); j++) {
			auto &[x, y] = h1[i][j];
			for (auto &[dx, dy] : moves) {
				if (x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < n) {
					if (d1[x + dx][y + dy] > i + 1) {
						d1[x + dx][y + dy] = i + 1;
						h1[i + 1].pb(make_pair(x + dx, y + dy));
					}
				}
			}
		}
	}
	for (int i = 0; i < 10000; i++) {
		for (int j = 0; j < h2[i].size(); j++) {
			auto &[x, y] = h2[i][j];
			if (d1[x][y] == d2[x][y]) {
				cout << i;
				return;
			}
			for (auto &[dx, dy] : moves) {
				if (x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < n) {
					if (d2[x + dx][y + dy] > i + 1) {
						d2[x + dx][y + dy] = i + 1;
						h2[i + 1].pb(make_pair(x + dx, y + dy));
					}
				}
			}
		}
	}
	cout << -1;
}
void solve()
{
	int n;
	pair<int, int> f, s;
	cin >> n >> f >> s;
	f.first--;
	f.second--;
	s.first--;
	s.second--;
	bfs(n, f, s);
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
