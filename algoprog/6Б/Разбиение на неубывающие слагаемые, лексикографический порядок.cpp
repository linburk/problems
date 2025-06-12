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

void foo(int i, int s, int n, vector<int> a) {
    if (s == n){
        for (auto j : a)
            if (j > 0)
                cout << j << " ";
        cout << endl;
        return;
    }
    for (int j = (a[i - 1] > 0 ? a[i - 1] : 1); j < n - s + 1; j++){
        a[i] = j;
        s += j;
        foo(i + 1, s, n, a);
        s -= j;
        a[i] = 0;
    }
}

int main(){
    vector<int> a(1000, 0);
    int n;
    cin >> n;
    foo(1, 0, n, a);
}