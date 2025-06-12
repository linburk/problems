#include <iostream>
#include <unordered_map>
using namespace std;


int main() {
    unordered_map<int, int> m;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++){
        int a;
        cin >> a;
        m[i] = a;
    }
    int k;
    cin >> k;
    for (int i = 0; i < k; i++){
        int a;
        cin >> a;
        m[a]--;
    }
    for (int i = 1; i <= n; i++){
        if (m[i] < 0)
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
}