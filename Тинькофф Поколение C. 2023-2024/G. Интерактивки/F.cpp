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

ll do_query(ll upY, ll downY, ll leftX, ll rightX)
{
	ll ans;
	cout << "? " << leftX << " " << downY << " " << rightX << " " << upY
		 << endl;
	cin >> ans;
	return ans;
}
ll mandarini;
ll n;
ll bin_search(ll upY, ll downY, ll leftX, ll rightX, ll bin_val)
{
	ll high = 0, low = 0;
	// 0 - upY   1 - downY   2 - leftX   3 - rightX
	if (bin_val == 0 || bin_val == 3) {
		high = (bin_val == 0 ? downY : leftX) - 1;
		low = n;
	}
	if (bin_val == 1 || bin_val == 2) {
		high = (bin_val == 1 ? upY : rightX) + 1;
		low = 1;
	}
	while (abs(high - low) > 1) {
		ll mid = (high + low) >> 1;
		ll ans = 0;
		if (bin_val == 0)
			ans = do_query(mid, downY, leftX, rightX);
		if (bin_val == 1)
			ans = do_query(upY, mid, leftX, rightX);
		if (bin_val == 2)
			ans = do_query(upY, downY, mid, rightX);
		if (bin_val == 3)
			ans = do_query(upY, downY, leftX, mid);
		if (ans < mandarini) {
			high = mid;
		} else {
			low = mid;
		}
	}
	return low;
}
void solve()
{
	cin >> n;
	ll upY = n, downY = 1, leftX = 1, rightX = n;
	mandarini = do_query(upY, downY, leftX, rightX);
	downY = bin_search(upY, downY, leftX, rightX, 1);
	leftX = bin_search(upY, downY, leftX, rightX, 2);
	ll width = do_query(downY, downY, leftX, n);
	ll height = mandarini / width;
	rightX = leftX + width - 1;
	upY = downY + height - 1;
	cout << "! " << leftX << " " << downY << " " << rightX << " " << upY
		 << endl;
	return;
}

int32_t main()
{
	setlocale(LC_ALL, "Russian");
#ifdef __APPLE__
	// std::freopen("/Users/dmitrii/Desktop/Code/project files/input.txt", "r",
	//              stdin);
	// std::freopen("/Users/dmitrii/Desktop/Code/project files/output.txt", "w",
	//              stdout);
#endif
	// std::cin.tie(0);
	// std::ios_base::sync_with_stdio(false);
	//    int t; cin >> t; for (; t; t--)
	solve();
	return 0;
}
