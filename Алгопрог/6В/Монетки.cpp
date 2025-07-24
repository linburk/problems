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

vector<int> ans;
int maxi = 0;
void rec(vector<int> moneti, map<int, int> nominal, int cursum, int need, vector<int> nominali){
    if (cursum == need and (moneti.size() < ans.size() or ans.empty())){
        ans = moneti;
    }
    if (cursum > maxi)
        maxi = cursum;
    for (auto i : nominali){
        if (i + cursum <= need and nominal[i] > 0) {
            vector<int> tmoneti = moneti;
            tmoneti.push_back(i);
            nominal[i]--;
            rec(tmoneti, nominal, cursum + i, need, nominali);
            nominal[i]++;
        }
    }
    return;
}

int main(){
    int n, k;
    cin >> k >> n;
    map<int, int> nominal;
    vector<int> nominali;
    for (int i = 0; i < n; i++){
        int c;
        cin >> c;
        nominal[c] = 2;
        nominali.push_back(c);
    }
    vector<int> moneti;
    rec(moneti, nominal, 0, k, nominali);
    if (ans.empty()) {
        if (maxi > k)
            cout << 0;
        else
            cout << -1;
        return 0;
    }
    cout << ans.size() << "\n";
    for (auto i : ans)
        cout << i << " ";
}