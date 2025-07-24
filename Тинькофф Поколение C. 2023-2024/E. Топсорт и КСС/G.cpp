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

// ######## // REDUCT GRAPH // ######## //
struct _reduction {
	_reduction()
	{
		transClosure = new vector<vector<bool> >;
		reductGraph = new vector<vector<int> >;
		adjMatrix = new vector<vector<bool> >;
		used = new vector<bool>;
	}
	~_reduction()
	{
		delete transClosure;
		delete reductGraph;
		delete adjMatrix;
		delete used;
	}

	vector<vector<int> > operator()(vector<set<int> > &graph)
	{
		buildAdj(graph);
		buildClosure(graph);
		reduction();
		buildNewGr();
		return *reductGraph;
	}

private:
	vector<bool> *used;
	vector<vector<bool> > *adjMatrix;
	vector<vector<bool> > *transClosure;
	vector<vector<int> > *reductGraph;

	void buildAdj(vector<set<int> > &graph)
	{
		adjMatrix->resize(graph.size(), vector<bool>(graph.size(), 0));
		for (int v = 0; v < graph.size(); v++) {
			for (auto to : graph[v]) {
				adjMatrix->at(v)[to] = 1;
			}
		}
	}
	void buildClosure(vector<set<int> > &graph)
	{
		transClosure->resize(graph.size(), vector<bool>(graph.size(), 0));
		for (int i = 0; i < graph.size(); i++) {
			used->assign(graph.size(), 0);
			dfs(i, i, graph);
		}
	}
	void dfs(int st, int v, vector<set<int> > &graph)
	{
		if (used->at(v))
			return;
		used->at(v) = 1;
		for (auto to : graph[v]) {
			dfs(st, to, graph);
			transClosure->at(st)[to] = 1;
		}
	}
	void reduction()
	{
		for (int a = 0; a < transClosure->size(); a++) {
			for (int b = 0; b < transClosure->size(); b++) {
				for (int c = 0; c < transClosure->size(); c++) {
					if (transClosure->at(a)[b] && transClosure->at(b)[c] &&
						adjMatrix->at(a)[c]) {
						adjMatrix->at(a)[c] = 0;
					}
				}
			}
		}
	}
	void buildNewGr()
	{
		reductGraph->resize(adjMatrix->size());
		for (int v = 0; v < reductGraph->size(); v++) {
			for (int to = 0; to < reductGraph->size(); to++) {
				if (adjMatrix->at(v)[to]) {
					reductGraph->at(v).push_back(to);
				}
			}
		}
	}
};

// ######## // CONDENSATE // ######## //
struct _condensateGraph {
	std::pair<std::vector<set<int> >, std::vector<std::vector<int> > >
	operator()(std::vector<std::vector<int> > &graph,
			   std::vector<std::vector<int> > &turnedGraph)
	{
		doTopSort(graph);
		buildComponents(turnedGraph);
		buildCondGr(graph);
		return { *condensatedGraph, *componentMembers };
	}

	_condensateGraph()
	{
		componentMembers = new std::vector<std::vector<int> >;
		condensatedGraph = new std::vector<std::set<int> >;
		order = new std::vector<int>;
		member = new std::vector<int>;
		used = new std::vector<bool>;
		component = new std::vector<int>;
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
	std::vector<std::vector<int> > *componentMembers;
	std::vector<std::set<int> > *condensatedGraph;
	std::vector<int> *order;
	std::vector<int> *member;
	std::vector<int> *component;
	std::vector<bool> *used;
	int componentCount;

	void doTopSort(vector<vector<int> > &graph)
	{
		used->resize(graph.size(), 0);
		for (int v = 0; v < graph.size(); v++) {
			if (!(*used)[v])
				topSort(v, &graph);
		}
	}
	void buildComponents(vector<vector<int> > &turnedGraph)
	{
		componentCount = 0;
		used->assign(turnedGraph.size(), 0);
		member->resize(turnedGraph.size(), 0);
		for (int i = turnedGraph.size() - 1; i >= 0; i--) {
			if (!used->at(order->at(i))) {
				getComponent(order->at(i), &turnedGraph);
				for (auto v : *component) {
					member->at(v) = componentCount;
				}
				componentCount++;
				component->clear();
			}
		}

		componentMembers->resize(componentCount);
		for (int v = 0; v < turnedGraph.size(); v++) {
			componentMembers->at(member->at(v)).push_back(v);
		}
	}
	void buildCondGr(vector<vector<int> > &graph)
	{
		condensatedGraph->resize(componentCount);
		for (int v = 0; v < graph.size(); v++) {
			for (auto to : graph[v]) {
				if (member->at(v) != member->at(to)) {
					condensatedGraph->at(member->at(v)).insert(member->at(to));
				}
			}
		}
	}
	void topSort(int v, std::vector<std::vector<int> > *graph)
	{
		if (used->at(v))
			return;
		used->at(v) = 1;
		for (auto to : graph->at(v)) {
			topSort(to, graph);
		}
		order->push_back(v);
	}
	void getComponent(int v, std::vector<std::vector<int> > *turnedGraph)
	{
		if (used->at(v))
			return;
		used->at(v) = 1;
		component->push_back(v);
		for (auto to : turnedGraph->at(v)) {
			getComponent(to, turnedGraph);
		}
	}
};

// ######## // GET NEW GRAPH // ######## //
void getNewGraph(vector<vector<int> > &graph, vector<vector<int> > &turnedGraph)
{
	_condensateGraph _cs;
	_reduction _rd;

	vector<pair<int, int> > newEdges;

	auto [condGr, compMb] = _cs(graph, turnedGraph);
	vector<vector<int> > newGr = _rd(condGr);

	for (int i = 0; i < compMb.size(); i++) {
		for (int v = 0; v < compMb[i].size() && compMb[i].size() > 1; v++) {
			newEdges.push_back(
				{ compMb[i][v], compMb[i][(v + 1) % compMb[i].size()] });
		}
	}

	for (int v = 0; v < newGr.size(); v++) {
		for (int to : newGr[v]) {
			newEdges.push_back({ compMb[v][0], compMb[to][0] });
		}
	}

	cout << newEdges.size() << endl;
	for (int i = 0; i < newEdges.size(); i++) {
		cout << newEdges[i].first + 1 << " " << newEdges[i].second + 1 << endl;
	}
}

// ######## // SOLUTION // ######## //
void solve()
{
	vector<vector<int> > graph, turnedGraph;
	int n, m;
	cin >> n >> m;
	graph.resize(n);
	turnedGraph.resize(n);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		graph[a - 1].push_back(b - 1);
		turnedGraph[b - 1].push_back(a - 1);
	}
	getNewGraph(graph, turnedGraph);
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
