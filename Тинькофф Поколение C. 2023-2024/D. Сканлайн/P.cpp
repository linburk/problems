#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

#define endl '\n'
#define all(cont) cont.begin(), cont.end()
#define unique(cont) cont.erase(unique(all(cont)), cont.end())
#define pb(x) emplace_back(x)

namespace tools
{

template <typename T> T gcd(T a, T b)
{
	while (b > 0) {
		a %= b;
		std::swap(a, b);
	}
	return a;
}

template <typename T> T lcm(T a, T b)
{
	return a * b / gcd(a, b);
}

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
	return os;
}

template <typename T>
std::istream &operator>>(std::istream &is, std::vector<std::vector<T> > &matrix)
{
	for (auto &i : matrix)
		for (auto &j : i)
			is >> j;
	return is;
}

template <typename T>
std::ostream &operator<<(std::ostream &os,
						 const std::vector<std::vector<T> > &matrix)
{
	for (const auto &i : matrix) {
		for (const auto &j : i)
			os << j << " ";
		os << "\n";
	}
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

bool comp(pair<int, int> a, pair<int, int> b)
{
	if (a.first == b.first)
		return a.second > b.second;
	return a.first < b.first;
}
bool comp2(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
	return comp(a.first, b.first);
}
struct times {
	int h;
	int m;
	int s;
	const bool operator<(const times &b) const
	{
		if (h == b.h) {
			if (m == b.m) {
				return s < b.s;
			}
			return m < b.m;
		}
		return h < b.h;
	}
	const bool operator==(const times &b) const
	{
		return h == b.h && m == b.m && s == b.s;
	}
};

bool timecomp(times a, times b)
{
	return a < b;
}

void solve()
{
	ll n;
	cin >> n;
	vector<times> clock(n);
	for (int i = 0; i < n; i++) {
		char c;
		cin >> clock[i].h >> c >> clock[i].m >> c >> clock[i].s;
	}
	sort(all(clock), timecomp);
	vector<ll> res(n, 0);
	for (int i = 1; i < n; i++) {
		times a = clock[0], b = clock[i];
		ll diff = 12 * 60 * 60 - (b.h - a.h) * 60 * 60 - (b.m - a.m) * 60 -
				  (b.s - a.s);
		//        cout << diff << endl;
		res[0] += diff;
	}

	for (int i = 1; i < n; i++) {
		times a = clock[i - 1], b = clock[i];
		ll diff = (b.h - a.h) * 60 * 60 + (b.m - a.m) * 60 + (b.s - a.s);
		res[i] = res[i - 1] + n * diff - 12 * 60 * 60;
	}
	times mintime;
	ll mintimeres = 1e18;
	for (int i = 0; i < n; i++) {
		if (res[i] < mintimeres) {
			mintimeres = res[i];
			mintime = clock[i];
		}
	}
	//    mintime.h = (mintime.h == 0 ? 12 : mintime.h);
	cout << mintime.h << ":"
		 << (mintime.m <= 9 ? "0" + to_string(mintime.m) :
							  to_string(mintime.m)) +
				":" +
				(mintime.s <= 9 ? "0" + to_string(mintime.s) :
								  to_string(mintime.s));
}

int32_t main()
{
	setlocale(LC_ALL, "Russian");
#ifdef __APPLE__
	std::freopen("input.txt", "r", stdin);
	std::freopen("output.txt", "w", stdout);
#endif
	std::cin.tie(0);
	std::cout.tie(0);
	std::ios_base::sync_with_stdio(false);
	//    int t;
	//    cin >> t;
	//    for (int i = 0; i < t; i++)
	solve();
	return 0;
}
