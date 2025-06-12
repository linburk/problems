#include <iostream>
#include <cmath>
#include <queue>
using namespace std;


int main()
{
    int n;
    cin >> n;
    vector<vector<int> > roads(n, vector<int>(n));

    vector<int> squaresmax(3);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> roads[i][j];
        }
    }

    int min = INT_MAX;

    for (int i = 0; i < n; i++)
    {
        vector<int> squares(3);
        int cur = 0;

        for (int j = 0; j < n; j++)
        {
            if (roads[i][j] != 0){
                squares[0] = i;
                cur += roads[i][j];
                int temp;
                squares[1] = j;
                int minli;
                int minl = 2001;
                for (int m = 0; m < n; m++){
                    if (m != i and roads[m][j] != 0 and roads[m][i] != 0){
                        temp = roads[m][j] + roads[m][i];
                        if (minl > temp){
                            minl = temp;
                            minli = m;
                        }   
                    }
                }
                cur += minl;
                squares[2] = minli;
                if (min > cur)
                {
                    min = cur;
                    squaresmax[0] = squares[0];
                    squaresmax[1] = squares[1];
                    squaresmax[2] = squares[2];
                }
            }     
        } 
    }

    for (int i = 0; i < 3; i++){
        cout << squaresmax[i] + 1 << " ";
    }
    
}