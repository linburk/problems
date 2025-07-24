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

vector<vector<int> > gr;

void solve()
{
	int n, m;
	cin >> n >> m;
	vector<int> colors(n);
	cin >> colors;
	vector<vector<int> > gr(n);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		gr[a - 1].push_back(b - 1);
		gr[b - 1].push_back(a - 1);
	}
	int HEAVY_SIZE = 555;

	vector<bool> is_heavy(n, 0);
	vector<vector<int> > heavy_gr(n);
	vector<map<int, int> > heavy_cnt(n);
	for (int v = 0; v < n; v++) {
		if (gr[v].size() >= HEAVY_SIZE) {
			is_heavy[v] = 1;
			for (auto to : gr[v])
				heavy_gr[to].push_back(v);
		}
	}
	int cnt = 0;
	for (int v = 0; v < n; v++) {
		for (auto to : gr[v]) {
			if (colors[to] != colors[v])
				cnt++;
		}
		if (is_heavy[v]) {
			for (auto to : gr[v]) {
				heavy_cnt[v][colors[to]]++;
			}
		}
	}

	int q;
	cin >> q;
	while (q--) {
		int old_color, v, new_color;
		cin >> v >> new_color;
		v--;
		old_color = colors[v];
		colors[v] = new_color;
		if (is_heavy[v]) {
			cnt += 2 * heavy_cnt[v][old_color];
			cnt -= 2 * heavy_cnt[v][new_color];
		} else {
			for (auto to : gr[v]) {
				if (colors[to] == old_color)
					cnt += 2;
				if (colors[to] == new_color)
					cnt -= 2;
			}
		}
		for (auto to : heavy_gr[v]) {
			heavy_cnt[to][old_color]--;
			heavy_cnt[to][new_color]++;
		}
		cout << cnt / 2 << '\n';
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
