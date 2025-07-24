#include <bits/stdc++.h>

using namespace std;

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

class segmentTree {
	struct node {
		long long left;
		long long right;
		long long minval;
		long long maxval;
	};
	vector<node> tree;
	inline void update(node &cur)
	{
		cur.minval = min(tree[cur.left].minval, tree[cur.right].minval);
		cur.maxval = max(tree[cur.left].maxval, tree[cur.right].maxval);
	}
	void build(const std::vector<long long> &arr, const long long n,
			   const long long l, const long long r)
	{
		if (l == r) {
			tree[n].minval = arr[l];
			tree[n].maxval = arr[l];
			return;
		}
		long long mid = (l + r) >> 1;
		tree[n].left = n << 1;
		tree[n].right = n << 1 | 1;
		build(arr, tree[n].left, l, mid);
		build(arr, tree[n].right, mid + 1, r);
		update(tree[n]);
	}
	void update(long long i, const long long val, const long long n,
				const long long l, const long long r)
	{
		if (r < i || l > i)
			return;
		if (i <= l && r <= i) {
			tree[n].minval += val;
			tree[n].maxval += val;
			return;
		}
		long long m = (l + r) >> 1;
		update(i, val, tree[n].left, l, m);
		update(i, val, tree[n].right, m + 1, r);
		update(tree[n]);
	}
	long long get_min(const long long ql, const long long qr, const long long n,
					  const long long l, const long long r)
	{
		if (l > qr || r < ql)
			return 1E9;
		if (l >= ql && r <= qr || l == r)
			return tree[n].minval;
		long long m = (l + r) >> 1;
		long long _l = get_min(ql, qr, tree[n].left, l, m);
		long long _r = get_min(ql, qr, tree[n].right, m + 1, r);
		return min(_l, _r);
	}
	long long get_max(const long long ql, const long long qr, const long long n,
					  const long long l, const long long r)
	{
		if (l > qr || r < ql)
			return -1E9;
		if (l >= ql && r <= qr || l == r)
			return tree[n].maxval;
		long long m = (l + r) >> 1;
		long long _l = get_max(ql, qr, tree[n].left, l, m);
		long long _r = get_max(ql, qr, tree[n].right, m + 1, r);
		return max(_l, _r);
	}
	long long tsize;

public:
	segmentTree(const std::vector<long long> &arr)
	{
		tree.resize(4 * arr.size());
		tsize = arr.size();
		build(arr, 1, 0, arr.size() - 1);
	}
	segmentTree(size_t size, long long elem)
	{
		tree.resize(4 * size);
		tsize = size;
		vector<long long> *temp = new vector<long long>(size, elem);
		build(*temp, 1, 0, size - 1);
		delete temp;
	}
	void update(long long i, long long val)
	{
		update(i, val, 1, 0, tsize - 1);
	}
	long long get_min(long long ql, long long qr)
	{
		return get_min(ql, qr, 1, 0, tsize - 1);
	}
	long long get_max(long long ql, long long qr)
	{
		return get_max(ql, qr, 1, 0, tsize - 1);
	}
	long long size()
	{
		return tsize;
	}
};

void solve()
{
	long long n, k;
	cin >> n >> k;
	vector<long long> arr(n);
	cin >> arr;
	vector<long long> b(n);
	b[0] = arr[0];
	for (long long i = 1; i < n; i++)
		b[i] = arr[i] - arr[i - 1];
	segmentTree tree(b);
	for (long long i = 0; i < k; i++) {
		long long cm;
		cin >> cm;
		if (cm == 1) {
			long long l, r;
			cin >> l >> r;
			//            cout << tree.get_min(r, l - 1) << " " << tree.get_max(l, r -
			//            1) << endl;
			if (l > r)
				cout << (tree.get_min(r, l - 1) < -1 ? "No" : "Yes") << endl;
			else
				cout << (tree.get_max(l, r - 1) > 1 ? "No" : "Yes") << endl;
		} else {
			long long l, r, d;
			cin >> l >> r >> d;
			tree.update(l - 1, d);
			if (r < n)
				tree.update(r, -d);
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
#ifdef __APPLE__
	std::freopen("input.txt", "r", stdin);
	std::freopen("output.txt", "w", stdout);
#endif
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(false);
	//    long long t;
	//    cin >> t;
	//    for (long long i = 0; i < t; i++)
	solve();
	return 0;
}
