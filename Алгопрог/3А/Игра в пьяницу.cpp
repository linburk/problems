#include <iostream>
#include <cmath>
#include <queue>
using namespace std;


int main()
{
    queue<int> first;
    queue<int> second;

    for (int i = 0; i < 5; i++)
    {
        int x;
        cin >> x;
        if (x == 0)
            x = 10;
        first.push(x);
    }
    for (int i = 0; i < 5; i++)
    {
        int x;
        cin >> x;
        if (x == 0)
            x = 10;
        second.push(x);
    }

    int a, b;
    int cnt = 0;

    while (true)
    {
        a = first.front();
        b = second.front();

        if (a > b)
        {
            first.pop();
            second.pop();
            first.push(a);
            first.push(b);
        }
        else if (b > a)
        {
            first.pop();
            second.pop();
            second.push(a);
            second.push(b);
        }

        cnt++;

        if (first.empty())
        {
            cout << "second " << cnt;
            break;
        }
        if (second.empty())
        {
            cout << "first " << cnt;
            break;
        }
        if (cnt > 1000000){
            cout << "botva";
            break;
        }
    }
}