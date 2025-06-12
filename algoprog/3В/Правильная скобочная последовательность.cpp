#include <queue>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

int main() {
    string s;
    getline(cin, s);
    vector<int> skobki(3, 0);
    for (auto c : s){
        if (c == '(')
            skobki[0]++;
        else if (c == '{')
            skobki[1]++;
        else if (c == '[')
            skobki[2]++;
        else if (c == ']')
            skobki[2]--;
        else if (c == '}')
            skobki[1]--;
        else if (c == ')')
            skobki[0]--;
    }
    if (skobki[0] == 0 and skobki[1] == 0 and skobki[2] == 0)
        cout << "yes";
    else
        cout << "no";
}