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

template <typename T, bool (*comparator)(const T &, const T &)>
class sparseTable {
	std::vector<std::vector<T> > ST;
	void build(const std::vector<T> &arr)
	{
		ST.resize(32 - __builtin_clz(arr.size() + 1),
				  std::vector<T>(arr.size()));
		ST[0] = arr;
		for (int i = 0; i + 1 < 32 - __builtin_clz(arr.size() + 1); i++) {
			for (int j = 0; j < arr.size() - (1 << i); j++) {
				ST[i + 1][j] = (comparator(ST[i][j], ST[i][j + (1 << i)]) ?
									ST[i][j] :
									ST[i][j + (1 << i)]);
			}
		}
	}

public:
	sparseTable()
	{
	}

	sparseTable(const std::vector<T> &arr)
	{
		build(arr);
	}

	const T get(int l, int r)
	{
		int d = 31 - __builtin_clz(r - l);
		return (comparator(ST[d][l], ST[d][r - (1 << d)]) ?
					ST[d][l] :
					ST[d][r - (1 << d)]);
	}
	const int size()
	{
		return ST[0].size();
	}

	void operator()(std::vector<T> &arr)
	{
		build(arr);
	}
};

class staticLCA {
	inline static bool comp(const std::pair<int, int> &a,
							const std::pair<int, int> &b)
	{
		return (a.first < b.first ? 1 : 0);
	}
	// vector<int> tin, tout;
	std::vector<std::pair<int, int> > euler_tour;
	std::vector<int> first_enter, last_enter;
	// int time = 0;

	sparseTable<std::pair<int, int>, comp> RMQ;

	std::vector<bool> used;
	void dfs(std::vector<std::vector<int> > &gr, int v, int depth)
	{
		// tin[v] = time++;
		used[v] = 1;
		first_enter[v] = euler_tour.size();
		euler_tour.push_back(std::make_pair(depth, v));
		for (auto to : gr[v]) {
			if (!used[to]) {
				dfs(gr, to, depth + 1);
				euler_tour.push_back(std::make_pair(depth, v));
			}
		}
		last_enter[v] = euler_tour.size();
		// tout[v] = time++;
	}

	void build(std::vector<std::vector<int> > &graph, int root)
	{
		// tin.resize(graph.size());
		// tout.resize(graph.size());
		used.resize(graph.size(), 0);
		first_enter.resize(graph.size());
		last_enter.resize(graph.size());
		dfs(graph, root, 0);
		RMQ(euler_tour);
	}

public:
	staticLCA(std::vector<std::vector<int> > &graph, int root)
	{
		build(graph, root);
	}

	int get(int u, int v)
	{
		return RMQ
			.get(std::min(first_enter[u], first_enter[v]),
				 std::max(last_enter[u], last_enter[v]))
			.second;
	}

	// bool is_ancestor(int _anc, int v){
	//     return tin[_anc] < tin[v] && tin[v] < tout[v] && tout[v] < tout[_anc];
	// }
};
vector<ll> cost;
vector<ll> dist;
vector<vector<int> > gr;
vector<bool> used;
void dfs(int v, int past)
{
	if (used[v])
		return;
	used[v] = 1;
	dist[v] = dist[past] + cost[v];
	for (auto to : gr[v]) {
		dfs(to, v);
	}
}
void solve()
{
	ll n;
	cin >> n;
	cost.resize(n);
	used.resize(n, 0);
	dist.resize(n, 0);
	gr.resize(n);
	cin >> cost;
	for (int i = 0; i < n - 1; i++) {
		ll a, b;
		cin >> a >> b;
		gr[a - 1].push_back(b - 1);
		gr[b - 1].push_back(a - 1);
	}
	dfs(0, 0);
	staticLCA LCA(gr, 0);
	ll m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		ll a, b;
		cin >> a >> b;
		ll lca = LCA.get(a - 1, b - 1);
		cout << dist[a - 1] + dist[b - 1] - 2 * dist[lca] + cost[lca] << endl;
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
