#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> cards;
    int max = 0, maxnum = 0;
    for (int i = 0; i < n; i++){
        int t;
        cin >> t;
        if (t > max)
            max = t;
        if (t == max)
            maxnum++;
    }
    if (maxnum % 2 == 0)
        cout << "Agasa";
    else
        cout << "Conan";
}