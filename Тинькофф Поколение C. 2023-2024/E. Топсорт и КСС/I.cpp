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
		order = new vector<pair<int, int> >;
		used = new vector<vector<bool> >;
	}
	~_condensate()
	{
		delete order;
		delete used;
	}

	int operator()(vector<vector<int> > &graph)
	{
		componentCount = 0;
		setMoveChecker(graph);
		topSortGraph(graph);
		countComponents(graph);
		return componentCount;
	}

private:
	void setMoveChecker(vector<vector<int> > &graph)
	{
		checkCanMove = [&graph](int i, int j, int toI, int toJ) {
			return toI >= 0 && toI < graph.size() && toJ >= 0 &&
				   toJ < graph[0].size() && graph[i][j] <= graph[toI][toJ];
		};
	}

	void topSortGraph(vector<vector<int> > &graph)
	{
		used->assign(graph.size(), vector<bool>(graph[0].size(), 0));
		for (int i = 0; i < graph.size(); i++) {
			for (int j = 0; j < graph[0].size(); j++) {
				if (!used->at(i)[j])
					topSort(i, j);
			}
		}
	}

	void countComponents(vector<vector<int> > &graph)
	{
		used->assign(graph.size(), vector<bool>(graph[0].size(), 0));
		for (int k = order->size() - 1; k >= 0; k--) {
			auto [i, j] = order->at(k);
			if (!used->at(i)[j]) {
				getComponent(i, j);
				componentCount++;
			}
		}
	}

	function<bool(int, int, int, int)> checkCanMove;
	vector<pair<int, int> > moves = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
	vector<pair<int, int> > *order;
	vector<vector<bool> > *used;
	int componentCount;

	void topSort(int i, int j)
	{
		if (used->at(i)[j])
			return;
		used->at(i)[j] = 1;
		for (auto [di, dj] : moves) {
			if (checkCanMove(i, j, di + i, dj + j)) {
				topSort(di + i, dj + j);
			}
		}
		order->push_back({ i, j });
	}
	void getComponent(int i, int j)
	{
		if (used->at(i)[j])
			return;
		used->at(i)[j] = 1;
		for (auto [di, dj] : moves) {
			if (checkCanMove(i, j, di + i, dj + j)) {
				getComponent(di + i, dj + j);
			}
		}
	}
};

void solve()
{
	_condensate _cs;
	int n, m;
	cin >> n >> m;
	vector<vector<int> > graph(n, vector<int>(m));
	cin >> graph;
	cout << _cs(graph);
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
