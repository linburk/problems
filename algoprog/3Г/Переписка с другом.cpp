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

int counter(vector<bool> &used, vector<int> &messages, vector<int> &count, int start, int k, int n){
    if (start == -1)
        return 0;
    int cntto = 0, cntcur = 0;
    for (int i = start - k; i <= start + k; i++){
        if (i >= 0 and i < n){
            if (!used[i]){
                used[i] = 1;
                cntto++;
            }
            cntcur++;
        }
    }
    count[start] = cntcur + counter(used, messages, count, messages[start], k, n);
    return count[start] - cntcur + cntto;
}


int main() {
    int n, k;
    cin >> n >> k;
    vector<int> messages(n);
    vector<int> count(n, -1);
    for (int i = 0, a; i < n; i++){
        cin >> a; a--;
        messages[i] = a;
    }
    for (int start = 0; start < n; start++){
        if (count[start] == -1){
            vector<bool> used(n, 0);
            counter(used, messages, count, start, k, n);
        }
    }
    for (auto i : count){
        cout << i << " ";
    }
}