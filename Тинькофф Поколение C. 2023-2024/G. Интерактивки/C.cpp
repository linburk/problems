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

void solve()
{
	int n;
	cin >> n;
	int l = 0, r = n + 1;
	while (r - l > 2) {
		int m = ((r + l) >> 1);
		if (!(m % 2))
			m--;
		int even, odd;
		cout << "? " << m << endl;
		cin >> even;
		cout << "? " << m + 1 << endl;
		cin >> odd;
		if (even == odd) {
			l = m + 1;
		} else {
			r = m;
		}
		//        cout << l << " " << r << endl;
	}
	if (l == 0) {
		int f;
		cout << "? 1" << endl;
		cin >> f;
		cout << "! " << f << endl;
		return;
	}
	if (r == n + 1) {
		int f;
		cout << "? " << n << endl;
		cin >> f;
		cout << "! " << f << endl;
		return;
	}
	int first, second, third;
	cout << "? " << r - 1 << endl;
	cin >> first;
	cout << "? " << r << endl;
	cin >> second;
	cout << "? " << r + 1 << endl;
	cin >> third;
	if (second == third) {
		cout << "! " << first << endl;
	} else {
		cout << "! " << second << endl;
	}
}

int32_t main()
{
	setlocale(LC_ALL, "Russian");
#ifdef __APPLE__
//    std::freopen("/Users/dmitrii/Documents/Code/Code/input.txt", "r", stdin);
//    std::freopen("/Users/dmitrii/Documents/Code/Code/output.txt", "w",
//    stdout);
#endif
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(false);
	//    int t; cin >> t; for (; t; t--)
	solve();
	return 0;
}
