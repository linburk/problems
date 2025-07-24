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
int main() {
    string s;
    getline(cin, s);
    vector<vector<int> > max_pal(s.size() + 2, vector<int>(s.size() + 2, 0));
    vector<vector<string> > memory(s.size() + 2, vector<string>(s.size()));
    for (int left = 1; left <= s.size(); left++){
        max_pal[left][left] = 1;
        memory[left][left] += s[left - 1];
    }
    for (int length = 1; length <= s.size(); length++){
        for (int left = 1; left <= s.size() - length + 1; left++){
            int right = left + length;
            if (s[right - 1] != s[left - 1]){
                max_pal[left][right] = max(max_pal[left + 1][right], max_pal[left][right - 1]);
                memory[left][right] = (memory[left + 1][right].size() > memory[left][right - 1].size() ? memory[left + 1][right] : memory[left][right - 1]);
            }
            else {
                max_pal[left][right] = max_pal[left + 1][right - 1] + 2;
                memory[left][right] = s[left - 1] + memory[left + 1][right - 1] + s[right - 1];
            }
        }
    }
    cout << max_pal[1][s.size()] << "\n";
    cout << memory[1][s.size()];
}