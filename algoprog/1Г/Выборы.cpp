#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std; 

int main(){
    int nparties, mbul;
    cin >> nparties >> mbul;
    vector<vector<char> > votes(mbul, vector<char>(nparties));

    string s;
    for (int i = -1; i < mbul; i++)
    {   
        cout << i << " ";
        getline(cin, s);
        int j = 0;
        for (char x : s){
            votes[i][j] += x;
            j++;
        }
            
    }

    int realvotes = 0;
    vector<int> votesperparties(nparties, 0);

    for (int cvotes = 0, votepos, i = 0; i < mbul; i++)
    {
        for (int j = 0; j < nparties; j++)
        {
            if (votes[i][j] == '+')
            {
                cvotes++;
                votepos = j;
            }
        }
        if (cvotes == 1)
        {
            realvotes++;
            votesperparties[votepos]++;
            cvotes = 0;
        }  
    }
    for (int i = 0; i < nparties; i++){
        if (float(votesperparties[i]) / realvotes > 0.06999)
            cout << i + 1 << " ";
    }
}