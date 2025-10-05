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

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Stack;

public class Main {
    
    public List<Integer> nextGreaterElements(int[] nums) {
        int n = nums.length;
        List<Integer> result = new ArrayList<>(Collections.nCopies(n, -1));
        Stack<Integer> stack = new Stack<>();

        for (int i = 0; i < 2 * n; i++) {
            int circularIdx = i % n;

            while (!stack.isEmpty() && nums[stack.peek()] < nums[circularIdx]) { 
                result.set(stack.peek(), nums[circularIdx]);
                stack.pop();
            }
            
            stack.push(circularIdx);
            
        }

        return result;
    }
    
    public static void main(String[] args) {
        System.out.println("Hello, World!");

        Main main = new Main();
        int[] nums = {2, 5, -3, -4, 6, 7, 2};
        List<Integer> result = main.nextGreaterElements(nums);
        System.out.println(result); // Output: [5, 6, 6, 6, 7, -1, 5]
    }

}
