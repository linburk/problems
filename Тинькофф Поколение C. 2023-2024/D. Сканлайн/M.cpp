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
		return a.second < b.second;
	return a.first < b.first;
}

bool comp2(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
	return comp(a.first, b.first);
}
void solve()
{
	int m;
	cin >> m;
	vector<pair<pair<int, int>, int> > segms;
	for (int i = 0, l = -1, r = -1; cin >> l >> r && !(l == 0 && r == 0); i++) {
		segms.push_back({ { l, r }, i });
	}
	sort(all(segms), comp2);
	int curleft = 0;
	vector<int> ans;
	set<pair<int, int> > right;
	right.insert({ -1e9, -1e9 });
	for (int i = 0; true; i++) {
		if (curleft >= m)
			break;
		if (i < segms.size() && segms[i].first.first <= curleft) {
			right.insert({ segms[i].first.second, i });
			continue;
		}
		auto [rmax, maxind] = *right.rbegin();
		if (rmax > curleft) {
			curleft = rmax;
			ans.push_back(maxind);
			i--;
			continue;
		}
		if (rmax <= curleft)
			break;
	}
	if (curleft < m) {
		cout << "No solution";
		exit(0);
	}
	cout << ans.size() << endl;
	for (auto k : ans) {
		auto [segm, ind] = segms[k];
		auto [l, r] = segm;
		cout << l << " " << r << endl;
	}
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
