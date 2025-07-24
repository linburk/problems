#include <queue>
#include <deque>
#include <iostream>
#include <set>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <list>
#include <iterator>
#include <iomanip>
#include <stdio.h>
#include <fstream>
using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define all(cont) cont.begin(), cont.end()
#define size_(cont) cont.size()
#define sort_(cont) sort(all(cont))
#define $FASTSTREAM \
    cin.tie(nullptr); \
    cout.tie(nullptr); \
    ios_base::sync_with_stdio(false);
#define $FILEINPUT \
    ifstream fin("input.txt"); \
    ofstream fout("output.txt");
ll gcd(ll a, ll b){
    while (b > 0){
        a %= b;
        swap(a, b);
    }
    return a;
}
ll lcm(ll a, ll b){
    return a * b / gcd(a, b);
}
ll max(ll a, ll b){
    if (a > b)
        return a;
    return b;
}
ll min(ll a, ll b){
    if (a < b)
        return a;
    return b;
}

struct tree {
    tree *left, *right;
    pair<ll, ll> max_value;
    void update() {
        max_value = max(left->max_value, right->max_value);
    }
};

void build(tree* cur, ll left, ll right, vector<ll> &a){
    if (left == right) {
        cur->max_value = {a[left], left};
        return;
    }
    ll middle = (left + right) / 2;
    tree* left_ = new tree();
    tree* right_ = new tree();
    cur->left = left_;
    cur->right = right_;
    build(cur->left, left, middle, a);
    build(cur->right, middle + 1, right, a);
    cur->update();
}
pair<ll, ll> get_max(tree* cur, ll left, ll right, ll qleft, ll qright){
    if (qleft > right or qright < left){
        return {-1, -1};
    }
    if (qleft <= left and qright >= right){
        return cur->max_value;
    }
    long long middle = (left + right) / 2;
    return max(get_max(cur->left, left, middle, qleft, qright), get_max(cur->right, middle + 1, right, qleft, qright));
}


int32_t main() {
    $FASTSTREAM
    tree* binary_tree = new tree();
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++){
        cin >> a[i];
    }
    build(binary_tree, 0, n - 1, a);
    ll q;
    cin >> q;
    for (ll i = 0; i < q; i++){
        int l, r;
        cin >> l >> r;
        l--; r--;
        pair<ll, ll> t = get_max(binary_tree, 0, n - 1, l, r);
        cout << t.first << " " << t.second + 1 << "\n";
    }
}