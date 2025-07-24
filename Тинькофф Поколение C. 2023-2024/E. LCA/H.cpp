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
public:
	std::vector<std::vector<int> > binaryUpp;
	std::vector<int> depths;

	void add_edge(int ind, int past)
	{
		depths[ind] = depths[past] + 1;
		binaryUpp[ind][0] = past;
		for (int i = 1; i < 30; i++) {
			binaryUpp[ind][i] = binaryUpp[binaryUpp[ind][i - 1]][i - 1];
		}
	}

	void build(int n, int root)
	{
		depths.resize(n);
		binaryUpp.resize(n, std::vector<int>(30));
		depths[root] = 0;
		for (int i = 0; i < 30; i++) {
			binaryUpp[root][i] = root;
		}
	}

	staticLCA()
	{
	}

	staticLCA(int n, int root)
	{
		build(n, root);
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
	int max1 = 1, max2 = 1, dist = 0;
	staticLCA LCA(n + 2, 1);
	for (int i = 2; i < n + 2; i++) {
		int p;
		cin >> p;
		LCA.add_edge(i, p);
		int lca1 = LCA.get_lca(i, max1), lca2 = LCA.get_lca(i, max2);
		int dist1 = LCA.depths[i] + LCA.depths[max1] - 2 * LCA.depths[lca1],
			dist2 = LCA.depths[i] + LCA.depths[max2] - 2 * LCA.depths[lca2];
		if (dist1 > dist2 && dist1 > dist) {
			dist = dist1;
			max2 = i;
		} else if (dist2 > dist1 && dist2 > dist) {
			dist = dist2;
			max1 = i;
		} else if (dist1 > dist) {
			dist = dist1;
			max2 = i;
		}
		cout << dist << endl;
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
