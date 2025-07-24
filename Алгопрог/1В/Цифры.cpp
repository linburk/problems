#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main(){
    int n = 1;
    vector<int> a;
    while (n != 0){
        cin >> n;
        a.push_back(n);
    }
    cout << count(a.begin(), a.end(), 1) << " ";
    cout << count(a.begin(), a.end(), 2) << " ";
    cout << count(a.begin(), a.end(), 3) << " ";
    cout << count(a.begin(), a.end(), 4) << " ";
    cout << count(a.begin(), a.end(), 5) << " ";
    cout << count(a.begin(), a.end(), 6) << " ";
    cout << count(a.begin(), a.end(), 7) << " ";
    cout << count(a.begin(), a.end(), 8) << " ";
    cout << count(a.begin(), a.end(), 9) << " ";

}