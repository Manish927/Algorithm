/*
Given an array of positive and negative numbers, the task is to find if there is a subarray (of size at least one) with 0 sum.

Examples: 

Input: {4, 2, -3, 1, 6}
Output: true 
Explanation:
There is a subarray with zero sum from index 1 to 3.

Input: {4, 2, 0, 1, 6}
Output: true
Explanation: The third element is zero. A single element is also a sub-array.

Input: {-3, 2, 3, 1, 6}
Output: false
*/

#include <iostream>
#include <unordered_set>
#include <vector>

bool hasZeroSumSubarray(const std::vector<int>& arr) {
    std::unordered_set<int> prefixSums;
    int currentSum = 0;

    for (int num : arr) {
        currentSum += num;
        
        if (prefixSums.count(currentSum) || num == 0 || currentSum == 0) { // Check if currentSum already exists
            return true;
        }
        prefixSums.insert(currentSum); // Add currentSum to the set
    }
    return false;
}

int main() {
    std::vector<int> arr1 = {4, 2, -3, 1, 6};
    if (hasZeroSumSubarray(arr1)) {
        std::cout << "Array 1: Found a subarray with 0 sum" << std::endl;
    } else {
        std::cout << "Array 1: No subarray with 0 sum" << std::endl;
    }

    std::vector<int> arr2 = {1, 2, 3, 4, 5};
    if (hasZeroSumSubarray(arr2)) {
        std::cout << "Array 2: Found a subarray with 0 sum" << std::endl;
    } else {
        std::cout << "Array 2: No subarray with 0 sum" << std::endl;
    }

    std::vector<int> arr3 = {-3, 2, 3, 1, 6};
    if (hasZeroSumSubarray(arr3)) {
        std::cout << "Array 3: Found a subarray with 0 sum" << std::endl;
    } else {
        std::cout << "Array 3: No subarray with 0 sum" << std::endl;
    }

    std::vector<int> arr4 = {0};
    if (hasZeroSumSubarray(arr4)) {
        std::cout << "Array 4: Found a subarray with 0 sum" << std::endl;
    } else {
        std::cout << "Array 4: No subarray with 0 sum" << std::endl;
    }

    return 0;
}