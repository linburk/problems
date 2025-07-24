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
	ll n;
	cin >> n;
	vvl a(n, vl(n));
	cin >> a;
	vl dp(1 << n, -1e18);
	vl f(1 << n, 0);
	for (int mask = 1; mask < 1 << n; mask++) {
		for (int i = 0; i < n; i++) {
			if (mask & (1 << i)) {
				for (int j = 0; j < n; j++) {
					if (mask & (1 << j)) {
						f[mask] += a[i][j];
					}
				}
			}
		}
	}
	for (int mask = 1; mask < 1 << n; mask++) {
		f[mask] /= 2;
		dp[mask] = f[mask];
	}

	for (int mask = 1; mask < 1 << n; mask++) {
		for (int submask = mask; submask; submask = (submask - 1) & mask) {
			dp[mask] = max(dp[mask], dp[submask] + f[submask ^ mask]);
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
