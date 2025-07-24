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
	os << "\n";
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
public:
	segmentTree(ll n, ll val)
	{
		tree.resize(4 * n);
		vector<ll> temp(n, val);
		tsize = n;
		build(temp, 0, tsize, 1);
	}

	ll get(ll ql, ll qr)
	{
		return get(ql, qr, 0, tsize, 1);
	}

	segmentTree(vector<ll> &array)
	{
		tree.resize(4 * array.size());
		tsize = array.size();
		build(array, 0, tsize, 1);
	}

	void update(ll ql, ll qr, ll val)
	{
		update(val, ql, qr, 0, tsize, 1);
	}

private:
	struct node {
		ll value;
		ll bonus = 0;
	};

	vector<node> tree;
	size_t tsize;

	void push(ll v, ll ls, ll rs)
	{
		if (tree[v].bonus != 0) {
			tree[ls].value += tree[v].bonus;
			tree[rs].value += tree[v].bonus;
			tree[ls].bonus += tree[v].bonus;
			tree[rs].bonus += tree[v].bonus;
			tree[v].bonus = 0;
		}
	}

	void build(vector<ll> &array, ll l, ll r, ll v)
	{
		if (r - l == 1) {
			tree[v].value = array[l];
			return;
		}
		ll m = (l + r) >> 1, ls = v << 1, rs = v << 1 | 1;
		build(array, l, m, ls);
		build(array, m, r, rs);
		tree[v].value = max(tree[ls].value, tree[rs].value);
	}

	void update(ll val, ll ql, ll qr, ll l, ll r, ll v)
	{
		if (qr <= l || r <= ql)
			return;
		if (ql <= l && r <= qr) {
			tree[v].value += val;
			tree[v].bonus += val;
			return;
		}
		ll m = (l + r) >> 1, ls = v << 1, rs = v << 1 | 1;
		push(v, ls, rs);
		update(val, ql, qr, l, m, ls);
		update(val, ql, qr, m, r, rs);
		tree[v].value = max(tree[ls].value, tree[rs].value);
	}

	ll get(ll ql, ll qr, ll l, ll r, ll v)
	{
		if (qr <= l || r <= ql)
			return 0;
		if (ql <= l && r <= qr) {
			return tree[v].value;
		}
		ll m = (l + r) >> 1, ls = v << 1, rs = v << 1 | 1;
		push(v, ls, rs);
		ll _lg = get(ql, qr, l, m, ls);
		ll _rg = get(ql, qr, m, r, rs);
		return max(_lg, _rg);
	}
};

void solve()
{
	int n, q;
	cin >> n >> q;
	vector<ll> a(n);
	cin >> a;
	segmentTree tree(a);
	for (int i = 0; i < q; i++) {
		char c;
		cin >> c;
		ll l, r, x, k, b;
		if (c == '+') {
			cin >> l >> r >> x;
			tree.update(l - 1, r, x);
		}
		if (c == '?') {
			cin >> l >> r >> k >> b;
			l--;
			ll ql = l, qr = r;
			ll ansBorder = 0;
			while (qr - ql > 1) {
				ll m = (qr + ql) / 2;
				ll midSearch = k * (m + 1) + b;
				ll getR = tree.get(m, r);
				if (getR < midSearch) {
					qr = m;
				} else {
					ql = m;
				}
			}
			if (ql + 1 != r)
				ansBorder = tree.get(ql + 1, r);
			for (ll i = max(ql - 1, l); i < min(qr + 1, r); i++)
				ansBorder =
					max(ansBorder, min(tree.get(i, i + 1), k * (i + 1) + b));
			cout << ansBorder << '\n';
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
