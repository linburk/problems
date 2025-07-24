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

void solve()
{
	int n, m, q;
	cin >> n >> m >> q;
	vector<int> current(n);
	cin >> current;
	vector<vector<int> > gr(n);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		gr[a - 1].push_back(b - 1);
		gr[b - 1].push_back(a - 1);
	}
	vector<int> heavies;
	vector<bool> is_heavy(n);
	vector<vector<int> > heavy_gr(n);
	int sqrt_m = sqrt(m) + 1;
	for (int i = 0; i < n; i++) {
		if (gr[i].size() >= sqrt_m) {
			heavies.push_back(i);
			is_heavy[i] = 1;
			for (auto to : gr[i])
				heavy_gr[to].push_back(i);
		}
	}
	vector<int> add(n, 0);
	while (q--) {
		char c;
		cin >> c;
		if (c == '+') {
			int v, x;
			cin >> v >> x;
			v--;
			if (is_heavy[v]) {
				add[v] += x;
			} else {
				for (auto to : gr[v])
					current[to] += x;
			}
		} else {
			int v;
			cin >> v;
			v--;
			int res = current[v];
			for (auto to : heavy_gr[v]) {
				res += add[to];
			}
			cout << res << '\n';
		}
	}
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
