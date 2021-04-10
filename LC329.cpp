/*329. Longest Increasing Path in a Matrix
Given an integer matrix, find the length of the longest increasing path.

From each cell, you can either move to four directions: left, right, up or down. You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).

Example 1:

Input: nums = 
[
  [9,9,4],
  [6,6,8],
  [2,1,1]
] 
Output: 4 
Explanation: The longest increasing path is [1, 2, 6, 9].
Example 2:

Input: nums = 
[
  [3,4,5],
  [3,2,6],
  [2,2,1]
] 
Output: 4 
Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed. 
*/

class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) 
    {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        
        int m = matrix.size();
        int n = matrix[0].size();
        
        vector<vector<int>> dp(m, vector<int>(n, 0));    // prepare the cache.
        int maxVal = 0;
        
        for (int row = 0; row < m; row++)
        {
            for (int col = 0; col < n; col++)
            {
                maxVal = max(maxVal, dfs(dp, matrix, row, col, -1));
            }
        }
        
        return maxVal;
    }
    
    int dfs(vector<vector<int>> &dp, vector<vector<int>>& matrix, int row, int col, int pre)
    {
        if (row < 0 || col < 0 || row == matrix.size() || col == matrix[0].size() || pre >= matrix[row][col])
            return 0;
        
        if (dp[row][col])
            return dp[row][col];
        
        int val = matrix[row][col];
        matrix[row][col] = -1;
        
        int left = dfs(dp, matrix, row, col - 1, val);
        int right = dfs(dp, matrix, row, col + 1, val);
        int up = dfs(dp, matrix, row - 1, col, val);
        int down = dfs(dp, matrix, row + 1, col, val);
        
        matrix [row][col] = val;
        
        return dp[row][col] = max({left, right, up, down}) + 1;
    }
};
