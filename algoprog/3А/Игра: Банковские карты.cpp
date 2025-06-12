#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int minimalmaxindex(vector<int> &a, int value){
    int max = INT_MAX;
    int maxi = -1;
    for (int i = 0; i < a.size(); i++){
        if (max > a[i] and a[i] > value){
            max = a[i];
            maxi = i;
        }
    }
    return maxi;
}
int maximalminindex(vector<int> &a, int value){
    int max = INT_MAX;
    int maxi = -1;
    for (int i = 0; i < a.size(); i++){
        if (max >= a[i] and a[i] >= value){
            max = a[i];
            maxi = i;
        }
    }
    return maxi;
}

int main(){
    int n;
    cin >> n;

    vector<int> sherlock(n);
    vector<int> moriarty(n);

    for (int i = 0; i < n; i++){
        char c;
        cin >> c;
        sherlock[i] = c - '0';
    }
        
    for (int i = 0; i < n; i++){
        char c;
        cin >> c;
        moriarty[i] = c - '0';
    }

    vector<int> mor1 = moriarty;
    vector<int> mor2 = moriarty;
    
    int cntmax = 0, cntmin = 0;
    for (int i = 0; i < n; i++){
        int x = sherlock[i];
        int ind = minimalmaxindex(mor1, x);
        if (ind != -1){
            cntmax++;
            mor1.erase(mor1.begin() + ind);
        }
    }
    for (int i = 0; i < n; i++){
        int x = sherlock[i];
        int ind = maximalminindex(mor2, x);
        if (ind == -1){
            cntmin++;
        }
        else
            mor2.erase(mor2.begin() + ind);
    }
    cout << cntmin << endl << cntmax;
    
}