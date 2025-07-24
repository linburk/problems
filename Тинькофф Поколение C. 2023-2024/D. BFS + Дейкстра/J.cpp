#include <stdio.h>

#include <algorithm>
#include <bitset>
#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>

#ifdef __APPLE__
#include <fstream>
std::ifstream input("input.txt");
std::ofstream output("output.txt");
#define cin input
#define cout output
#endif

using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

#define endl '\n'
#define all(cont) cont.begin(), cont.end()
#define pb(x) push_back(x)
#define $FASTSTREAM   \
	std::cin.tie(0);  \
	std::cout.tie(0); \
	std::ios_base::sync_with_stdio(false);

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

template <typename T>
std::istream &operator>>(std::istream &is, std::pair<T, T> &p)
{
	is >> p.first >> p.second;
	return is;
}

} // namespace tools
using namespace tools;
namespace bigints
{
struct bigint {
	const static int digits = 1010;
	const static int base = 10;
	std::vector<int> value;
	bigint()
	{
		value.resize(digits, 0);
	}
	bigint(std::string val)
	{
		value.resize(digits, 0);
		for (int i = 0; i < val.size(); i++) {
			value[i] = val[val.size() - i - 1] - '0';
		}
	}
	bigint &operator+=(const bigint &num)
	{
		for (int i = 0; i < digits - 1; i++) {
			value[i] += num.value[i];
			if (value[i] >= base) {
				value[i + 1] += value[i] / base;
				value[i] %= base;
			}
		}
		return *this;
	}
	bigint &operator*=(const bigint &num)
	{
		std::vector<int> valres(digits, 0);
		for (int i = 0; i < digits / 2; i++) {
			for (int j = 0; j < digits / 2; j++) {
				valres[i + j] += value[i] * num.value[j];
			}
		}
		for (int i = 0; i < digits - 1; i++) {
			if (valres[i] >= base) {
				valres[i + 1] += valres[i] / base;
				valres[i] %= base;
			}
		}
		value = valres;
		return *this;
	}
	bigint &operator*=(const int num)
	{
		for (int i = 0; i < digits; i++) {
			value[i] *= num;
		}
		for (int i = 0; i < digits; i++) {
			if (value[i] > base) {
				value[i + 1] += value[i] / base;
				value[i] %= base;
			}
		}
		return *this;
	}
	bigint &operator/=(const int num)
	{
		for (int i = digits - 1; i >= 0; i--) {
			if (i > 0)
				value[i - 1] += (value[i] % num) * base;
			value[i] /= num;
		}
		return *this;
	}
	bigint &operator-=(const bigint &num)
	{
		for (int i = 0; i < digits; i++) {
			value[i] -= num.value[i];
		}
		for (int i = 0; i < digits - 1; i++) {
			if (value[i] < 0) {
				value[i] += base;
				value[i + 1]--;
			}
		}
		return *this;
	}
	const int operator%(const int num)
	{
		vector<int> valtemp = value;
		for (int i = digits - 1; i >= 0; i--) {
			if (i > 0) {
				valtemp[i - 1] += (valtemp[i] % num) * base;
				valtemp[i] /= num;
			}
		}
		return valtemp[0] % num;
	}
	const bool operator>(const bigint &num) const
	{
		for (int i = digits - 1; i >= 0; i--) {
			if (value[i] != num.value[i])
				return value[i] > num.value[i];
		}
		return 0;
	}
	const bool operator<(const bigint &num) const
	{
		for (int i = digits - 1; i >= 0; i--) {
			if (value[i] != num.value[i])
				return value[i] < num.value[i];
		}
		return 0;
	}
};
std::istream &operator>>(std::istream &is, bigint &num)
{
	std::string val;
	is >> val;
	for (int i = 0; i < val.size(); i++) {
		num.value[i] = val[val.size() - i - 1] - '0';
	}
	return is;
}
std::ostream &operator<<(std::ostream &os, bigint &num)
{
	std::string ans;
	for (int i = 0; i < num.digits; i++) {
		std::string x = std::to_string(num.value[i]);
		ans += x;
	}
	int end = ans.size() - 1;
	while (ans[end] == '0' && end > 0)
		end--;
	for (int i = end; i >= 0; i--)
		os << ans[i];
	return os;
}
} // namespace bigints
using namespace bigints;

void bfs(int mod, int k, bigint x, vector<int> &digits,
		 vector<vector<int> > &grfrom, vector<vector<pair<int, int> > > grto)
{
	queue<int> q;
	q.push(0);
	vector<int> dist(k, 1e9);
	dist[0] = 0;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (auto d : grfrom[v]) {
			if (dist[d] == 1e9) {
				dist[d] = dist[v] + 1;
				q.push(d);
			}
		}
	}
	if (dist[mod] == 1e9) {
		cout << -1;
		exit(0);
	}
	cout << x;
	vector<bool> used(k, 0);
	string s;
	q.push(mod);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (auto [d, y] : grto[v]) {
			if (dist[(v * 10 + d) % k] == dist[v] - 1) {
				s += to_string(d);
				q.push((v * 10 + d) % k);
				break;
			}
		}
	}
	cout << s;
}

void solve()
{
	bigint x;
	int k, n;
	cin >> x >> k >> n;
	vector<int> digits(n);
	cin >> digits;
	int mod = x % k;
	vector<vector<int> > grfrom(k);
	vector<vector<pair<int, int> > > grto(k);
	sort(all(digits));
	for (int i = 0; i < k; i++) {
		for (int d : digits) {
			grfrom[(i * 10 + d) % k].pb(i);
			grto[i].pb(make_pair(d, (i * 10 + d) % k));
		}
	}
	for (auto i : grto)
		sort(all(i));
	bfs(mod, k, x, digits, grfrom, grto);
}

int32_t main()
{
	setlocale(LC_ALL, "Russian");
#ifndef __APPLE__
	$FASTSTREAM
#endif
	//    int t;
	//    cin >> t;
	//    for (int i = 0; i < t; i++)
	solve();
	return 0;
}
