#include <bits/stdc++.h>

#include <climits>
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
// mt19937_64 rng(chrono::steady_clock().now().time_since_epoch().count());
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

vvi gr;
vi dp;
vi sz;
void dfs(int v)
{
	if (gr[v].size() == 0)
		return void(dp[v] = 1);
	for (auto to : gr[v]) {
		dfs(to);
		sz[v] += sz[to];
	}
	for (auto to : gr[v]) {
		dp[v] += dp[to];
	}
	dp[v] += sz[v];
}
void solve()
{
	int n;
	cin >> n;
	gr.resize(n);
	sz.resize(n, 1);
	for (int i = 1; i < n; i++) {
		int a;
		cin >> a;
		gr[a - 1].push_back(i);
	}
	dp.resize(n, 0);
	dfs(0);
	for (int i : dp)
		cout << i << " ";
}

int32_t main()
{
	setlocale(LC_ALL, "Russian");
#ifdef __APPLE__
	// std::freopen("/Users/dmitrii/Documents/Code/Code/input.txt", "r", stdin);
	// std::freopen("/Users/dmitrii/Documents/Code/Code/output.txt", "w", stdout);
#endif
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(false);
	//    int t; cin >> t; for (; t; t--)
	solve();
	return 0;
}
