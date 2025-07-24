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

void stroki(int i, int n, int k, int cnt, vector<int> a){
    if (cnt == k){
        for (int j = 0; j < n; j++){
            cout << a[j];
        }
        cout << endl;
        return;
    }
    if (i == n)
        return;
    a[i] = 0;
    stroki(i + 1, n, k, cnt, a);
    a[i] = 1;
    stroki(i + 1, n, k, cnt + 1, a);
}

int main(){
    vector<int> a(102, 0);
    int n, k;
    cin >> n >> k;
    stroki(0, n, k, 0, a);
}