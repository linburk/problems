#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

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

class segmentTree {
	struct node {
		int value = -1;
		int size = 1;
		int cnt = 0;
		int suff = 0;
		int pref = 0;
	};
	void update(node &n, node &ls, node &rs)
	{
		n.pref = ls.pref;
		n.suff = rs.suff;
		if (ls.pref == ls.size) {
			n.pref += rs.pref;
		}
		if (rs.suff == rs.size) {
			n.suff += ls.suff;
		}
		n.cnt = max({ ls.cnt, rs.cnt, ls.suff + rs.pref, n.pref, n.suff });
	}
	void relax(size_t n)
	{
		tree[n].cnt = tree[n].suff = tree[n].pref = (tree[n].value == 0);
	}

private:
	void build(vector<int> &arr, size_t l, size_t r, size_t n)
	{
		if (l == r) {
			tree[n].value = arr[l];
			relax(n);
			return;
		}
		size_t m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
		build(arr, l, m, ls);
		build(arr, m + 1, r, rs);
		tree[n].size = tree[ls].size + tree[rs].size;
		update(tree[n], tree[ls], tree[rs]);
	}
	void update(int i, int val, size_t l, size_t r, size_t n)
	{
		if (l > i || r < i)
			return;
		if (l == i && r == i) {
			tree[n].value = val;
			relax(n);
			return;
		}
		size_t m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
		update(i, val, l, m, ls);
		update(i, val, m + 1, r, rs);
		update(tree[n], tree[ls], tree[rs]);
	}
	node get(int ql, int qr, size_t l, size_t r, size_t n)
	{
		if (l > qr || r < ql)
			return { 0, 0, 0 };
		if (ql <= l && r <= qr) {
			return tree[n];
		}
		size_t m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
		node _lg = get(ql, qr, l, m, ls);
		node _rg = get(ql, qr, m + 1, r, rs);
		node res;
		res.size = _lg.size + _rg.size;
		update(res, _lg, _rg);
		return res;
	}

protected:
	vector<node> tree;
	size_t tsize;

public:
	segmentTree(vector<int> &arr)
	{
		tsize = arr.size();
		tree.resize(4 * tsize);
		build(arr, 0, tsize - 1, 1);
	}
	int get(int ql, int qr)
	{
		return get(ql, qr, 0, tsize - 1, 1).cnt;
	}
	void update(int i, int val)
	{
		update(i, val, 0, tsize - 1, 1);
	}
};

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	cin >> a;
	segmentTree tree(a);
	int k;
	cin >> k;
	while (k--) {
		string comm;
		cin >> comm;
		if (comm == "QUERY") {
			int l, r;
			cin >> l >> r;
			cout << tree.get(l - 1, r - 1) << '\n';
		} else {
			int i, x;
			cin >> i >> x;
			tree.update(i - 1, x);
		}
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
