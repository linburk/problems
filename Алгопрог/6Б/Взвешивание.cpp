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

vector<int> lans, rans;
void recursion(vector<int> left, vector<int> right, vector<int> giri, int sumleft, int sumright){
    if (sumleft == sumright and lans.empty()){
        if (left.empty()){
            left.push_back(0);
        }
        if (right.empty())
            right.push_back(0);
        lans = left;
        rans = right;
        return;
    }
    if (giri.empty() or !lans.empty())
        return;
    if (sumright > sumleft){
        for (int i = 0; i < giri.size(); i++){
            vector<int> leftt = left, girit = giri;
            girit.erase(girit.begin() + i);
            leftt.push_back(giri[i]);
            recursion(leftt, right, girit, sumleft + giri[i], sumright);
        }
    }
    else {
        for (int i = 0; i < giri.size(); i++){
            vector<int> rightt = right, girit = giri;
            girit.erase(girit.begin() + i);
            rightt.push_back(giri[i]);
            recursion(left, rightt, girit, sumleft, sumright + giri[i]);
        }
    }
}

int main(){
    int k, n;
    cin >> k >> n;
    vector<int> giri(n);
    for (int i = 0; i < n; i++)
        cin >> giri[i];
    vector<int> left;
    vector<int> right;
    int sumleft = k;
    int sumright = 0;
    recursion(left, right, giri, sumleft, sumright);
    if (lans.empty()){
        cout << -1;
        return 0;
    }
    for (auto i : lans){
        cout << i << " ";
    }
    cout << '\n';
    for (auto i : rans){
        cout << i << " ";
    }
}