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

class _trie {
	struct node {
		int next[2] = { 0, 0 };
		int terminal = 0;
	};
	vector<node> trie;

public:
	void insert(int x, int n = 0, int index = 31)
	{
		if (index == -1) {
			trie[n].terminal++;
			return;
		}
		int bit = (x >> index) & 1;
		if (!trie[n].next[bit]) {
			trie[n].next[bit] = (int)trie.size();
			trie.push_back(node());
		}
		insert(x, trie[n].next[bit], index - 1);
	}

	pair<int, int> get_max(int x, int n = 0, int res = 0, int index = 31)
	{
		if (index == -1) {
			return { res, trie[n].terminal };
		}
		int bit = (x >> index) & 1;
		if (trie[n].next[1 ^ bit]) {
			res |= (1 ^ bit) << index;
			return get_max(x, trie[n].next[1 ^ bit], res, index - 1);
		} else {
			res |= bit << index;
			return get_max(x, trie[n].next[bit], res, index - 1);
		}
	}
	_trie()
	{
		trie.resize(1);
	}
};

void solve()
{
	_trie trie;
	_trie trie_inv;
	int n;
	cin >> n;
	vector<int> nums(n);
	cin >> nums;
	for (int x : nums) {
		trie.insert(x);
		trie_inv.insert(INT_MAX ^ x);
	}
	for (int x : nums) {
		pair<int, int> get_max = trie.get_max(x);
		pair<int, int> get_min;
		for (int bit = 0; bit < 31; bit++) {
			get_min = trie_inv.get_max(x ^ (1 << bit));
			get_min.first ^= INT_MAX;
			if (get_min.first != x || get_min.second > 1) {
				break;
			}
		}
		cout << (x ^ get_min.first) << " " << (x ^ get_max.first) << "\n";
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
