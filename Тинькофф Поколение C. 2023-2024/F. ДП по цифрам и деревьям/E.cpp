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

vector<vector<pair<ll, ll> > > gr;
vl dp;
vl sz;
void dfs1(ll v, ll p)
{
	for (auto [to, w] : gr[v]) {
		if (to != p) {
			dfs1(to, v);
			sz[v] += sz[to];
			dp[v] += dp[to] + w * sz[to];
		}
	}
}
void dfs2(ll v, ll p)
{
	for (auto pa : gr[v]) {
		ll to = pa.first, w = pa.second;
		if (to != p) {
			dp[to] += dp[v] - dp[to] - w * sz[to] + w * (sz[v] - sz[to]);
			sz[to] = sz[v];
			dfs2(to, v);
		}
	}
}

void solve()
{
	int n;
	cin >> n;
	gr.resize(n);
	dp.resize(n, 0);
	sz.resize(n, 1);
	for (int i = 0; i < n - 1; i++) {
		int a, b, w;
		cin >> a >> b >> w;
		gr[a - 1].push_back(make_pair(b - 1, w));
		gr[b - 1].push_back(make_pair(a - 1, w));
	}
	dfs1(0, -1);
	dfs2(0, -1);
	for (auto i : dp)
		cout << i << " ";
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
