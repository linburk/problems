#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main()
{  
    int n;
    cin >> n;

    vector<vector<int> > input(n + 1, vector<int>(n + 1, 10000));
    vector<vector<char> > output(n, vector<char>(n, '-'));
    input[1][0] = 0;
    output[n - 1][n - 1] = '#';
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            char t;
            cin >> t;
            input[i][j] = int(t) - '0';
        }
    }

    
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            input[i][j] = min(input[i - 1][j], input[i][j - 1]) + input[i][j];
        }
    }

    int i = n;
    int j = n;
    while (i != 0)
    {
        while (j != 0)
        {
            if (input[i][j - 1] > input[i - 1][j])
            {
                output[i - 2][j - 1] = '#';
                i--;
            }
            else
            {
                output[i - 1][j - 2] = '#';
                j--;
            }
            if (i == 1 and j == 1){
                i--;
                j--;
            }
        }
    }

    for (auto x : output)
    { 
        for (auto y : x) 
            cout << y; 
        cout << endl;
    } 
}