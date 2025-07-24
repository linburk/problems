#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef vector<bool> vb;
typedef vector<vb> vvb;

#define all(cont) cont.begin(), cont.end()
#define funique(cont) cont.erase(unique(all(cont)), cont.end())

namespace tools
{
mt19937_64 rng(chrono::steady_clock().now().time_since_epoch().count());
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
	//        os << "\n";
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

vl vert;
vb used;
vvl dp, gr;
void dfs(ll v, ll p)
{
	if (used[v])
		return;
	used[v] = 1;
	if (gr[v].size() == 0) {
		dp[v][0] = 0;
		dp[v][1] = vert[v];
		return;
	}
	for (auto to : gr[v]) {
		if (to != p) {
			dfs(to, v);
			dp[v][0] += max(dp[to][0], dp[to][1]);
		}
	}
	dp[v][1] = vert[v];
	for (auto to : gr[v]) {
		if (to != p) {
			dp[v][1] += dp[to][0];
		}
	}
}
void solve()
{
	int n;
	cin >> n;
	vert.resize(n);
	used.resize(n, 0);
	cin >> vert;
	gr.resize(n);
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		gr[a - 1].push_back(b - 1);
		gr[b - 1].push_back(a - 1);
	}
	dp.resize(n, vl(2, 0));
	dfs(0, -1);
	cout << max(dp[0][1], dp[0][0]);
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
	//    int t; cin >> t; for (; t; t--)
	solve();
	return 0;
}
