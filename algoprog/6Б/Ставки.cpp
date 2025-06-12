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

map<int, set<int> > memory;
map<int, set<int> > ans;
vector<int> memstavki;
void recursion(vector<vector<pair<int, int> > > &stavki, int i, int n, int stavka, vector<int> memstavok) {
    if (i == n + 1){
        if (ans.empty()){
            memstavki = memstavok;
            ans = memory;
        }
        return;
    }
    int a = stavki[i - 1][stavka].first, b = stavki[i - 1][stavka].second;
    int c = stavki[i - 1][(stavka + 1) % 2].first, d = stavki[i - 1][(stavka + 1) % 2].second;
    if (binary_search(memory[b].begin(), memory[b].end(), a) or binary_search(memory[c].begin(), memory[c].end(), d))
        return;

    set<int> tempa = memory[a], tempd = memory[d];
    memory[a].insert(memory[b].begin(), memory[b].end());
    memory[a].insert(b);
    memory[d].insert(memory[c].begin(), memory[c].end());
    memory[d].insert(c);
    memstavok[i - 1] = 0;
    recursion(stavki, i + 1, n, 0, memstavok);
    memstavok[i - 1] = 1;
    recursion(stavki, i + 1, n, 1, memstavok);
    memory[a] = tempa;
    memory[d] = tempd;
}


int main(){
    int n, k;
    cin >> k >> n;
    vector<vector<pair<int, int> > > stavki(n);
    for (int i = 0; i < n; i++){
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        stavki[i].push_back(make_pair(a, b));
        stavki[i].push_back(make_pair(c, d));
    }
    vector<int> memstavok(n);
    recursion(stavki, 1, n, 0, memstavok);
    recursion(stavki, 1, n, 1, memstavok);
    if (ans.empty()){
        cout << 0;
        return 0;
    } // ÑÐ°Ð·Ð»Ð¾Ð¶Ð¸ÑÑ Ð¿Ð¾ Ð¼ÐµÑÑÐ°Ð¼
    vector<pair<set<int>, int> > answer;
    for (int i = 1; i <= k; i++){
        answer.push_back(make_pair(ans[i], i));
    }
    sort(answer.begin(), answer.end());
    for (int i = answer.size() - 1; i >= 0; i--){
        cout << answer[i].second << " ";
    }
}