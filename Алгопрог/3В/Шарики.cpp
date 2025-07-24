#include <queue>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <list>

using namespace std;

bool summ(int &sum, vector<pair<int, int> > &a){
    bool flag = 0;
    for (int i = 0; i < a.size(); i++){
        if (a[i].second >= 3){
            sum += a[i].second;
            a.erase(a.begin() + i, a.begin() + i + 1);
            flag = 1;
        }
    }
    return flag;
}

int main()
{
    int n;
    cin >> n;
    vector<pair<int, int> > a;
    for (int i = 0; i < n; i++){
        int b;
        cin >> b;
        a.push_back({b, 1});
    }
    int sum = 0;
    bool flag = 1;
    for (auto i : a){
        cout << " {" << i.first << " " << i.second << "} " << " ";
    }
    cout << endl;
    while (flag){
        for (int i = 0; i < a.size() - 1; i++){
            cout << " {" << a[i].first << " " << a[i].second << "} " << " ";
            if (a[i].first == a[i + 1].first){
                a[i + 1].second += a[i].second;
                a.erase(a.begin() + i, a.begin() + i + 1);
            }
        }
        flag = summ(sum, a);
    }
    cout << endl <<  sum;
    for (auto i : a){
        cout << " {" << i.first << " " << i.second << "} " << " ";
    }
}