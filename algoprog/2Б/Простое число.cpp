#include <iostream>
using namespace std;

void schitatchisla(vector<bool> &resheto, int n, vector<long> &primes){
    for (int i = 2; i <= n; i++){
        if (resheto[i])
            primes.push_back(i);
        for (int j = i * i; j <= n; j += i){
            resheto[j] = 0;
        }
    }
}

int main(){
    vector<bool> resheto(40001, 1);
    vector<long> primes;
    vector<bool> &reshetor = resheto;
    vector<long> &primesr = primes;
    
    int n;
    cin >> n;
    schitatchisla(reshetor, 40000, primesr);
    cout << primes[n - 1];
}
// Ð¿Ð¾ÐºÐ° Ð¼Ð°ÐºÑÐ¸Ð¼Ð°Ð»ÑÐ½ÑÐ¹ Ð½Ð¾Ð¼ÐµÑ 4203