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
vector<int> ans;
vector<bool> used;
void dfs(int v, vector<set<int> > &gr)
{
	if (used[v])
		return;
	used[v] = 1;
	for (int to : gr[v])
		dfs(to, gr);
	ans.push_back(v + 1);
}

void solve()
{
	int n;
	cin >> n;
	used.resize(n, 0);
	vector<vector<int> > *buses = new vector<vector<int> >(n, vector<int>(4));
	cin >> *buses;

	set<int> stations;
	for (int i = 0; i < n; i++) {
		stations.insert((*buses)[i][0]);
		stations.insert((*buses)[i][1]);
	}

	map<int, set<pair<ull, int> > > st;
	for (int i = 0; i < n; i++) {
		ll a = (*buses)[i][0], b = (*buses)[i][1], c = (*buses)[i][2],
		   d = (*buses)[i][3];
		auto beg = stations.find(a);
		auto end = stations.find(b);
		end++;
		for (; beg != end; beg++)
			st[*beg].insert({ 1ll * (*beg - a) * d + c, i });
	}
	delete buses;
	vector<set<int> > graph(n);
	for (auto s : stations) {
		for (auto it = st[s].begin(); it != st[s].end(); it++) {
			auto it2 = it;
			it2++;
			if (it2 == st[s].end())
				break;
			auto [time1, i1] = *it;
			auto [time2, i2] = *it2;
			graph[i1].insert(i2);
		}
	}

	for (int i = 0; i < n; i++) {
		if (!used[i])
			dfs(i, graph);
	}
	reverse(all(ans));
	cout << ans;
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
