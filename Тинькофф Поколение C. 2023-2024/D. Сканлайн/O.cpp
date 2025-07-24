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

void solve()
{
	//    int n;
	//    cin >> n;
	//    vector<pair<pair<int, int>, int> > segms(n);
	//    for (int i = 0; i < n; i++){
	//        int s, t, c;
	//        cin >> s >> t >> c;
	//        segms[i] = {{s, s + t}, c};
	//    }
	//    sort(all(segms), comp2);

	int n;
	cin >> n;
	vector<pair<pair<int, int>, int> > segments;
	vector<int> ans(n, 0);
	for (int i = 0; i < n; i++) {
		int l, r;
		cin >> l >> r;
		segments.push_back({ { l, 1 }, i });
		segments.push_back({ { r, -1 }, i });
	}
	sort(all(segments), comp2);
	int was = 0, not_was = n;
	for (auto [p, ind] : segments) {
		auto [time, event] = p;
		if (event == 1) {
			not_was--;
			ans[ind] += was;
		}
		if (event == -1) {
			was++;
			ans[ind] += not_was;
			ans[ind] = n - ans[ind] - 1;
		}
	}
	cout << ans;
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
