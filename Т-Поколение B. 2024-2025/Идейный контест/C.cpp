#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <climits>
#include <functional>
#include <random>
#include <string>
#include <iostream>
#include <numeric>
#include <vector>
#include <deque>

using u8 = unsigned char;
using i32 = int;
using i64 = long long;
using u64 = unsigned long long;

using std::cin, std::cout;
using std::vector, std::array, std::deque, std::pair, std::string;

std::mt19937 ru32(42);

struct dsu {
	vector<int> anc;
	vector<int> rank;
	vector<int> can;
	dsu(int n)
	{
		anc.resize(n);
		std::iota(anc.begin(), anc.end(), 0);
		rank.resize(n);
		can.resize(n, 1);
	}
	int leader(int a)
	{
		return anc[a] == a ? a : anc[a] = leader(anc[a]);
	}
	bool unite(int a, int b)
	{
		a = leader(a), b = leader(b);
		if (a == b) {
			int rs = can[a];
			can[a] = 0;
			return rs;
		}
		if (rank[a] > rank[b])
			std::swap(a, b);
		if (!can[a] && !can[b])
			return 0;
		rank[b] = std::max(rank[a] + 1, rank[b]);
		anc[a] = b;
		can[b] &= can[a];
		return 1;
	}
};

int main()
{
	cin.tie(nullptr);
	std::ios::sync_with_stdio(false);
#ifdef __APPLE__
	std::freopen(std::getenv("FINPATH"), "r", stdin);
	std::freopen(std::getenv("FOUTPATH"), "w", stdout);
#endif
	int n, m;
	cin >> n >> m;
	vector<pair<i64, pair<int, int> > > p(m);
	for (int i = 0; i < m; ++i) {
		cin >> p[i].second.first >> p[i].second.second >> p[i].first;
	}
	std::sort(p.rbegin(), p.rend());
	dsu d(n);
	i64 rs = 0;
	for (int i = 0; i < m; ++i) {
		auto [w, pp] = p[i];
		auto [a, b] = pp;
		if (d.unite(a - 1, b - 1))
			rs += w;
	}
	cout << rs << "\n";
}
