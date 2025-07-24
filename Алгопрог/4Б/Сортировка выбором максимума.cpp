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
    for (int i = n - 1; i >= 0; i--){
        int max = a[i];
        int maxind = i;
        for (int j = i - 1; j >= 0; j--){
            if (a[j] > max){
                max = a[j];
                maxind = j;
            }
        }
        swap(a[i], a[maxind]);
    }
    for (auto i : a)
        cout << i << " ";
}