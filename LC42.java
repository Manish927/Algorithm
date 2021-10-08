/*
42. Trapping Rain Water

Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

 
Example 1:


Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.
Example 2:

Input: height = [4,2,0,3,2,5]
Output: 9 */

class Solution {
    public int trap(int[] height) {
        
        if (height.length <= 0) {
            return 0;
        }
        
        int result = 0;
        int[] left_max = new int[height.length];
        int[] right_max = new int[height.length];
        
        left_max[0] = height[0];
        right_max[height.length - 1] = height[height.length - 1];
        
        for (int i = 1; i < height.length; i++) {
            left_max[i] = Math.max(height[i], left_max[i - 1]);
        }
        
        for (int i = height.length - 2; i >= 0; i--) {
            right_max[i] = Math.max(height[i], right_max[i + 1]);
        }
        
        for (int i = 1; i < height.length; i++) {
            result += Math.min(left_max[i], right_max[i]) - height[i];
        }
        
        return result;
        
    }
}
