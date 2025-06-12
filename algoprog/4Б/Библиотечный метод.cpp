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

void insertion_sorting(vector<int> &a){
    for (int i = 1; i < a.size(); i++){
        for (int j = i; j > 0 ; j--){
            if (a[j - 1] > a[j]) {
                swap(a[j - 1], a[j]);
                for (auto c : a)
                    cout << c << " ";
                cout << endl;
            }
            else
                break;
        }
    }
}

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    insertion_sorting(a);
//    for (auto i : a)
//        cout << i << " ";
}