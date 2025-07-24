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

vector<int> mem;
vector<bool> used;
vector<vector<int> > graph;
void bfs()
{
	queue<int> q;
	used[0] = 1;
	q.push(0);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (auto i : graph[v]) {
			if (!used[i]) {
				q.push(i);
				used[i] = 1;
				mem[i] = v;
			}
		}
	}
}

void solve()
{
	int n;
	cin >> n;
	mem.resize(n + 1);
	graph.resize(n + 1);
	mem[0] = -1;
	used.resize(n + 1, 0);

	for (int i = 1; i < n; i++) {
		int b;
		cin >> b;
		b--;
		graph[b].push_back(i);
	}
	bfs();
	vector<int> ans;
	int e = n - 1;
	while (mem[e] != -1) {
		ans.pb(e + 1);
		e = mem[e];
	}
	cout << 1 << " ";
	for (int i = ans.size() - 1; i >= 0; i--) {
		cout << ans[i] << " ";
	}
}

int32_t main()
{
#ifndef __APPLE__
	$FASTSTREAM
#endif
	solve();
}
