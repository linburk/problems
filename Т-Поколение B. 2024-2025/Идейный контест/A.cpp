#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
#include <deque>

using std::cin, std::cout;
using std::vector, std::array, std::deque, std::pair;

int const mod = 1E9 + 7;

using i64 = long long;
template <typename T> using matrix = vector<vector<T> >;
template <typename T> matrix<T> operator*(matrix<T> a, matrix<T> b)
{
	matrix<T> rs(a.size(), vector<T>(b[0].size()));
	for (int i = 0; i < a.size(); ++i) {
		for (int j = 0; j < b[0].size(); ++j) {
			for (int k = 0; k < b.size(); ++k) {
				rs[i][j] = (1ll * a[i][k] * b[k][j] + rs[i][j]) % mod;
			}
		}
	}
	return rs;
};

template <typename T> matrix<T> pow(matrix<T> a, i64 k)
{
	matrix<T> rs(a.size(), vector<T>(a.size()));
	for (int i = 0; i < rs.size(); ++i)
		rs[i][i] = 1;
	for (; k; k >>= 1) {
		if (k & 1)
			rs = rs * a;
		a = a * a;
	}
	return rs;
}

int main()
{
	cin.tie(nullptr);
	std::ios::sync_with_stdio(false);
#ifdef __APPLE__
	std::freopen(std::getenv("FINPATH"), "r", stdin);
	std::freopen(std::getenv("FOUTPATH"), "w", stdout);
#endif
	int t;
	cin >> t;
	for (int i = 0; i < t; ++i) {
		int n;
		cin >> n;
		vector<i64> a(n), b(n);
		for (auto &&i : a)
			cin >> i;
		for (auto &&i : b)
			cin >> i;
		int c = 0;
		i64 sa = std::accumulate(a.begin(), a.end(), 0ll);
		i64 sb = std::accumulate(b.begin(), b.end(), 0ll);
		for (int i = 0; i < n; ++i)
			c += b[i] <= sa - a[i];
		bool yes = 0;
		for (int i = 0; i < n; ++i) {
			yes |= c - (b[i] <= sa - a[i]) == n - 1 && sb - b[i] <= sa;
		}
		cout << (yes ? "YES\n" : "NO\n");
	}
}
