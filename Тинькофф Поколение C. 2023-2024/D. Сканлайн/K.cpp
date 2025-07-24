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
	if (a.first.first == b.first.first) {
		return a.second < b.second;
	}
	return a.first.first < b.first.first;
}
bool comp2(pair<ll, ll> a, pair<ll, ll> b)
{
	if (a.second == b.second) {
		return a.first < b.first;
	}
	return a.second < b.second;
}
bool comp3(pair<ll, ll> a, pair<ll, ll> b)
{
	if (a.second == b.second) {
		return a.first < b.first;
	}
	return a.second < b.second;
}

bool comp4(pair<pair<ll, ll>, ll> a, pair<pair<ll, ll>, ll> b)
{
	return comp3(a.first, b.first);
}

void solve()
{
	ll n;
	cin >> n;
	vector<pair<pair<ll, ll>, ll> > events;
	vector<pair<pair<ll, ll>, ll> > segments;
	for (ll i = 1; i <= n; i++) {
		ll s, f;
		cin >> s >> f;
		events.push_back({ { s, i }, 1 });
		events.push_back({ { f, i }, -1 });
		segments.push_back({ { s, f }, i });
	}
	sort(all(events), comp);
	sort(all(segments), comp4);
	pair<ll, ll> ans;
	ll diff = 1e10;
	ll minf = -1e10, maxs = -1e10;
	ll minfind = -1, maxsind = -1;
	stack<pair<ll, ll> > open;
	if (n < 5000) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i != j) {
					auto [p1, ind1] = segments[i];
					auto [p2, ind2] = segments[j];
					auto [l1, r1] = p1;
					auto [l2, r2] = p2;
					if (l2 < r1 && r2 > l1) {
						if (diff > r2 - l1) {
							diff = r2 - l1;
							ans = { ind1, ind2 };
						}
					}
					if (l2 > l1 && r2 < r1) {
						if (diff > r2 - l2) {
							diff = r2 - l2;
							ans = { ind1, ind2 };
						}
					}
				}
			}
		}
	} else {
		for (auto [p, event] : events) {
			auto [time, ind] = p;

			if (event == 1) {
				maxs = time;
				maxsind = ind;
			}
			if (event == -1 && time > maxs && (minf <= maxs || time < minf) &&
				ind != maxsind) {
				minf = time;
				minfind = ind;
			}

			if (minf != -1 && maxs != -1) {
				if (minf - maxs < diff && minf - maxs > 0) {
					ans = { maxsind, minfind };
					diff = minf - maxs;
				}
			}

			if (event == 1) {
				open.push({ time, ind });
			}
			if (event == -1) {
				if (open.size() > 1) {
					if (time - open.top().first < diff &&
						ind == open.top().second) {
						diff = time - open.top().first;
						open.pop();
						ans = { ind, open.top().second };
					} else {
						open.pop();
					}
				} else {
					open.pop();
				}
			}
		}
	}
	if (diff == 1e10) {
		cout << 0;
		exit(0);
	}
	cout << ans.first << " " << ans.second;
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
