#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<bool> primes(vector<bool>& resheto) {
    for (int i = 2; i <= sqrt(200000); i++) {
        if (resheto[i]) {
            for (int j = i * i; j <= 200000; j += i)
                resheto[j] = 0;
        }
    }
    return resheto;
}

int main() {
    int n;
    cin >> n;

    vector<bool> resheto(200001, 1);
    vector<bool>& r = resheto;
    resheto[0] = 0;
    resheto[1] = 0;
    resheto = primes(r);

    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= n - i; j++) {
            if (resheto[i] and resheto[j] and i + j == n) {
                cout << i << " " << j;
                return 1;
            }
        }
    }
}