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

template <typename T> class segment_tree {
	static const int MAX_SIZE = 1E5 + 100;
	static const int INF = 1E9 + 100;
	T tree[MAX_SIZE * 4];

public:
	segment_tree()
	{
		memset(tree, 0, sizeof tree);
	}
	int size = 0;
	void build(std::vector<T> &arr, int n = 1, int l = 0, int r = MAX_SIZE)
	{
		if (l == r) {
			tree[n] = arr[l];
			return;
		}
		int mid = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
		build(arr, ls, l, mid);
		build(arr, rs, mid + 1, r);
		tree[n] = tree[ls] + tree[rs];
	}

	void update(int i, T val, int n = 1, int l = 0, int r = MAX_SIZE)
	{
		if (r < i || l > i)
			return;
		if (l == i && r == i) {
			tree[n] = val;
			return;
		}
		int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
		update(i, val, ls, l, m);
		update(i, val, rs, m + 1, r);
		tree[n] = tree[ls] + tree[rs];
	}

	T get(int ql, int qr, int n = 1, int l = 0, int r = MAX_SIZE)
	{
		if (l > qr || r < ql)
			return 0;
		if (l >= ql && r <= qr)
			return tree[n];
		int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
		T _l = get(ql, qr, ls, l, m);
		T _r = get(ql, qr, rs, m + 1, r);
		return _l + _r;
	}
};

void solve()
{
	segment_tree<ll> tree;
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < k; i++) {
		char command;
		cin >> command;
		if (command == 'A') {
			int ind, x;
			cin >> ind >> x;
			tree.update(ind - 1, x);
		} else {
			int l, r;
			cin >> l >> r;
			cout << tree.get(l - 1, r - 1) << endl;
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
