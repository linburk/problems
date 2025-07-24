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

struct _topSort {
	vector<bool> used;
	void operator()(vector<int> &topSort,
					vector<vector<pair<int, int> > > &graph)
	{
		used.assign(graph.size(), 0);
		for (int v = 0; v < graph.size(); v++) {
			if (!used[v])
				dfs(v, graph, topSort);
		}
		reverse(all(topSort));
	}

	void dfs(int v, vector<vector<pair<int, int> > > &graph,
			 vector<int> &topSort)
	{
		if (used[v])
			return;
		used[v] = 1;
		for (auto to : graph[v]) {
			dfs(to.first, graph, topSort);
		}
		topSort.push_back(v);
	}
};

void spfa(vector<vector<pair<int, int> > > &graph, int s, int f)
{
	vector<int> topSort;
	_topSort ts;
	ts(topSort, graph);
	vector<ll> dist(graph.size(), 1e10);
	dist[s] = 0;
	for (int i = 0; i < graph.size(); i++) {
		for (auto [to, w] : graph[topSort[i]]) {
			if (dist[topSort[i]] != 1e10)
				dist[to] = min(dist[to], dist[topSort[i]] + w);
		}
	}
	cout << (dist[f] == 1e10 ? "Unreachable" : to_string(dist[f]));
}

void solve()
{
	vector<vector<pair<int, int> > > graph;
	int n, m, s, t;
	cin >> n >> m >> s >> t;
	graph.resize(n);
	for (int i = 0; i < m; i++) {
		int b, e, w;
		cin >> b >> e >> w;
		graph[b - 1].push_back({ e - 1, w });
	}
	spfa(graph, s - 1, t - 1);
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
