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
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(a.begin(), a.end());
    int sum = 0;
    for (int j = 1, i = a.size(); i >= 1; i--, j++){
        sum += a[i - 1];
        if (j % 3 == 0){
            sum -= a[i - 1];
        }
    }
    cout << sum;
}