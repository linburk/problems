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
typedef vector<vector<bool> > vvb;

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

map<int, pair<int, int> > hash_val;

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	cin >> a;
	int m;
	cin >> m;
	vector<int> b(m);
	cin >> b;
	for (int i = 0; i <= 100000; i++) {
		hash_val[i] = { rng(), rng() };
	}
	vector<vector<pair<int, int> > > hash1(n, vector<pair<int, int> >(n));
	vector<vector<pair<int, int> > > hash2(m, vector<pair<int, int> >(m));
	for (int l = 0; l < n; l++) {
		pair<int, int> cur_hash;
		for (int r = l; r < n; r++) {
			cur_hash.first += hash_val[a[r]].first;
			cur_hash.second += hash_val[a[r]].second;
			hash1[l][r] = cur_hash;
		}
	}
	for (int l = 0; l < m; l++) {
		pair<int, int> cur_hash;
		for (int r = l; r < m; r++) {
			cur_hash.first += hash_val[b[r]].first;
			cur_hash.second += hash_val[b[r]].second;
			hash2[l][r] = cur_hash;
		}
	}
	int maxK = 0;
	for (int k = 0; k < min(n, m); k++) {
		for (int l1 = 0; l1 < n - k; l1++) {
			int r1 = l1 + k;
			for (int l2 = 0; l2 < m - k; l2++) {
				int r2 = l2 + k;
				if (hash1[l1][r1] == hash2[l2][r2]) {
					maxK = k + 1;
				}
			}
		}
	}
	cout << maxK;
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
