/*
Next Greater Element in Circular Array

Given a circular integer array arr[], the task is to determine the next greater element (NGE) for each element in the array.

The next greater element of an element arr[i] is the first element that is greater than arr[i] when traversing circularly. If no such element exists, return -1 for that position.

Note: Since the array is circular, after reaching the last element, the search continues from the beginning until we have looked at all elements once.

Examples: 

Input: arr[] = [1, 3, 2, 4]
Output: [3, 4, 4, -1]
Explanation:
The next greater element for 1 is 3.
The next greater element for 3 is 4.
The next greater element for 2 is 4.
The next greater element for 4 does not exist, so return -1.
Input: arr[] = [0, 2, 3, 1, 1]
Output: [2, 3, -1, 2, 2]
Explanation:
The next greater element for 0 is 2.
The next greater element for 2 is 3.
The next greater element for 3 does not exist, so return -1.
The next greater element for 1 is 2 (from circular traversal).
The next greater element for 1 is 2 (from circular traversal).
*/

#include <vector>
#include <stack>

std::vector<int> nextGreaterElement(vector<int> nums) {
    std::vector<int> result(nums.size(), -1);   // Initialize result with -1
    std::stack<int> s;                // Store indexes of elements

    for (int i = 0; i < nums.size() * 2; ++i) {
      int circularIdx = i % nums.size();
      
        while (!s.empty() && nums[s.top()] < nums[circularIdx] )
        {
            int top = s.top();
            s.pop();
            result[top] = nums[circularIdx];
        }
        
        s.push(circularIdx);
    }
    return result;
}

int main() {
    vector<int> arr = {1, 3, 2, 4};
    vector<int> res = nextGreaterElement(arr);
    for (int x : res) {
        cout << x << " ";
    }
    return 0;
}
