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

struct _condensate {
	_condensate()
	{
		used = new vector<bool>;
		order = new vector<int>;
		member = new vector<int>;
		component = new vector<int>;
		condensatedGraph = new vector<set<int> >;
	}
	~_condensate()
	{
		delete order;
		delete member;
		delete component;
		delete condensatedGraph;
	}
	vector<set<int> > operator()(vector<vector<int> > &graph,
								 vector<vector<int> > &turnedGraph)
	{
		topSortGraph(graph);
		getMember(turnedGraph);
		getCondensatedGraph(graph);
		return *condensatedGraph;
	}

private:
	vector<bool> *used;
	vector<int> *order, *member, *component;
	vector<set<int> > *condensatedGraph;
	int componentCount;

	void topSortGraph(vector<vector<int> > &graph)
	{
		used->resize(graph.size(), 0);
		for (int v = 0; v < graph.size(); v++) {
			if (!used->at(v))
				topSort(v, graph);
		}
	}
	void topSort(int v, vector<vector<int> > &graph)
	{
		if (used->at(v))
			return;
		used->at(v) = 1;
		for (auto to : graph[v]) {
			topSort(to, graph);
		}
		order->push_back(v);
	}
	void getCondensatedGraph(vector<vector<int> > &graph)
	{
		condensatedGraph->resize(componentCount);
		for (int v = 0; v < member->size(); v++) {
			for (auto to : graph[v]) {
				if (member->at(v) != member->at(to))
					condensatedGraph->at(member->at(v)).insert(member->at(to));
			}
		}
	}

	void getMember(vector<vector<int> > &turnedGraph)
	{
		componentCount = 0;
		used->assign(order->size(), 0);
		member->resize(order->size());
		for (int v = order->size() - 1; v >= 0; v--) {
			if (!used->at(order->at(v))) {
				getComponent(order->at(v), turnedGraph);
				for (auto i : *component)
					member->at(i) = componentCount;
				componentCount++;
				component->clear();
			}
		}
	}
	void getComponent(int v, vector<vector<int> > &turnedGraph)
	{
		if (used->at(v))
			return;
		used->at(v) = 1;
		component->push_back(v);
		for (auto to : turnedGraph[v]) {
			getComponent(to, turnedGraph);
		}
	}
};
int vertexEraser(vector<set<int> > &graph)
{
	int cnt = 0;
	for (int i = 0; i < graph.size(); i++) {
		if (graph[i].size() > 0)
			cnt++;
	}
	return graph.size() - cnt;
}
void solve()
{
	_condensate _cs;
	vector<vector<int> > gr, tGr;
	int n, m;
	cin >> n >> m;
	gr.resize(n);
	tGr.resize(n);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		gr[a - 1].push_back(b - 1);
		tGr[b - 1].push_back(a - 1);
	}
	vector<set<int> > modGr = _cs(gr, tGr);
	cout << vertexEraser(modGr);
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
