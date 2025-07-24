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

void stroki(int i, int n, vector<int> a){
    if (i == n){
        for (int j = 0; j < n; j++)
            cout << a[j];
        cout << endl;
        return;
    }
    a[i] = 0;
    stroki(i + 1, n, a);
    a[i] = 1;
    stroki(i + 1, n, a);
}


int main(){
    int n;
    vector<int> a(100, 0);
    cin >> n;
    stroki(0, n, a);
}