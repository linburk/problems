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


int value = 0;
void bubble_sorting(vector<int> &a){
    for (int i = 0; i < a.size(); i++){
        for (int j = 1; j < a.size() - i; j++){
            if (a[j - 1] > a[j]){
                swap(a[j], a[j - 1]);
                value++;
            }
        }
    }
}

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    bubble_sorting(a);
    cout << value;
}