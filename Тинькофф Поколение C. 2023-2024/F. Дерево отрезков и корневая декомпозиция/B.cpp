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
		ll value;
		ll bonus = 0;
	};
	void push(int n)
	{
		if (tree[n].bonus) {
			tree[n << 1].value += tree[n].bonus;
			tree[n << 1 | 1].value += tree[n].bonus;
			tree[n << 1].bonus += tree[n].bonus;
			tree[n << 1 | 1].bonus += tree[n].bonus;
			tree[n].bonus = 0;
		}
	}
	void update(int n)
	{
		tree[n].value = apply(tree[n << 1].value, tree[n << 1 | 1].value);
	}

private:
	void build(vector<int> &arr, size_t l, size_t r, int n)
	{
		if (l == r) {
			tree[n].value = arr[l];
			return;
		}
		size_t m = (l + r) >> 1;
		build(arr, l, m, n << 1);
		build(arr, m + 1, r, n << 1 | 1);
		update(n);
	}
	void update(int val, int ql, int qr, size_t l, size_t r, int n)
	{
		if (l > qr || r < ql)
			return;
		if (ql <= l && r <= qr) {
			tree[n].value += val;
			tree[n].bonus += val;
			return;
		}
		push(n);
		size_t m = (l + r) >> 1;
		update(val, ql, qr, l, m, n << 1);
		update(val, ql, qr, m + 1, r, n << 1 | 1);
		update(n);
	}
	ll get(int ql, int qr, size_t l, size_t r, int n)
	{
		if (l > qr || r < ql)
			return NEUTRAL;
		if (ql <= l && r <= qr)
			return tree[n].value;
		push(n);
		size_t m = (l + r) >> 1;
		ll _lg = get(ql, qr, l, m, n << 1);
		ll _rg = get(ql, qr, m + 1, r, n << 1 | 1);
		return (apply(_lg, _rg));
	}

protected:
	function<ll(ll, ll)> apply = [](ll a, ll b) { return max(a, b); };
	const ll NEUTRAL = LONG_LONG_MIN;
	vector<node> tree;
	size_t tsize;

public:
	segmentTree(vector<int> &arr)
	{
		tsize = arr.size();
		tree.resize(4 * tsize);
		build(arr, 0, tsize - 1, 1);
	}
	void update(int val, int ql, int qr)
	{
		update(val, ql, qr, 0, tsize - 1, 1);
	}
	ll get(int ql, int qr)
	{
		return get(ql, qr, 0, tsize - 1, 1);
	}
};

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	cin >> a;
	int m;
	cin >> m;
	segmentTree tree(a);
	while (m--) {
		char comm;
		cin >> comm;
		if (comm == 'a') {
			int l, r, val;
			cin >> l >> r >> val;
			tree.update(val, l - 1, r - 1);
		}
		if (comm == 'm') {
			int l, r;
			cin >> l >> r;
			cout << tree.get(l - 1, r - 1) << ' ';
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
