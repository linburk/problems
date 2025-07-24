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
typedef vector<vvi> vvvi;
typedef vector<vvl> vvvl;

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

const int MOD = 1e9 + 9;
bool is_prime[1000];
void solve()
{
	for (int i = 0; i < 1000; i++)
		is_prime[i] = 1;
	is_prime[0] = is_prime[1] = 0;
	for (int i = 2; i < 35; i++) {
		if (is_prime[i]) {
			for (int j = i * i; j < 1000; j += i) {
				is_prime[j] = 0;
			}
		}
	}
	int n;
	cin >> n;
	vvvi dp(n + 1, vvi(10, vi(10, 0)));
	for (int i = 100; i < 1000; i++) {
		if (is_prime[i]) {
			dp[3][i / 100][i / 10 % 10]++;
		}
	}
	//    dp[2][0][1] = 1;
	for (int i = 4; i <= n; i++) {
		for (int m = 0; m < 10; m++) {
			for (int j = 0; j < 10; j++) {
				for (int k = 0; k < 10; k++) {
					if (is_prime[m * 100 + j * 10 + k]) {
						dp[i][m][j] = (dp[i][m][j] + dp[i - 1][j][k]) % MOD;
					}
				}
			}
		}
	}
	int ans = 0;
	for (int i = (n == 3 ? 0 : 1); i < 10; i++) {
		for (int j = (n == 3 ? 0 : 1); j < 10; j++) {
			ans = (ans + dp[n][i][j]) % MOD;
		}
	}
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
	//    int t; cin >> t; for (; t; t--)
	solve();
	return 0;
}
