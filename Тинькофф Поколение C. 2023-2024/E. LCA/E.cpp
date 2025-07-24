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

class staticLCA {
	std::vector<std::vector<int> > binaryUpp;
	std::vector<std::vector<int> > funcMin;
	std::vector<int> depths;

	void dfs(std::vector<std::vector<pair<int, int> > > &graph, int vertex,
			 int past_vertex, int weight)
	{
		depths[vertex] = depths[past_vertex] + 1;
		binaryUpp[vertex][0] = past_vertex;
		funcMin[vertex][0] = weight;
		for (int i = 1; i < 30; i++) {
			binaryUpp[vertex][i] = binaryUpp[binaryUpp[vertex][i - 1]][i - 1];
			funcMin[vertex][i] = min(funcMin[vertex][i - 1],
									 funcMin[binaryUpp[vertex][i - 1]][i - 1]);
		}
		for (auto to : graph[vertex]) {
			dfs(graph, to.first, vertex, to.second);
		}
	}

	void build(std::vector<std::vector<pair<int, int> > > &graph, int root)
	{
		depths.resize(graph.size());
		binaryUpp.resize(graph.size(), std::vector<int>(30));
		funcMin.resize(graph.size(), std::vector<int>(30));
		depths[root] = -1;
		dfs(graph, root, root, 1e9);
	}

public:
	staticLCA()
	{
	}

	staticLCA(std::vector<std::vector<pair<int, int> > > &graph, int root)
	{
		build(graph, root);
	}

	int get_lca(int a, int b)
	{
		if (depths[a] < depths[b])
			swap(a, b);
		for (int i = 29; i >= 0; i--) {
			if (depths[binaryUpp[a][i]] >= depths[b]) {
				a = binaryUpp[a][i];
			}
		}

		if (a == b)
			return b;

		for (int i = 29; i >= 0; i--) {
			if (binaryUpp[b][i] != binaryUpp[a][i]) {
				b = binaryUpp[b][i];
				a = binaryUpp[a][i];
			}
		}
		return binaryUpp[a][0];
	}

	int get_min(int a, int b)
	{
		if (depths[a] < depths[b])
			swap(a, b);
		int ans = 1e9;
		for (int i = 29; i >= 0; i--) {
			if (depths[binaryUpp[a][i]] >= depths[b]) {
				ans = min(ans, funcMin[a][i]);
				a = binaryUpp[a][i];
			}
		}

		if (a == b)
			return ans;

		for (int i = 29; i >= 0; i--) {
			if (binaryUpp[b][i] != binaryUpp[a][i]) {
				ans = min({ ans, funcMin[a][i], funcMin[b][i] });
				b = binaryUpp[b][i];
				a = binaryUpp[a][i];
			}
		}

		return min({ ans, funcMin[a][0], funcMin[b][0] });
	}

	ll upp(int a, int level)
	{
		for (int i = 29; i >= 0; i--) {
			if (level >= (1 << i)) {
				a = binaryUpp[a][i];
				level -= (1 << i);
			}
		}
		return a;
	}
};

void solve()
{
	int n;
	cin >> n;
	vector<vector<pair<int, int> > > graph(n);
	for (int i = 1; i < n; i++) {
		int x, y;
		cin >> x >> y;
		graph[x - 1].push_back({ i, y });
	}
	staticLCA LCA(graph, 0);
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		cout << LCA.get_min(a - 1, b - 1) << endl;
	}
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
