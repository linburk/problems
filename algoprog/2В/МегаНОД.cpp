#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int a = arr[i];
        int b = arr[i + 1];
        while (a != 0) {
            b = b % a;
            swap(b, a);
        }
        arr[i + 1] = b;
    }
    cout << arr[n - 1];
}