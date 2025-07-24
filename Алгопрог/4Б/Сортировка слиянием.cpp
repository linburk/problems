#include <queue>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <list>
#include <iterator>
using namespace std;

void merging(vector<int>::iterator iterator_left, vector<int>::iterator iterator_middle, vector<int>::iterator iterator_right){
    
    vector<int>::iterator iterator_left_copy = iterator_left, iterator_middle_copy = iterator_middle; // ÐºÐ¾Ð¿Ð¸Ñ Ð¸ÑÐµÑÐ°ÑÐ¾ÑÐ¾Ð²
    vector<int> transitional_array; // Ð²ÑÐµÐ¼ÐµÐ½Ð½ÑÐ¹ Ð¼Ð°ÑÑÐ¸Ð²

    while (iterator_left != iterator_middle and iterator_middle != iterator_right){
        if (*iterator_left < *iterator_middle){
            transitional_array.push_back(*iterator_left);
            iterator_left++;
        }
        else {
            transitional_array.push_back(*iterator_middle);
            iterator_middle++;
        }
    }

    transitional_array.insert(transitional_array.end(), iterator_left, iterator_middle_copy); // Ð²ÑÑÐ°Ð²ÐºÐ° Ð¾ÑÑÐ°ÑÐºÐ¾Ð²
    transitional_array.insert(transitional_array.end(), iterator_middle, iterator_right);

    move(transitional_array.begin(), transitional_array.end(), iterator_left_copy); // Ð¿ÐµÑÐµÐ¼ÐµÑÐµÐ½Ð¸Ðµ Ð² Ð¸ÑÑÐ¾Ð´Ð½ÑÐ¹ Ð¼Ð°ÑÑÐ¸Ð²

}

void merge_sorting(vector<int>::iterator iterator_left, vector<int>::iterator iterator_right){

    if (iterator_left + 1 >= iterator_right)
        return;

    int int_middle = distance(iterator_left, iterator_right) / 2; // ÑÐµÑÐµÐ´Ð¸Ð½Ð° Ð¼Ð°ÑÑÐ¸Ð²Ð°

    vector<int>::iterator iterator_middle = iterator_left + int_middle;

    merge_sorting(iterator_left, iterator_middle);
    merge_sorting(iterator_middle, iterator_right);

    merging(iterator_left, iterator_middle, iterator_right);

}

int main(){

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    merge_sorting(a.begin(), a.end());

    for (auto i : a)
        cout << i << " ";

}