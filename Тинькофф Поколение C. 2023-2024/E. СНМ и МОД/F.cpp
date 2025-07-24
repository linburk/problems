#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

#define endl '\n'
#define all(cont) cont.begin(), cont.end()
#define funique(cont) cont.erase(unique(all(cont)), cont.end())

namespace tools
{
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
class _DSU {
public:
	_DSU(int n)
	{
		rank.resize(n, 1);
		ancestor.resize(n);
		iota(all(ancestor), 0);
	}
	void unite(int a, int b)
	{
		a = leader(a);
		b = leader(b);
		if (rank[a] > rank[b])
			swap(a, b);
		ancestor[a] = b;
		if (a != b)
			rank[b] += rank[a];
	}
	int leader(int v)
	{
		return (ancestor[v] == v ? v : ancestor[v] = leader(ancestor[v]));
	}
	vector<int> rank, ancestor;
};
void solve()
{
	int n, m, x;
	cin >> n >> m >> x;
	_DSU dsu1(n), dsu2(n);
	for (int i = 0; i < m; i++) {
		int a, b, w;
		cin >> a >> b >> w;
		if (w < x)
			dsu1.unite(a - 1, b - 1);
		if (w <= x)
			dsu2.unite(a - 1, b - 1);
	}
	ull cnt1 = 0, cnt2 = 0;
	for (int i = 0; i < n; i++) {
		cnt1 += dsu1.rank[dsu1.leader(i)] - 1;
		cnt2 += dsu2.rank[dsu2.leader(i)] - 1;
	}
	cnt1 /= 2;
	cnt2 /= 2;
	cout << cnt2 - cnt1;
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
