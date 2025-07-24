#include <iostream>
#include <cmath>
#include <vector>
using namespace std;


int main()
{
    int n;
    cin >> n;
    vector<vector<int> > bridges(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> bridges[i][j];
        }
    }
    vector<int> colors(n);
    for (int i = 0; i < n; i++)
    {
        cin >> colors[i];
    }
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (bridges[i][j]){
                if (colors[i] != colors[j])
                    cnt++;
            }
        }
    }
    cnt /= 2;
    cout << cnt;
}