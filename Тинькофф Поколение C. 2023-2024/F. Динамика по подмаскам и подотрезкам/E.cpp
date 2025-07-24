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

vi result;
void cut_tree(int l, int r, vvi &canl)
{
	if (canl[l][r] == l)
		return;
	cut_tree(l, canl[l][r], canl);
	cut_tree(canl[l][r], r, canl);
	result.push_back(canl[l][r] + 1);
}
void resG(int l, int r, vvi &canl, vvi &prev)
{
	if (prev[l][r] == l) {
		cut_tree(l, r, canl);
		return;
	}
	resG(l, prev[l][r], canl, prev);
	resG(prev[l][r], r, canl, prev);
}

void solve()
{
	int n;
	cin >> n;
	vi a(n);
	cin >> a;
	vvi canl(n, vi(n, -1));
	vvi dp(n, vi(n, 1e9));
	vvi prev(n, vi(n, -1));
	for (int i = 0; i < n - 1; i++)
		canl[i][i + 1] = i;
	auto check = [&a](int l, int m, int r) -> bool {
		return (a[l] > a[m] && a[m] < a[r]) || (a[l] < a[m] && a[m] > a[r]);
	};
	for (int k = 0; k < n; k++) {
		for (int l = 0; l < n - k; l++) {
			int r = l + k;
			for (int m = l + 1; m < r; m++) {
				if (check(l, m, r) && canl[l][m] != -1 && canl[m][r] != -1) {
					canl[l][r] = m;
					break;
				}
			}
		}
	}
	for (int k = 0; k < n; k++) {
		for (int l = 0; l < n - k; l++) {
			int r = l + k;
			if (a[l] > a[r])
				continue;
			if (canl[l][r] != -1) {
				dp[l][r] = r - l - 1;
				prev[l][r] = l;
			}
			for (int m = l + 1; m < r; m++) {
				if (a[l] > a[m] || a[m] > a[r])
					continue;
				if (dp[l][r] > dp[l][m] + dp[m][r]) {
					dp[l][r] = dp[l][m] + dp[m][r];
					prev[l][r] = m;
				}
			}
		}
	}
	if (prev[0][n - 1] == -1) {
		cout << -1;
		return;
	}
	resG(0, n - 1, canl, prev);
	cout << result.size() << "\n" << result;
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
