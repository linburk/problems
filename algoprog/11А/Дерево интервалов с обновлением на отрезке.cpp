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
using namespace std;

struct tree {
    tree *left, *right;
    long long value;
    long long bonus = 0;
    void update(){
        value = left->value + right->value;
    }
    void update(long long k){
        value += k;
        bonus += k;
    }
    void push(){
        left->update(bonus);
        right->update(bonus);
        bonus = 0;
    }
};

void build(tree* cur, long long left, long long right, vector<long long> &a){
    if (left == right) {
        cur->value = a[left];
        return;
    }
    long long middle = (left + right) / 2;
    tree* left_ = new tree();
    tree* right_ = new tree();
    cur->left = left_;
    cur->right = right_;
    build(cur->left, left, middle, a);
    build(cur->right, middle + 1, right, a);
    cur->update();
}
void update(tree* cur, long long left, long long right, long long qleft, long long qright, long long value){
    if (left > qright or right < qleft)
        return;
    if (left == right){
        cur->value += value;
        return;
    }
    long long middle = (left + right) / 2;
    update(cur->left, left, middle, qleft, qright, value);
    update(cur->right, middle + 1, right, qleft, qright, value);
    cur->update();
}
long long get_value(tree* cur, long long left, long long right, long long qleft, long long qright){
    if (qleft > right or qright < left){
        return 0;
    }
    if (qleft <= left and qright >= right){
        return cur->value;
    }
    cur->push();
    long long middle = (left + right) / 2;
    return get_value(cur->left, left, middle, qleft, qright) + get_value(cur->right, middle + 1, right, qleft, qright);
}

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    long long n, q;
    cin >> n;
    vector<long long> a(n);
    for (long long i = 0; i < n; i++)
        cin >> a[i];
    tree* binary_tree = new tree();
    build(binary_tree, 0, n - 1, a);
    cin >> q;
    for (int i = 0; i < q; i++){
        char c;
        cin >> c;
        switch (c) {
            case 'g':{
                int pos;
                cin >> pos;
                pos--;
                cout << get_value(binary_tree, 0, n - 1, pos, pos) << "\n";
                break;
            }
            case 'a':{
                int l, r, x;
                cin >> l >> r >> x;
                l--; r--;
                update(binary_tree, 0, n - 1, l, r, x);
                break;
            }

        }
    }
}