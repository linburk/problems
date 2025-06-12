#include <queue>
#include <deque>
#include <iostream>
#include <vector>
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

void A(int i, int n, vector<int> a, vector<bool> w){
    if (i == n){
        for (int j = 0; j < n; j++)
            cout << a[j];
        cout << endl;
        return;
    }
    for (int j = 1; j <= n; j++){
        if (!w[j]) {
            w[j] = 1;
            a[i] = j;
            A(i + 1, n, a, w);
            w[j] = 0;
        }
    }
}
int main(){
    vector<int> a(11);
    vector<bool> w(11, 0);
    int n;
    cin >> n;
    A(0, n, a, w);
}