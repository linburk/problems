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

vector<int> blocks;
vector<int> a;
const int BLOCK_SIZE = 555;
int get(int l, int r)
{
	int res = -1e9;
	while (l <= r) {
		if (l % BLOCK_SIZE == 0 && l + BLOCK_SIZE <= r) {
			res = max(res, blocks[l / BLOCK_SIZE]);
			l += BLOCK_SIZE;
		} else {
			res = max(res, a[l]);
			l++;
		}
	}
	return res;
}
void solve()
{
	int n;
	cin >> n;
	a.resize(n);
	blocks.resize(n / BLOCK_SIZE + 1, -1e9);
	cin >> a;
	for (int i = 0; i < n / BLOCK_SIZE + 1; i++) {
		for (int j = i * BLOCK_SIZE; j < (i + 1) * BLOCK_SIZE && j < n; j++) {
			blocks[i] = max(blocks[i], a[j]);
		}
	}
	int k;
	cin >> k;
	while (k--) {
		int l, r;
		cin >> l >> r;
		cout << get(l - 1, r - 1) << "\n";
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
