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
    map<char, int> alphabetnumbs;
    map<int, char> alphabetchars;
    for (int i = 0; i <= 9; i++){
        alphabetnumbs[i + '0'] = i;
        alphabetchars[i] = i + '0';
    }
    for (int i = 10; i <= 36; i++){
        alphabetnumbs[i + 'A' - 10] = i;
        alphabetchars[i] = i + 'A' - 10;
    }

    string ans, s;
    getline(cin, s);
    int hex = 1, t = 0;
    for (int i = s.size() - 1; i >= 0; i--){
        t += (alphabetnumbs[s[i]] * hex);
        hex *= 16;
    }
    while (t > 0){
        ans += (t % 2 + '0');
        t /= 2;
    }
    for (int i = ans.size() - 1; i > -1; i--){
        cout << ans[i];
    }
}