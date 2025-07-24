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

bool comp(pair<pair<ll, ll>, ll> a, pair<pair<ll, ll>, ll> b)
{
	if (a.first.second == b.first.second) {
		return a.first.first < b.first.first;
	}
	return a.first.second < b.first.second;
}
bool comp2(pair<ll, ll> a, pair<ll, ll> b)
{
	if (a.second == b.second) {
		return a.first < b.first;
	}
	return a.second < b.second;
}

ll binsearch(vector<pair<pair<ll, ll>, ll> > &events, ll i, ll st)
{
	ll l = -1, r = i;
	while (r - l > 1) {
		int m = (l + r) / 2;
		if (events[m].first.second > st)
			r = m;
		else
			l = m;
	}

	return l + 1;
}

void solve()
{
	int n;
	cin >> n;
	vector<pair<pair<ll, ll>, ll> > events;
	vector<ll> dp(n + 1);
	for (ll i = 0; i < n; i++) {
		ll s, t, c;
		cin >> s >> t >> c;
		events.push_back({ { s, s + t }, c });
	}
	sort(all(events), comp);
	dp[0] = 0;
	for (ll i = 1; i <= n; i++) {
		ll j = binsearch(events, i, events[i - 1].first.first);
		dp[i] = max(dp[i - 1], dp[j] + events[i - 1].second);
	}
	cout << dp[n];
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
