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
vector<int> a, blocks;
const int BLOCK_SIZE = 555;

int get(int l, int r)
{
	int res = 0;
	while (l <= r) {
		if (l % BLOCK_SIZE == 0 && l + BLOCK_SIZE <= r) {
			res += blocks[l / BLOCK_SIZE];
			l += BLOCK_SIZE;
		} else {
			res += a[l] == 0;
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
	blocks.resize(n / BLOCK_SIZE + 1, 0);
	cin >> a;
	for (int i = 0; i < n; i++) {
		blocks[i / BLOCK_SIZE] += a[i] == 0;
	}
	int k;
	cin >> k;
	while (k--) {
		int l, r;
		cin >> l >> r;
		cout << get(l - 1, r - 1) << ' ';
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
