#include <iostream>
#include <cmath>
using namespace std;

int main(){
    int n;
    cin >> n;

    vector<vector<char> > square(n, vector<char>(n));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> square[i][j];
    
    vector<vector<int> > result(n + 1, vector<int> (n + 1, 0));

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (square[i][j] == '#') 
                result[i + 1][j + 1]++;
        }
    }

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            if (result[i - 1][j] != 0 and result[i][j - 1] != 0 and result[i - 1][j - 1] != 0)
                result[i][j] = min(min(result[i - 1][j - 1] + 1, result[i - 1][j]),result[i][j - 1]) + 1;
        }
    }
    
    int max = 0;

    for (auto x : result){
        for (auto y : x){
            if (y > max)
                max = y;
        }
    }

    cout << max;
    
}