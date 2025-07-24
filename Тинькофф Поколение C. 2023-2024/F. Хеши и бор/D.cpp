#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef vector<bool> vb;
typedef vector<vector<bool> > vvb;

#define all(cont) cont.begin(), cont.end()
#define funique(cont) cont.erase(unique(all(cont)), cont.end())

namespace tools
{
// mt19937_64 rng(chrono::steady_clock().now().time_since_epoch().count());
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

class hash_array {
protected:
	static const size_t MAXLEN = 1E5;
	static const int64_t f1 = 31, f2 = 37;
	static const int64_t m2 = 1E9 + 7;
	static array<array<int64_t, 2>, MAXLEN> POWERS_INITIALIZE()
	{
		array<array<int64_t, 2>, MAXLEN> result;
		result[0][0] = result[0][1] = 1;
		for (int64_t i = 1; i < MAXLEN; i++) {
			result[i][0] = result[i - 1][0] * f1;
			result[i][1] = (result[i - 1][1] % m2 * f2) % m2;
		}
		return result;
	}
	static inline array<array<int64_t, 2>, MAXLEN> powers = POWERS_INITIALIZE();

private:
	vector<vector<int64_t> > hash_memory;
	void HASH_INITIALIZE(string &arr)
	{
		size_t N = arr.size();
		hash_memory.resize(N + 1, vector<int64_t>(2));
		hash_memory[N][0] = hash_memory[N][1] = 0;
		for (int64_t i = N - 1; i >= 0; i--) {
			hash_memory[i][0] = arr[i] + 1 - 'a' + hash_memory[i + 1][0] * f1;
			hash_memory[i][1] =
				(arr[i] % m2 + 1 - 'a' + (hash_memory[i + 1][1] * f2) % m2) %
				m2;
		}
	}

public:
	pair<int64_t, int64_t> get_hash(size_t l, size_t r)
	{
		return { hash_memory[l][0] - hash_memory[r][0] * powers[r - l][0],
				 (hash_memory[l][1] -
				  (hash_memory[r][1] * powers[r - l][1]) % m2 + m2) %
					 m2 };
	}
	hash_array(string &arr)
	{
		HASH_INITIALIZE(arr);
	}
};

void solve()
{
	string p, t;
	cin >> p >> t;
	ll n = t.size(), m = p.size();
	vector<bool> enter(n, 0);
	ll cnt = 0;
	for (ll right = m, left = 0; left <= n - m; ++left, right = left + m) {
		ll incorrect = 0;
		for (int j = 0; j < m; j++) {
			if (p[j] != t[j + left]) {
				incorrect++;
			}
		}
		if (incorrect <= 1) {
			cnt++;
			enter[left] = 1;
		}
	}
	cout << cnt << "\n";
	for (int i = 0; i < n; i++) {
		if (enter[i])
			cout << i + 1 << " ";
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
