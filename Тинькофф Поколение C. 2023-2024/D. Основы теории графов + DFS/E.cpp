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

vector<vector<int> > graph;
vector<bool> used;
set<int> bfs(int s)
{
	set<int> ret;
	queue<int> q;
	q.push(s);
	ret.insert(s);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (auto i : graph[v]) {
			if (!used[i]) {
				used[i] = 1;
				q.push(i);
				ret.insert(i);
			}
		}
	}
	return ret;
}

void solve()
{
	int n, m;
	cin >> n >> m;
	graph.resize(n);
	used.resize(n, 0);
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		graph[a].pb(b);
		graph[b].pb(a);
	}
	int cnt = 0;
	vector<set<int> > ans;
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			ans.pb(bfs(i));
			cnt++;
		}
	}
	cout << cnt << endl;
	for (auto i : ans) {
		cout << size(i) << endl;
		for (auto j : i)
			cout << j + 1 << " ";
		cout << endl;
	}
}

int32_t main()
{
#ifndef __APPLE__
	$FASTSTREAM
#endif
	solve();
}
