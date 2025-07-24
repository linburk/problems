#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

struct threepair{
    int first;
    int second;
    int third;
};

int main(){
    int m, n;
    cin >> m >> n;
    threepair a;
    a.first = 0; a.second = 0; a.third = 0;
    vector<pair<threepair, threepair> > helpers(n, make_pair(a, a));
    for (int i = 0; i < n; i++){
        cin
        >> helpers[i].first.first
        >> helpers[i].first.second
        >> helpers[i].first.third
        ;
    }
    vector<int> mem(n, 0);
    int t = 0;
    while (m > 0){
        for (int i = 0; i < n; i++){
            if (helpers[i].second.third > 0)
                helpers[i].second.third--;
            if (helpers[i].second.first > 0)
                helpers[i].second.first--;
        }
        for (int i = 0; i < n; i++){
            if (m > 0) {
                if (helpers[i].second.third == 0 and helpers[i].second.first == 0) {
                    if (helpers[i].second.second < helpers[i].first.second) {
                        helpers[i].second.first = helpers[i].first.first;
                        helpers[i].second.second++;
                        m--;
                        mem[i]++;
                    } else {
                        helpers[i].second.third = helpers[i].first.third;
                        helpers[i].second.second = 0;
                    }
                }
            }
        }
        t++;
    }
    int max = 0;
    for (int i = 0; i < n; i++){
        if (helpers[i].second.first > max)
            max = helpers[i].second.first - 1;
    }
    t += max;
    cout << t << endl;
    for (int i = 0; i < n; i++){
        cout << mem[i] << " ";
    }
}