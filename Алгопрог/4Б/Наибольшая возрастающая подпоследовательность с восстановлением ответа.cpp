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

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    vector<int> mem(n + 1, -1), ab(n + 1, 1);
    for (int i = 1; i <= n; i++){
        for (int j = i - 1; j > 0; j--){
            if (a[i - 1] > a[j - 1] and ab[i] < ab[j] + 1){
                ab[i] = ab[j] + 1;
                mem[i] = j - 1;
            }
        }
    }
    vector<int> ans;
    int max = -1;
    int pos = -1;
    for (int i = 1; i <= n; i++){
        if (ab[i] > max){
            max = ab[i];
            pos = i;
        }
    }
    while (pos != -1){
        ans.push_back(pos);
        pos = mem[pos];
    }
    for (int i = ans.size() - 1; i >= 0; i--){
        cout << a[ans[i]] << " ";
    }
}