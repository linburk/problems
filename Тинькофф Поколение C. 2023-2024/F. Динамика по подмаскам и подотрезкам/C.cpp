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
	os << "\n";
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
	int n;
	cin >> n;
	vector<vector<int> > gr(n, vector<int>(n));
	cin >> gr;
	vector<vector<int> > dp(1 << n, vector<int>(n, 1e9));
	dp[1][0] = 0;
	for (int mask = 1; mask < (1 << n); mask++) {
		for (int to = 0; to < n; to++) {
			if (mask & (1 << to)) {
				for (int from = 0; from < n; from++) {
					if ((mask & (1 << from)) && gr[from][to]) {
						if ((dp[mask][to] >
							 dp[mask ^ (1 << to)][from] + gr[from][to]) &&
							gr[from][to]) {
							dp[mask][to] =
								dp[mask ^ (1 << to)][from] + gr[from][to];
						}
					}
				}
			}
		}
	}
	int to = -1, minPath = 1e9;
	for (int i = 0; i < n; i++)
		if (dp[(1 << n) - 1][i] < minPath) {
			minPath = dp[(1 << n) - 1][i];
			to = i;
		}
	if (minPath == 1e9) {
		cout << -1;
		return;
	}
	vector<int> ans{ to + 1 };
	cout << minPath << "\n";
	int mask = (1 << n) - 1;
	while (mask != 1) {
		for (int from = 0; from < n; from++) {
			if ((mask & (1 << from)) &&
				dp[mask ^ (1 << to)][from] + gr[from][to] == dp[mask][to] &&
				gr[from][to]) {
				ans.push_back(from + 1);
				mask ^= (1 << to);
				to = from;
				break;
			}
		}
	}
	reverse(all(ans));
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
	//    int t;
	//    cin >> t;
	//    for (int i = 0; i < t; i++)
	solve();
	return 0;
}
