#include <bits/stdc++.h>
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
typedef vector<vector<bool> > vvb;

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

struct node {
	int next[2] = { 0, 0 };
	int count = 0;
};

vector<node> trie(1);

void insert(int x, int n = 0, int index = 31)
{
	if (index == -1) {
		trie[n].count = 1;
		return;
	}
	int bit = (x >> index) & 1;
	if (!trie[n].next[bit]) {
		trie[n].next[bit] = (int)trie.size();
		trie.push_back(node());
	}
	insert(x, trie[n].next[bit], index - 1);
	trie[n].count = (trie[n].next[0] ? trie[trie[n].next[0]].count : 0) +
					(trie[n].next[1] ? trie[trie[n].next[1]].count : 0);
}
int get(int x, int n = 0, int res = 0, int index = 31)
{
	if (index == -1)
		return res;
	int bit = (x >> index) & 1;
	if (trie[trie[n].next[bit]].count == 1 << index)
		bit = (bit == 1 ? 0 : 1);
	res |= (((x >> index) & 1) ^ bit) << index;
	return get(x, trie[n].next[bit], res, index - 1);
}

void solve()
{
	int n, m;
	cin >> n >> m;
	vector<int> a(n);
	cin >> a;
	for (auto i : a) {
		insert(i);
	}
	vector<int> q(m);
	cin >> q;
	int x = 0;
	for (auto i : q) {
		x ^= i;
		cout << get(x) << " ";
	}
}

int32_t main()
{
	setlocale(LC_ALL, "Russian");
#ifdef __APPLE__
	std::freopen("/Users/dmitrii/Documents/Code/Code/input.txt", "r", stdin);
	std::freopen("/Users/dmitrii/Documents/Code/Code/output.txt", "w", stdout);
#endif
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(false);
	//    int t;
	//    cin >> t;
	//    for (int i = 0; i < t; i++)
	solve();
	return 0;
}
