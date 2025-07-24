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

namespace hash_structure
{

class hash_string : public std::string {
private:
	static const size_t MAXLEN = 50001;
	static const unsigned short P1 = 131, P2 = 139;
	static std::vector<std::pair<unsigned long long, unsigned long long> >
	initialize_pows()
	{
		std::vector<std::pair<unsigned long long, unsigned long long> > powers(
			MAXLEN);
		powers[0] = { 1, 1 };
		for (int i = 1; i < MAXLEN; i++) {
			powers[i].first = 1LL * powers[i - 1].first * P1;
			powers[i].second = 1LL * powers[i - 1].second * P2;
		}
		return powers;
	}
	static inline std::vector<std::pair<unsigned long long, unsigned long long> >
		pows = initialize_pows();
	std::vector<std::pair<unsigned long long, unsigned long long> > hash;

public:
	void calculate_hash()
	{
		hash.resize(length() + 2);
		hash[length() + 1] = { 1, 1 };
		for (auto i = rbegin(); i != rend(); i++) {
			size_t ind = length() - distance(rbegin(), i);
			hash[ind] = { *i - 'A' + 1 + 1LL * hash[ind + 1].first * P1,
						  *i - 'A' + 1 + 1LL * hash[ind + 1].second * P2 };
		}
	}

	const std::pair<unsigned long long, unsigned long long>
	get_hash(size_t l, size_t r) const
	{
		// 0-indexed
		return { hash[l + 1].first - hash[r].first * pows[r - l - 1].first,
				 hash[l + 1].second - hash[r].second * pows[r - l - 1].second };
	}

	const std::pair<unsigned long long, unsigned long long> get_hash() const
	{
		return get_hash(0, length() + 1);
	}
};
} // namespace hash_structure
using namespace hash_structure;

void solve1()
{
	//    int n;
	//    cin >> n;
	//    cin.get();
	//    hash_string a, b;
	//    getline(cin, a);
	//    getline(cin, b);
	//    b = a;
	//    reverse(all(b));
	//    a.calculate_hash();
	//    b.calculate_hash();
	//    vector<int> ans(n);
	//    for (int i = 0; i < n; i++){
	//
	//    }
	//    cout << ans;
}

void dijkstra(vector<vector<vector<pair<pair<int, int>, int> > > > &gr,
			  vector<int> &cost)
{
	vector<vector<int> > dist(gr.size(), vector<int>(2, 1e9));
	vector<vector<bool> > marks(gr.size(), vector<bool>(2, 0));
	dist[0][0] = 0;
	for (int i = 0; i < gr.size() * 2; i++) {
		pair<int, int> v = { -1, -1 };
		for (int j = 0; j < gr.size(); j++) {
			for (int k = 0; k < 2; k++) {
				if (!marks[j][k] && (v == make_pair(-1, -1) ||
									 dist[v.first][v.second] > dist[j][k]))
					v = make_pair(j, k);
			}
		}
		if (v == make_pair(-1, -1))
			break;
		marks[v.first][v.second] = 1;
		for (auto j : gr[v.first][v.second]) {
			dist[j.first.first][j.first.second] =
				min(dist[j.first.first][j.first.second],
					dist[v.first][v.second] + j.second);
		}
	}
	cout << (dist[gr.size() - 1][0] == 1e9 && dist[gr.size() - 1][1] ?
				 -1 :
				 min(dist[gr.size() - 1][0], dist[gr.size() - 1][1]));
}

void solve()
{
	int n;
	cin >> n;
	vector<int> cost(n);
	for (auto &i : cost)
		cin >> i;
	int m;
	cin >> m;
	vector<vector<vector<pair<pair<int, int>, int> > > > gr(
		n, vector<vector<pair<pair<int, int>, int> > >(2));
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		gr[a][0].push_back({ { b, 0 }, cost[a] });
		gr[a][0].push_back({ { a, 1 }, cost[a] });
		gr[a][1].push_back({ { b, 0 }, 0 });
		gr[a][1].push_back({ { b, 1 }, cost[a] });

		gr[b][0].push_back({ { a, 0 }, cost[b] });
		gr[b][1].push_back({ { a, 0 }, 0 });
		gr[b][1].push_back({ { a, 1 }, cost[b] });
	}
	dijkstra(gr, cost);
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
