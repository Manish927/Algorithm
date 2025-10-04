/*
Next Greater Element

You are given an array arr[] of integers, the task is to find the next greater element for each element of the array in order of their appearance in the array. Next greater element of an element in the array is the nearest element on the right which is greater than the current element.
If there does not exist next greater of current element, then next greater element for current element is -1.

Examples

Input: arr[] = [1, 3, 2, 4]
Output: [3, 4, 4, -1]
Explanation: The next larger element to 1 is 3, 3 is 4, 2 is 4 and for 4, since it doesn't exist, it is -1.
Input: arr[] = [6, 8, 0, 1, 3]
Output: [8, -1, 1, 3, -1]
Explanation: The next larger element to 6 is 8, for 8 there is no larger elements hence it is -1, for 0 it is 1, for 1 it is 3 and then for 3 there is no larger element on right and hence -1.
Input: arr[] = [1, 2, 3, 5]
Output: [2, 3, 5, -1]
Explanation: For a sorted array, the next element is next greater element also except for the last element.
Input: arr[] = [5, 4, 3, 1]
Output: [-1, -1, -1, -1]
Explanation: There is no next greater element for any of the elements in the array, so all are -1.
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

