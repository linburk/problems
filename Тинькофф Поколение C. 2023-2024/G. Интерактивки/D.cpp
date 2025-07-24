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
int n;
void bin_search(int l, int r, int k, bool comp)
{
	while (r - l > 1) {
		int m = (l + r) >> 1;
		int m_q;
		cout << "? " << m << endl;
		cin >> m_q;
		if ((comp ? m_q >= k : m_q <= k)) {
			r = m;
		} else {
			l = m;
		}
	}
	int r_q, l_q;
	l = max(1, l);
	r = min(n, r);
	cout << "? " << r << endl;
	cin >> r_q;
	if (r_q == k) {
		cout << "! " << r << endl;
		exit(0);
	}
	cout << "? " << l << endl;
	cin >> l_q;
	if (l_q == k) {
		cout << "! " << l << endl;
		exit(0);
	}
}
void solve()
{
	int k;
	cin >> n >> k;
	int l = 0, r = n + 1;
	while (r - l > 2) {
		int m = (r + l) >> 1;
		int m2 = m + 1;
		cout << "? " << m << endl;
		int m_q, m2_q;
		cin >> m_q;
		cout << "? " << min(m2, n) << endl;
		cin >> m2_q;
		if (m2_q > m_q) {
			l = m;
		} else {
			r = m;
		}
	}

	int max_ = -1, m_i;
	for (int i = max(l, 1); i <= min(r, n); i++) {
		cout << "? " << i << endl;
		int q;
		cin >> q;
		if (q > max_) {
			max_ = q;
			m_i = i;
		}
	}
	bin_search(0, m_i + 1, k, 1);
	bin_search(m_i - 1, n + 1, k, 0);
}

int32_t main()
{
	setlocale(LC_ALL, "Russian");
#ifdef __APPLE__
	// std::freopen("/Users/dmitrii/Documents/Code/Code/input.txt", "r", stdin);
	// std::freopen("/Users/dmitrii/Documents/Code/Code/output.txt", "w", stdout);
#endif
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(false);
	//    int t; cin >> t; for (; t; t--)
	solve();
	return 0;
}
