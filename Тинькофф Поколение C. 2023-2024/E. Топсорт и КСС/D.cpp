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

struct _condensateGraph {
	pair<vector<int>, int> operator()(vector<vector<int> > &graph,
									  vector<vector<int> > &turnedGraph)
	{
		componentCount = 0;
		(*member).resize(graph.size(), 0);
		(*used).resize(graph.size(), 0);
		for (int v = 0; v < graph.size(); v++) {
			if (!(*used)[v])
				topSort(v, &graph);
		}
		(*used).assign(graph.size(), 0);
		for (int i = graph.size() - 1; i >= 0; i--) {
			if (!(*used)[(*order)[i]]) {
				getComponent((*order)[i], &turnedGraph);
				(*componentMembers).push_back(vector<int>());
				for (auto v : (*component)) {
					(*member)[v] = componentCount;
					(*componentMembers)[componentCount].push_back(v);
				}
				componentCount++;
				(*component).clear();
			}
		}
		(*condensatedGraph).resize(componentCount);
		for (int v = 0; v < graph.size(); v++) {
			for (auto to : graph[v]) {
				(*condensatedGraph)[(*member)[v]].push_back((*member)[to]);
			}
		}
		(*used).assign(componentCount, 0);
		(*order).clear();
		for (int comp = 0; comp < componentCount; comp++) {
			topSort(comp, condensatedGraph);
		}
		for (int i = 0; i < componentCount; i++) {
			for (auto v :
				 (*componentMembers)[(*order)[componentCount - i - 1]]) {
				(*member)[v] = i + 1;
			}
		}
		return { (*member), componentCount };
	}

	_condensateGraph()
	{
		componentMembers = new vector<vector<int> >;
		condensatedGraph = new vector<vector<int> >;
		order = new vector<int>;
		member = new vector<int>;
		used = new vector<bool>;
		component = new vector<int>;
	}

	~_condensateGraph()
	{
		delete order;
		delete member;
		delete component;
		delete used;
		delete condensatedGraph;
		delete componentMembers;
	}

private:
	vector<vector<int> > *componentMembers;
	vector<vector<int> > *condensatedGraph;
	vector<int> *order;
	vector<int> *member;
	vector<int> *component;
	vector<bool> *used;
	int componentCount;

	void topSort(int v, vector<vector<int> > *graph)
	{
		if ((*used)[v])
			return;
		(*used)[v] = 1;
		for (auto to : (*graph)[v]) {
			topSort(to, graph);
		}
		(*order).push_back(v);
	}

	void getComponent(int v, vector<vector<int> > *turnedGraph)
	{
		if ((*used)[v])
			return;
		(*used)[v] = 1;
		(*component).push_back(v);
		for (auto to : (*turnedGraph)[v]) {
			getComponent(to, turnedGraph);
		}
	}
};

void solve()
{
	_condensateGraph funcCondensate;
	vector<vector<int> > graph, turnedGraph;
	int n, m;
	cin >> n >> m;
	graph.resize(n);
	turnedGraph.resize(n);
	for (int i = 0; i < m; i++) {
		int from, to;
		cin >> from >> to;
		graph[from - 1].push_back(to - 1);
		turnedGraph[to - 1].push_back(from - 1);
	}
	auto [member, cnt] = funcCondensate(graph, turnedGraph);
	cout << cnt << endl << member;
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
// 5
// 1 3 5 5 2
// 1 2 3 4 2
// 1 2 2 2 1
//
