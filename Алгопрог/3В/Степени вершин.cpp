#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> sum(n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            int x;
            cin >> x;
            if (x == 1)
                sum[i]++;
        }
    }
    for (auto i : sum){
        cout << i << endl;
    }
}