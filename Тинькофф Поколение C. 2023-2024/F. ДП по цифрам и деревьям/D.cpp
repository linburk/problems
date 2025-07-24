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

const int MOD = 1E9 + 7;
vvl dp(110, vl(10, 0));
void precalc()
{
	for (int i = 0; i < 10; i++)
		dp[1][i] = 1;
	for (int i = 2; i < 110; i++) {
		for (int j = 1; j < 10; j++) {
			for (int k = j; k < 10; k++) {
				dp[i][j] = (dp[i][j] + dp[i - 1][k]) % MOD;
			}
		}
		for (int j = 0; j < 10; j++) {
			dp[i][0] = (dp[i][0] + dp[i - 1][j]) % MOD;
		}
	}
}
ll count(string &num)
{
	ll res = 0;
	ll n = num.size() - 1;
	int min_digit = num[0] - '0';
	for (int i = 0; i < n; i++) {
		if (num[i + 1] - '0' < min_digit)
			break;
		for (int j = min_digit; j < num[i + 1] - '0'; j++) {
			res = (res + dp[n - i][j]) % MOD;
		}
		min_digit = max(min_digit, num[i + 1] - '0');
	}
	return res;
}
void solve()
{
	precalc();
	string l, r;
	cin >> l >> r;
	l = '0' + l;
	r = '0' + r;
	ll lcnt = count(l), rcnt = count(r);
	if (is_sorted(all(r)))
		rcnt++;
	cout << (rcnt - lcnt + MOD) % MOD;
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
