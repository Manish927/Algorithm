/*
300. Longest Increasing Subsequence

Given an unsorted array of integers, find the length of longest increasing subsequence.

Example:

Input: [10,9,2,5,3,7,101,18]
Output: 4 
Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4. 
Note:

There may be more than one LIS combination, it is only necessary for you to return the length.
Your algorithm should run in O(n2) complexity.
Follow up: Could you improve it to O(n log n) time complexity?
*/

public class Solution 
{
    public int lengthOfLIS(int[] nums) 
    {
        int[] dp = new int[nums.length];
        int len = 0;
        
        for (int num : nums) 
        {
            int i = Arrays.binarySearch(dp, 0, len, num);
        
            if (i < 0) 
            {
                i = -(i + 1);
            }
            
            dp[i] = num;
            
            if (i == len) 
            {
                len++;
            }
        }
        
        return len;
    }
}
