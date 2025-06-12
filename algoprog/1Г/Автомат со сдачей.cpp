#include <iostream>
#include <vector>
#include <string>

using namespace std; 

int main(){
    int n; // Ð¿Ð¾ÐºÑÐ¿Ð°ÑÐµÐ»Ð¸
    cin >> n;
    vector<int> bank(n); // Ð¿Ð»Ð°ÑÐµÐ¶Ð¸
    for (int i = 0; i < n; i++)
        cin >> bank[i];

    int mon_5_s = 0;
    int mon_5_n = 0;

    for (int i = 0; i < n; i++){
        if (bank[i] > 5){
            if (mon_5_n * 5 <= bank[i]){
            mon_5_s += (bank[i] - 5 - mon_5_n * 5) / 5;
            }
            else {
                mon_5_n -= bank[i] / 5;
            }
        }
        else 
            mon_5_n++;
    }
    if (mon_5_s < 0)
        mon_5_s = 0;
    cout << mon_5_s;
}