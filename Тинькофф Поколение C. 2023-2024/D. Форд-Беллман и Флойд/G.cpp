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

void floyd(vector<vector<int> > &dist, vector<int> &race,
		   vector<vector<int> > &races)
{
	vector<vector<int> > next(dist.size(), vector<int>(dist.size(), -1));
	for (int i = 0; i < dist.size(); i++) {
		for (int j = 0; j < dist.size(); j++) {
			if (dist[i][j] != -1e9) {
				next[i][j] = j;
			}
		}
	}
	for (int k = 0; k < dist.size(); k++) {
		for (int i = 0; i < dist.size(); i++) {
			for (int j = 0; j < dist.size(); j++) {
				if (dist[i][k] != -1e9 && dist[k][j] != -1e9) {
					if (dist[i][j] < dist[i][k] + dist[k][j]) {
						dist[i][j] = dist[i][k] + dist[k][j];
						next[i][j] = next[i][k];
					}
				}
			}
		}
	}
	vector<int> cycle;
	for (int i = 0; i < dist.size(); i++) {
		if (dist[i][i] > 0)
			cycle.push_back(i);
	}
	vector<int> path;
	path.push_back(race[0]);
	for (int i = 1; i < race.size(); i++) {
		if (race[i - 1] != race[i]) {
			for (auto j : cycle) {
				if (dist[race[i - 1]][j] != -1e9 && dist[j][race[i]] != -1e9) {
					cout << 0;
					exit(0);
				}
			}
			int s = next[race[i - 1]][race[i]];
			while (s != race[i]) {
				path.push_back(s);
				s = next[s][race[i]];
			}
			path.push_back(s);
		}
	}

	vector<int> ans;
	for (int i = 1; i < path.size(); i++) {
		ans.push_back(races[path[i - 1]][path[i]]);
	}
	cout << ans.size() << endl << ans;
}

void solve()
{
	int n, m, k;
	cin >> n >> m >> k;
	vector<vector<int> > dist(n, vector<int>(n, -1e9));
	vector<vector<int> > races(n, vector<int>(n, -1));
	for (int i = 0; i < m; i++) {
		int a, b, w;
		cin >> a >> b >> w;
		a--;
		b--;
		if (w > dist[a][b]) {
			dist[a][b] = w;
			races[a][b] = i + 1;
		}
	}
	vector<int> race(k);
	for (int i = 0; i < k; i++) {
		cin >> race[i];
		race[i]--;
	}
	floyd(dist, race, races);
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
