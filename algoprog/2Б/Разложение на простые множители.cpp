#include <iostream>
#include <vector>

using namespace std;

int main(){
    long long n;
    cin >> n;
    vector<long long> a;
    long long d = n;
    for (int i = 2; i <= n; i++){
        if (d % i == 0 and d != 0){
                d /= i;
                a.push_back(i);
                i--;
        }
        if (d == 0) 
            break;
    }
    for (int i = 0; i < a.size() - 1; i++){
        cout << a[i] << "*";
    }
    cout << a[a.size() - 1];
}