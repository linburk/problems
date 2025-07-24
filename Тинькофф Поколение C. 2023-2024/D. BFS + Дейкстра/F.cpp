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
#define pb(x) emplace_back(x)
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

} // namespace tools
using namespace tools;

string right_shift(string n)
{
	int t = n[n.size() - 1];
	for (int i = n.size() - 1; i >= 1; i--) {
		n[i] = n[i - 1];
	}
	n[0] = t;
	return n;
}
string left_shift(string n)
{
	int t = n[0];
	for (int i = 0; i < n.size(); i++) {
		n[i] = n[i + 1];
	}
	n[n.size() - 1] = t;
	return n;
}
void bfs(string &s, string &e)
{
	vector<int> past(10000, -2);
	past[stoi(s)] = -1;
	queue<string> q;
	q.push(s);
	int ans = -1;
	while (!q.empty()) {
		string cur = q.front();
		if (cur == e) {
			ans = stoi(cur);
			break;
		}
		q.pop();
		string ri = right_shift(cur);
		string li = left_shift(cur);
		string p1 = "-";
		string m1 = "-";
		if (cur[3] != '1') {
			m1 = cur;
			m1[3]--;
		}
		if (cur[0] != '9') {
			p1 = cur;
			p1[0]++;
		}
		if (past[stoi(ri)] == -2) {
			past[stoi(ri)] = stoi(cur);
			q.push(ri);
		}
		if (past[stoi(li)] == -2) {
			past[stoi(li)] = stoi(cur);
			q.push(li);
		}
		if (p1 != "-" && past[stoi(p1)] == -2) {
			past[stoi(p1)] = stoi(cur);
			q.push(p1);
		}
		if (m1 != "-" && past[stoi(m1)] == -2) {
			past[stoi(m1)] = stoi(cur);
			q.push(m1);
		}
	}
	vector<int> res;
	while (ans != -1) {
		res.pb(ans);
		ans = past[ans];
	}
	cout << res.size() << endl;
	for (int i = res.size() - 1; i >= 0; i--)
		cout << res[i] << endl;
	return;
}
void solve()
{
	string n1, n2;
	getline(cin, n1);
	getline(cin, n2);
	bfs(n1, n2);
}

int32_t main()
{
	setlocale(LC_ALL, "Russian");
#ifndef __APPLE__
	$FASTSTREAM
#endif
	solve();
	return 0;
}
