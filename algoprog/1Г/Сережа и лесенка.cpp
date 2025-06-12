#include <iostream>
#include <vector>

using namespace std; 

int main(){
    int n;
    cin >> n;
    vector<int> a(5002);
    for (int x, i = 0; i < n; i++)
    {
        cin >> x;
        a[x]++;
    }
    int maxel = 0;
    for (int i = 0; i < 5002; i++)
    {
        if (a[i] != 0 and i > maxel)
        {
            maxel = i;
        }
            
    }
    a[maxel] = 1;
    
    for (int i = 0; i < 5002; i++)
    {
        if (a[i] > 2)
            a[i] = 2;
    }

    int count = 0;
    vector<int> b;
    for (int i = 0; i < 5002; i++)
    {
        if (a[i] != 0)
        {
            count++;
            b.push_back(i);
            a[i]--;
        }
    }
    for (int i = 5002; i > 0; i--)
    {
        if (a[i] != 0)
        {
            count++;
            b.push_back(i);
            a[i]--;
        }
    }
    
    cout << count << endl;
    for (int x : b)
        cout << x << " ";
 
}