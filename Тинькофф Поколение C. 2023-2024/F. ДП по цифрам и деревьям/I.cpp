
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

const int MOD = 1e9 + 7;
vl dig;
ll n, a, k;
ll a_to_k_size;
vl a_to_k;
ll prepow[62];
vl dp;
vl dp_pref;
vl ed_pref;

void precalc()
{
	prepow[0] = 1;
	prepow[1] = k;
	for (int i = 2; i < 62; i++) {
		prepow[i] = (prepow[i - 1] * k) % MOD;
	}
	a_to_k_size = 0;
	ll a_t = a;
	while (a_t) {
		a_to_k_size++;
		a_t /= k;
	}
	a_to_k.resize(a_to_k_size);
	a_t = a;
	for (ll i = a_to_k_size - 1; i >= 0; i--) {
		a_to_k[i] = a_t % k;
		a_t /= k;
	}
	ed_pref.resize(n + 1);
	ed_pref[0] = 0;
	for (int i = 1; i <= n; i++) {
		ed_pref[i] = ed_pref[i - 1] + (dig[i - 1] == -1);
	}
}
ll get_ed(ll l, ll r)
{
	ll res = ed_pref[r] - ed_pref[l];
	if (l > r)
		res = 0;
	return prepow[res];
}

void calc_dp()
{
	dp.resize(n + 1ll);
	dp[0] = 1ll;
	for (ll i = 1ll; i <= n; i++) {
		for (ll j = i; j > max(i - a_to_k_size, 0ll); j--) {
			ll len = i - j + 1ll;
			ll null_c = j - 1;
			if (len < a_to_k_size) {
				if (dig[null_c] != -1ll) {
					if (dig[null_c] == 0ll)
						continue;
					dp[i] += dp[null_c] * get_ed(null_c, i) % MOD;
					dp[i] %= MOD;
				} else {
					dp[i] += dp[null_c] *
							 (get_ed(null_c + 1, i) % MOD * (k - 1ll)) % MOD;
					dp[i] %= MOD;
				}
			}
			if (len >= a_to_k_size) {
				ll t_cnt = 0;
				for (ll cur = j; cur < j + a_to_k_size; cur++) {
					ll ql = null_c + cur - j + 1;
					ll qr = i;
					ll a_symb = cur - j;
					ll dig_symb = cur - 1;
					if (dig[dig_symb] == 0 && cur == j)
						break;
					if (dig[dig_symb] == -1) {
						if (cur == i)
							t_cnt++;
						ll z = (cur == j ? a_to_k[a_symb] - 1 : a_to_k[a_symb]);
						t_cnt += z * get_ed(ql, qr) % MOD;
						t_cnt %= MOD;

					} else {
						if (dig[dig_symb] == a_to_k[a_symb]) {
							if (cur == i)
								t_cnt++;
							t_cnt %= MOD;
						} else if (dig[dig_symb] < a_to_k[a_symb]) {
							t_cnt += get_ed(ql, qr);
							t_cnt %= MOD;
							break;

						} else if (dig[dig_symb] > a_to_k[a_symb]) {
							break;
						}
					}
				}
				dp[i] += (dp[i - a_to_k_size] * t_cnt) % MOD;
				dp[i] %= MOD;
			}
		}
	}
}

void solve()
{
	cin >> n >> a >> k;
	dig.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> dig[i];
	}
	precalc();
	calc_dp();
	cout << dp[n];
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
//
