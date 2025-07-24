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
	std::vector<std::vector<int> > binary_uppers;
	std::vector<int> depths;

	void dfs(std::vector<std::vector<int> > &graph, int vertex, int past_vertex)
	{
		depths[vertex] = depths[past_vertex] + 1;
		binary_uppers[vertex][0] = past_vertex;
		for (int i = 1; i < 30; i++) {
			binary_uppers[vertex][i] =
				binary_uppers[binary_uppers[vertex][i - 1]][i - 1];
		}
		for (auto to : graph[vertex]) {
			dfs(graph, to, vertex);
		}
	}

	void build(std::vector<std::vector<int> > &graph, int root)
	{
		depths.resize(graph.size());
		binary_uppers.resize(graph.size(), std::vector<int>(30));
		depths[root] = -1;
		dfs(graph, root, root);
	}

public:
	staticLCA()
	{
	}

	staticLCA(std::vector<std::vector<int> > &graph, int root)
	{
		build(graph, root);
	}

	int get_lca(int a, int b)
	{
		if (depths[a] < depths[b])
			swap(a, b);
		for (int i = 29; i >= 0; i--) {
			if (depths[binary_uppers[a][i]] >= depths[b]) {
				a = binary_uppers[a][i];
			}
		}

		if (a == b)
			return b;

		for (int i = 29; i >= 0; i--) {
			if (binary_uppers[b][i] != binary_uppers[a][i]) {
				b = binary_uppers[b][i];
				a = binary_uppers[a][i];
			}
		}
		return binary_uppers[a][0];
	}

	ll upp(int a, int level)
	{
		for (int i = 29; i >= 0; i--) {
			if (level >= (1 << i)) {
				a = binary_uppers[a][i];
				level -= (1 << i);
			}
		}
		return a;
	}
};

void solve()
{
	ll n, m;
	cin >> n >> m;
	vector<vector<int> > graph(n);
	for (int i = 1; i < n; i++) {
		int v;
		cin >> v;
		graph[v].push_back(i);
	}
	ll x, y, z;
	vector<ll> a(2 * m + 1);
	cin >> a[1] >> a[2] >> x >> y >> z;
	staticLCA LCA(graph, 0);
	for (int i = 3; i <= 2 * m; i++) {
		a[i] = (x * a[i - 2] + y * a[i - 1] + z) % n;
	}
	ll a1 = a[1], a2 = a[2];
	ll cnt = 0;
	for (ll i = 2; i <= m + 1; i++) {
		ll ans = LCA.upp(a1, a2);
		cnt += ans;
		a1 = (a[2 * i - 1] + ans) % n;
		a2 = a[2 * i];
	}
	cout << cnt;
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
