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

template <typename T = long long> class segment_tree {
	static const int MAX_SIZE = 2 * 1E5 + 16;
	static const int INF = 1E9 + 100;

	T tree[MAX_SIZE * 4];

public:
	segment_tree()
	{
		memset(tree, 0, sizeof tree);
	}

	void build(const std::vector<T> &arr, const int n = 1, const int l = 0,
			   const int r = MAX_SIZE)
	{
		if (l == r) {
			tree[n] = (!arr[l] ? 1 : 0);
			return;
		}
		int mid = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
		build(arr, ls, l, mid);
		build(arr, rs, mid + 1, r);
		tree[n] = tree[ls] + tree[rs];
	}

	segment_tree(const std::vector<T> &arr)
	{
		segment_tree();
		build(arr, 1, 0, arr.size() - 1);
	}

	void update(const int i, const T val, const int n = 1, const int l = 0,
				const int r = MAX_SIZE)
	{
		if (r < i || l > i)
			return;
		if (l == i && r == i) {
			tree[n] = (!val ? 1 : 0);
			return;
		}
		int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
		update(i, val, ls, l, m);
		update(i, val, rs, m + 1, r);
		tree[n] = tree[ls] + tree[rs];
	}

	pair<T, T> get(int k, const int ql, const int qr, const int n = 1,
				   const int l = 0, const int r = MAX_SIZE)
	{
		if (l > qr || r < ql)
			return make_pair(-1, 0);
		if (l >= ql && r <= qr && tree[n] < k)
			return make_pair(-1, tree[n]);
		if (l == r)
			return make_pair(l + 1, 1);
		int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
		pair<T, T> _l = get(k, ql, qr, ls, l, m);
		if (_l.first != -1)
			return _l;
		pair<T, T> _r = get(k - _l.second, ql, qr, rs, m + 1, r);
		if (_r.first != -1)
			return _r;
		return make_pair(-1, _l.second + _r.second);
	}
};

void solve()
{
	int n, k;
	cin >> n;
	vector<int> arr(2 * 1E5 + 17, 0);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		if (x)
			arr[i] = 1;
	}
	segment_tree<int> tree(arr);
	cin >> k;
	for (int i = 0; i < k; i++) {
		char c;
		cin >> c;
		if (c == 's') {
			int l, r, kk;
			cin >> l >> r >> kk;
			pair<int, int> res = tree.get(kk, l - 1, r - 1);
			cout << res.first << " ";
		} else {
			int ind, x;
			cin >> ind >> x;
			if (x)
				x = 1;
			tree.update(ind - 1, x);
		}
	}
}

int32_t main()
{
	setlocale(LC_ALL, "Russian");
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(false);
	//    int t;
	//    cin >> t;
	//    for (int i = 0; i < t; i++)
	solve();
	return 0;
}
