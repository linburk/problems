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

class disjointSetUnion {
public:
	disjointSetUnion(int n, int m)
	{
		ancestor.resize(n, vector<pair<int, int> >(m));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				ancestor[i][j] = { i, j };
		}
		efficient.resize(n, vector<int>(m, 0));
		rank.resize(n, vector<int>(m, 0));
	}
	vector<vector<pair<int, int> > > ancestor;
	vector<vector<int> > efficient;
	vector<vector<int> > rank;
	multiset<int> minMax;
	void unite(pair<int, int> a, pair<int, int> b)
	{
		a = leader(a);
		b = leader(b);
		if (a == b)
			return;
		if (rank[a.first][a.second] > rank[b.first][b.second])
			swap(a, b);
		int ia = a.first, ja = a.second, ib = b.first, jb = b.second;
		ancestor[ia][ja] = b;
		rank[ib][jb] = max(rank[ib][jb], rank[ia][ja] + 1);
		auto ita = minMax.find(efficient[ia][ja]);
		minMax.erase(ita);
		auto itb = minMax.find(efficient[ib][jb]);
		minMax.erase(itb);
		efficient[ib][jb] = max(efficient[ib][jb], efficient[ia][ja]);
		minMax.insert(efficient[ib][jb]);
	}

	pair<int, int> leader(pair<int, int> a)
	{
		return (a == ancestor[a.first][a.second] ?
					a :
					ancestor[a.first][a.second] =
						leader(ancestor[a.first][a.second]));
	}
};

struct query {
	int i, j, eff;
};

void solve()
{
	const pair<int, int> moves[]{ { 0, 1 }, { 1, 0 }, { -1, 0 }, { 0, -1 } };
	int n, m;
	cin >> n >> m;
	disjointSetUnion DSU(n, m);
	cin >> DSU.efficient;
	int q;
	cin >> q;
	stack<query> queries;
	for (int i = 0; i < q; i++) {
		int x, y;
		cin >> x >> y;
		queries.push({ x - 1, y - 1, DSU.efficient[x - 1][y - 1] });
		DSU.efficient[x - 1][y - 1] = 0;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (DSU.efficient[i][j])
				DSU.minMax.insert(DSU.efficient[i][j]);
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (auto move : moves) {
				int di = move.first, dj = move.second;
				if (i + di >= 0 && i + di < n && j + dj >= 0 && j + dj < m &&
					DSU.efficient[i][j] != 0 &&
					DSU.efficient[i + di][j + dj] != 0) {
					DSU.unite({ i, j }, { i + di, j + dj });
				}
			}
		}
	}
	stack<int> answers;
	answers.push(*DSU.minMax.begin());
	while (!queries.empty()) {
		int x = queries.top().i, y = queries.top().j, eff = queries.top().eff;
		DSU.efficient[x][y] = eff;
		DSU.minMax.insert(DSU.efficient[x][y]);
		queries.pop();
		for (auto move : moves) {
			int dx = move.first, dy = move.second;
			if (x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < m &&
				DSU.efficient[x][y] != 0 && DSU.efficient[x + dx][y + dy] != 0)
				DSU.unite({ x, y }, { x + dx, y + dy });
		}
		answers.push(*DSU.minMax.begin());
	}
	while (!answers.empty()) {
		cout << answers.top() << "\n";
		answers.pop();
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
