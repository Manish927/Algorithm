/*
Remove Duplicates Sorted Array

You are given a sorted array arr[] containing positive integers. Your task is to remove all duplicate elements from this array such that each element appears only once. Return an array containing these distinct elements in the same order as they appeared.
Examples :

Input: arr[] = [2, 2, 2, 2, 2]
Output: [2]
Explanation: After removing all the duplicates only one instance of 2 will remain i.e. [2] so modified array will contains 2 at first position and you should return array containing [2] after modifying the array.
Input: arr[] = [1, 2, 4]
Output: [1, 2, 4]
Explation:  As the array does not contain any duplicates so you should return [1, 2, 4].
*/


#include <iostream>
#include <vector>
using namespace std;

vector<int> removeDuplicates(vector<int> &arr) {
    std::vector<int> result;
    int size = arr.size();
    int idx = 1;
    
    if (arr.empty()) {
        return result;
    }
    
    result.push_back(arr[0]);
    
    for (int i = 1; i < size; i++) {
        if (arr[i-1] != arr[i]) {
            result.push_back(arr[i]);
        }
    }
    
    return result;
}

int main() {
    vector<int> arr = {2, 2, 2, 2, 2};
    vector<int> distinct = removeDuplicates(arr);
    for (int num : distinct) {
        cout << num << " ";
    }
    return 0;
}