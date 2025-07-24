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
	struct node {
		T max_value;
		T max_cnt;
		node()
		{
		}
		node(T max_value, T max_cnt)
			: max_value(max_value)
			, max_cnt(max_cnt)
		{
		}
	};

	static const int MAX_SIZE = 1E5 + 100;
	static const int INF = 1E9 + 100;
	node tree[MAX_SIZE * 4];

public:
	segment_tree()
	{
		memset(tree, 0, sizeof tree);
	}
	int size = 0;
	void build(std::vector<T> &arr, int n = 1, int l = 0, int r = MAX_SIZE)
	{
		if (l == r) {
			tree[n].max_value = arr[l];
			tree[n].max_cnt = 1;
			return;
		}
		int mid = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
		build(arr, ls, l, mid);
		build(arr, rs, mid + 1, r);
		if (tree[ls].max_value == tree[rs].max_value) {
			tree[n].max_cnt = tree[ls].max_cnt + tree[rs].max_cnt;
			tree[n].max_value = tree[ls].max_value;
		} else if (tree[ls].max_value > tree[rs].max_value) {
			tree[n].max_value = tree[ls].max_value;
			tree[n].max_cnt = tree[ls].max_cnt;
		} else {
			tree[n].max_value = tree[rs].max_value;
			tree[n].max_cnt = tree[rs].max_cnt;
		}
	}

	void update(int i, T val, int n = 1, int l = 0, int r = MAX_SIZE)
	{
		if (r < i || l > i)
			return;
		if (l == i && r == i) {
			tree[n].max_value = val;
			tree[n].max_cnt = 1;
			return;
		}
		int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
		update(i, val, ls, l, m);
		update(i, val, rs, m + 1, r);
		if (tree[ls].max_value == tree[rs].max_value) {
			tree[n].max_cnt = tree[ls].max_cnt + tree[rs].max_cnt;
			tree[n].max_value = tree[ls].max_value;
		} else if (tree[ls].max_value > tree[rs].max_value) {
			tree[n].max_value = tree[ls].max_value;
			tree[n].max_cnt = tree[ls].max_cnt;
		} else {
			tree[n].max_value = tree[rs].max_value;
			tree[n].max_cnt = tree[rs].max_cnt;
		}
	}

	pair<T, T> get(int ql, int qr, int n = 1, int l = 0, int r = MAX_SIZE)
	{
		if (l > qr || r < ql)
			return { -INF, 0 };
		if (l >= ql && r <= qr)
			return { tree[n].max_value, tree[n].max_cnt };
		int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
		pair<T, T> _l = get(ql, qr, ls, l, m);
		pair<T, T> _r = get(ql, qr, rs, m + 1, r);
		if (_l.first == _r.first)
			return { _l.first, _l.second + _r.second };
		return (_l.first > _r.first ? _l : _r);
	}
};

void solve()
{
	segment_tree<int> tree;
	int n, k;
	cin >> n;
	vector<int> arr(1E5 + 100, 0);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	tree.build(arr);
	cin >> k;
	for (int i = 0; i < k; i++) {
		char command;
		cin >> command;
		if (command == 'Q') {
			int l, r;
			cin >> l >> r;
			cout << tree.get(l - 1, r - 1).second << endl;
		} else {
			int index, x;
			cin >> index >> x;
			tree.update(index - 1, x);
		}
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
