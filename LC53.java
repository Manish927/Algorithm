/*
Given an integer array nums, find the subarray with the largest sum, and return its sum.

 

Example 1:

Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: The subarray [4,-1,2,1] has the largest sum 6.
Example 2:

Input: nums = [1]
Output: 1
Explanation: The subarray [1] has the largest sum 1.
*/

class Solution {
    public int maxSubArray(int[] A) {
        int maxGlobal = A[0];
        int sums[] = new int[A.length];
        sums[0] = A[0];

        for (int i = 1; i < A.length; i++)
        {
            sums[i] = Math.max(A[i], (A[i] + sums[i - 1]));
            maxGlobal = Math.max(sums[i], maxGlobal);
        }
        return maxGlobal;
    }
}