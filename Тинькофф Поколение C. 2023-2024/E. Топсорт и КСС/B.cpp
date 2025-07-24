#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

#define endl '\n'
#define all(cont) cont.begin(), cont.end()
#define unique(cont) cont.erase(unique(all(cont)), cont.end())

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

template <typename T, typename V>
std::istream &operator>>(std::istream &is, std::pair<T, V> &p)
{
	is >> p.first >> p.second;
	return is;
}

} // namespace tools
using namespace tools;

struct _topsort {
	vector<int> topSort;
	vector<int> used;
	void dfs(vector<vector<int> > &gr, int v)
	{
		if (used[v] == -1) {
			topSort.push_back(-1);
			return;
		}
		if (used[v] == 1)
			return;
		used[v] = 1;
		for (int to : gr[v]) {
			dfs(gr, to);
		}
		topSort.push_back(v);
	}
	vector<int> operator()(vector<vector<int> > &graph)
	{
		topSort.resize(0);
		used.resize(graph.size(), 0);
		for (int i = 0; i < graph.size(); i++)
			dfs(graph, i);
		reverse(all(topSort));
		return topSort;
	}
};
vector<int> ans;
vector<int> times;
vector<vector<int> > graph;
ll cost = 0;
vector<bool> used;
void dfs(vector<vector<int> > &graph, int v)
{
	if (used[v])
		return;
	used[v] = 1;
	for (auto to : graph[v]) {
		dfs(graph, to);
	}
	ans.push_back(v + 1);
	cost += times[v];
}

void solve()
{
	_topsort _ts;
	int n;
	cin >> n;
	used.resize(n, 0);
	times.resize(n, 0);
	graph.resize(n);
	cin >> times;
	for (int i = 0; i < n; i++) {
		int k;
		cin >> k;
		for (int j = 0; j < k; j++) {
			int to;
			cin >> to;
			graph[i].push_back(to - 1);
		}
	}
	dfs(graph, 0);
	cout << cost << " " << ans.size() << endl << ans;
}

int32_t main()
{
	setlocale(LC_ALL, "Russian");
#ifdef __APPLE__
	std::freopen("/Users/dmitrii/Documents/Code/Code/input.txt", "r", stdin);
	std::freopen("/Users/dmitrii/Documents/Code/Code/output.txt", "w", stdout);
#endif
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(false);
	//    int t;
	//    cin >> t;
	//    for (int i = 0; i < t; i++)
	solve();
	return 0;
}
