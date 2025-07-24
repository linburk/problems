#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

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

struct meet {
	int min, max, change;
};
istream &operator>>(istream &is, meet &m)
{
	is >> m.min >> m.max >> m.change;
	return is;
}

void solve()
{
	int n, k;
	cin >> n >> k;
	vector<meet> meets(n);
	cin >> meets;
	vector<vector<int> > dp(1 << n, vector<int>(n, -1e9));
	for (int i = 0; i < n; i++) {
		if (meets[i].max >= k && k >= meets[i].min) {
			dp[1 << i][i] = k + meets[i].change;
		}
		dp[0][i] = k;
	}
	for (int mask = 1; mask < 1 << n; mask++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (dp[mask ^ (1 << i)][j] >= meets[i].min &&
					dp[mask ^ (1 << i)][j] <= meets[i].max)
					dp[mask][i] = dp[mask ^ (1 << i)][j] + meets[i].change;
			}
		}
	}
	int max_m = 0;
	int last = -1;
	for (int i = 1; i < 1 << n; i++) {
		for (int j = 0; j < n; j++) {
			if (dp[i][j] != -1e9 &&
				__builtin_popcount(i) > __builtin_popcount(max_m)) {
				max_m = i;
				last = j;
			}
		}
	}
	vector<int> res;
	while (max_m) {
		res.push_back(last + 1);
		//        cout << bitset<3>(max_m) << '\n'; cout.flush();
		for (int i = 0; i < n; i++) {
			if ((max_m & (1 << i)) &&
				dp[max_m ^ (1 << last)][i] + meets[last].change ==
					dp[max_m][last]) {
				max_m ^= (1 << last);
				last = i;
				break;
			}
		}
	}
	reverse(all(res));
	cout << res.size() << "\n" << res;
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
