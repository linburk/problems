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
		os << i;
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

void solve()
{
	ll n, m;
	cin >> n >> m;
	vvl gr(n, vl(n, 0));
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		gr[a - 1][b - 1] = 1;
	}
	vl dp(1 << n, 0);
	vvl f(1 << n, vl(n + 1, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (gr[i][j]) {
				f[1 << i | 1 << j][i]++;
			}
		}
	}
	for (int mask = 1; mask < 1 << n; mask++) {
		for (int start = 0; start < n; start++) {
			if ((1 << start) & mask) {
				for (int v = 0; v < n; v++) {
					if ((1 << v) & mask && gr[start][v]) {
						f[mask][start] += f[mask ^ (1 << start)][v];
					}
				}
			}
		}
		for (int i = 0; i < n; i++) {
			f[mask][n] += f[mask][i];
		}
	}
	dp[0] = 1;
	for (int mask = 1; mask < 1 << n; mask++) {
		for (int submask = mask; submask >= (1 << (31 - __builtin_clz(mask)));
			 submask = (submask - 1) & mask) {
			dp[mask] += dp[mask ^ submask] * f[submask][n];
		}
	}
	cout << dp[(1 << n) - 1];
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
