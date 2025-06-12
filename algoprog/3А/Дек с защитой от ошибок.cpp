#include <iostream>
#include <cmath>

using namespace std;


int main()
{
    int deque[50000];
    int indexleft = 25000, indexright = 25000;
    string command;
    while (command != "exit"){
        cin >> command;
        if (command == "push_front"){
            int numb;
            cin >> numb;
            indexleft--;
            deque[indexleft] = numb;
            cout << "ok" << endl;
        }
        if (command == "push_back"){
            int numb;
            cin >> numb;
            deque[indexright] = numb;
            indexright++;
            cout << "ok" << endl;
        }
        if (command == "pop_front"){
            if (indexleft == indexright){
                cout << "error" << endl;
            }
            else {
                cout << deque[indexleft] << endl;
                indexleft++;
            }
        }
        if (command == "pop_back"){
            if (indexleft == indexright){
                cout << "error" << endl;
            }
            else {
                cout << deque[indexright - 1] << endl;
                indexright--;
            }
        }
        if (command == "front"){
            if (indexleft == indexright){
                cout << "error" << endl;
            }
            else {
                cout << deque[indexleft] << endl;

            }   
        }
        if (command == "back"){
                if (indexleft == indexright){
                cout << "error" << endl;
            }
            else {
                cout << deque[indexright - 1] << endl;

            }
        }
        if (command == "size"){
            cout << indexright - indexleft << endl;
        }
        if (command == "clear"){
            indexleft = 25000;
            indexright = 25000;
            cout << "ok" << endl;
        }
    }
    cout << "bye";
}