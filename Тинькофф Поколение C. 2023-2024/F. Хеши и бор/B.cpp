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

static const int ALPHABET = 26;
struct node {
	vector<pair<int, int> > next;
	int terminal = 0;
};
vector<node> trie(1);
int check(int n, char a)
{
	int fl = -1;
	for (int i = 0; i < trie[n].next.size(); i++) {
		if (trie[n].next[i].first == a - 'a')
			fl = i;
	}
	return fl;
}
void insert(string &s, int n, int index)
{
	if (index == s.size()) {
		trie[n].terminal++;
		return;
	}
	int checknind = check(n, s[index]);
	if (checknind == -1) {
		trie.push_back(node());
		checknind = (int)trie[n].next.size();
		trie[n].next.push_back({ s[index] - 'a', (int)trie.size() - 1 });
	}
	insert(s, trie[n].next[checknind].second, index + 1);
}
vector<char> strdfs(1000001);
vector<string> sorted_strings;
void dfs(int n, int index)
{
	if (trie[n].terminal) {
		string t;
		for (int i = 0; i < index; i++)
			t += strdfs[i];
		for (int i = 0; i < trie[n].terminal; i++) {
			sorted_strings.push_back(t);
		}
	}
	for (int i = 0; i < ALPHABET; i++) {
		int checknind = check(n, 'a' + i);
		if (checknind != -1) {
			strdfs[index] = 'a' + i;
			dfs(trie[n].next[checknind].second, index + 1);
		}
	}
}
void solve()
{
	string s;
	cin >> s;
	vector<string> points;
	for (int i = 0; i < s.length(); i++) {
		int j = i;
		string t;
		if (s[j] == '.') {
			while (s[j] == '.' && j < s.length()) {
				t += '.';
				j++;
			}
			points.push_back(t);
			i = j - 1;
		} else {
			while (s[j] != '.' && j < s.length()) {
				t += s[j];
				j++;
			}
			insert(t, 0, 0);
			i = j - 1;
		}
	}
	dfs(0, 0);
	if (s[0] == '.') {
		for (int i = 0; i < points.size(); i++) {
			cout << points[i];
			if (i < sorted_strings.size())
				cout << sorted_strings[i];
		}
	} else {
		for (int i = 0; i < sorted_strings.size(); i++) {
			cout << sorted_strings[i];
			if (i < points.size())
				cout << points[i];
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
