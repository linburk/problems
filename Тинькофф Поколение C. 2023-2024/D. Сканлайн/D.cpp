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

template <typename T> class linked_stack {
	struct node {
		T value;
		node *prev;
		node()
		{
			prev = nullptr;
		}
		node(T x, node *prev_)
		{
			value = x;
			prev = prev_;
		}
	};
	int len;
	node *head;

public:
	linked_stack()
	{
		len = 0;
	}
	void push(T value)
	{
		len++;
		head = new node(value, head);
	}
	void pop()
	{
		len--;
		node *t = head;
		head = head->prev;
		delete t;
	}
	void clear()
	{
		while (len > 0) {
			pop();
		}
	}
	~linked_stack()
	{
		clear();
	}
	T top()
	{
		return head->value;
	}
	int size()
	{
		return len;
	}
};

bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
	if (a.first.second == b.first.second)
		return a.first.first > b.first.first;
	return a.first.second < b.first.second;
}

void solve()
{
	vector<pair<pair<int, int>, int> > segm;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int l, r;
		cin >> l >> r;
		segm.push_back({ { l, r }, i });
	}
	linked_stack<pair<int, int> > current;
	sort(all(segm), comp);

	vector<int> ans(n, 0);
	for (auto [seg, ind] : segm) {
		auto [l, r] = seg;
		while (current.size() && current.top().first >= l) {
			ans[current.top().second] = ind + 1;
			current.pop();
		}
		current.push({ l, ind });
	}
	cout << ans;
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
