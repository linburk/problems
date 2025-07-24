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
	struct node {
		ll value = 0;
		ll bonus = 0;
		ll arypthm_bonus = 0;
		ll value_bonus = 0;
	};
	void push(int n, int l, int r)
	{
		int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
		int dist = r - l + 1;
		tree[n].value +=
			tree[n].bonus * dist + dist *
									   (2 * tree[n].arypthm_bonus +
										(dist - 1) * tree[n].arypthm_bonus) /
									   2;
		if (l != r) {
			tree[ls].arypthm_bonus += tree[n].arypthm_bonus;
			tree[rs].arypthm_bonus += tree[n].arypthm_bonus;
			tree[ls].bonus += tree[n].bonus;
			tree[rs].bonus +=
				tree[n].bonus + tree[n].arypthm_bonus * (m - l + 1);
		}
		if (tree[n].value_bonus) {
			tree[ls].value += tree[n].value_bonus;
			tree[rs].value += tree[n].value_bonus;
			tree[ls].value_bonus += tree[n].value_bonus;
			tree[rs].value_bonus += tree[n].value_bonus;
		}
		tree[n].value_bonus = tree[n].bonus = tree[n].arypthm_bonus = 0;
	}

private:
	void update(int ql, int qr, int d, int l, int r, int n)
	{
		int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
		push(n, l, r);
		if (l > qr || r < ql)
			return;
		if (ql <= l && r <= qr) {
			tree[n].bonus += (d > 0 ? 1 : -1) * (l - ql);
			tree[n].arypthm_bonus += d;
			push(n, l, r);
			return;
		}
		update(ql, qr, d, l, m, ls);
		update(ql, qr, d, m + 1, r, rs);
		tree[n].value = tree[ls].value + tree[rs].value;
	}
	void update_plus(int ql, int qr, ll val, int l, int r, int n)
	{
		int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
		push(n, l, r);
		if (l > qr || r < ql)
			return;
		if (ql <= l && r <= qr) {
			tree[n].bonus += val;
			push(n, l, r);
			return;
		}
		update_plus(ql, qr, val, l, m, ls);
		update_plus(ql, qr, val, m + 1, r, rs);
		tree[n].value = tree[ls].value + tree[rs].value;
	}
	ll get(int ql, int qr, int l, int r, int n)
	{
		int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
		push(n, l, r);
		if (l > qr || r < ql)
			return 0;
		if (ql <= l && r <= qr)
			return tree[n].value;
		ll _lg = get(ql, qr, l, m, ls);
		ll _rg = get(ql, qr, m + 1, r, rs);
		return _lg + _rg;
	}

protected:
	vector<node> tree;
	int tsize;

public:
	segmentTree(int n)
	{
		tsize = n;
		tree.resize(4 * tsize);
	}
	void update(int ql, int qr, int d)
	{
		update(ql, qr, d, 0, tsize - 1, 1);
	}
	void update_plus(int ql, int qr, ll val)
	{
		update_plus(ql, qr, val, 0, tsize - 1, 1);
	}
	ll get(int ql, int qr)
	{
		return get(ql, qr, 0, tsize - 1, 1);
	}
};
void solve()
{
	int n, m;
	cin >> n >> m;
	segmentTree rooms(n);
	//    while (m--){
	//        int c;
	//        cin >> c;
	//        if (c == 1){
	//            int l, r, v;
	//            cin >> l >> r >> v;
	//            rooms.update_plus(l, r, v);
	//        }
	//        if (c == 2){
	//            int l, r, d;
	//            cin >> l >> r >> d;
	//            rooms.update(l, r, d);
	//        }
	//
	//        cout << (c == 2 ? "UPDATE\n" : "BONUS\n");
	//        for (int i = 0; i < n; i++){
	//            cout << rooms.get(i, i) << ' ';
	//        } cout << "\n\n";
	//
	//    }
	//    for (int j = 0; j < m; j++){
	//        char c;
	//        cin >> c;
	//        if (c == '?'){
	//            int l, r;
	//            cin >> l >> r;
	//
	//            cout << "GET\n";
	//            for (int i = 0; i < n; i++){
	//                cout << rooms.get(i, i) << ' ';
	//            } cout << "\n";
	//
	//            cout << rooms.get(l - 1, r - 1) << "\n\n";
	//
	//        }
	//        if (c == 'R'){
	//            int i, q;
	//            cin >> i >> q;
	//            i--;
	//
	//            cout << "UPDATE_ARYPTHM\n";
	//
	//            int l_start = max(i - q + 1, 0);
	//            int r_start = min(i + q - 1, n - 1);
	//            int l_st_val = max(0, q - i - 1);
	//
	//            for (int i = 0; i < n; i++){
	//                cout << rooms.get(i, i) << ' ';
	//            } cout << "\n";
	//
	//            rooms.update_plus(l_start, i, l_st_val);
	//            rooms.update(l_start, i, 1);
	//
	//            for (int i = 0; i < n; i++){
	//                cout << rooms.get(i, i) << ' ';
	//            } cout << "\n";
	//
	//            rooms.update_plus(i + 1, r_start, q);
	//            rooms.update(i + 1, r_start, -1);
	//
	//            for (int i = 0; i < n; i++){
	//                cout << rooms.get(i, i) << ' ';
	//            } cout << "\n\n";
	//        }
	//        if (c == 'C'){
	//            int l, r, x;
	//            cin >> l >> r >> x;
	//            cout << "MINUS SEGM\n";
	//            for (int i = 0; i < n; i++){
	//                cout << rooms.get(i, i) << ' ';
	//            } cout << "\n";
	//
	//            rooms.update_plus(l - 1, r - 1, -x);
	//
	//            for (int i = 0; i < n; i++){
	//                cout << rooms.get(i, i) << ' ';
	//            } cout << "\n\n";
	//        }
	//        cout << endl;
	//    }
	//    cout << "RESULT\n";
	//    rooms = segmentTree(n);
	for (int j = 0; j < m; j++) {
		char c;
		cin >> c;
		if (c == '?') {
			int l, r;
			cin >> l >> r;
			cout << rooms.get(l - 1, r - 1) << "\n";
		}
		if (c == 'R') {
			int i, q;
			cin >> i >> q;
			i--;
			int l_start = max(i - q + 1, 0);
			int r_start = min(i + q - 1, n - 1);
			int l_st_val = max(0, q - i - 1);
			rooms.update_plus(l_start, i, l_st_val);
			rooms.update(l_start, i, 1);
			rooms.update_plus(i + 1, r_start, q);
			rooms.update(i + 1, r_start, -1);
		}
		if (c == 'C') {
			int l, r, x;
			cin >> l >> r >> x;
			rooms.update_plus(l - 1, r - 1, -x);
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
