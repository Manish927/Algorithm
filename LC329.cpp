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
    
    int rows, cols;
    vector<vector<int>>dp;
    int res = 0;
    
    void dfs(vector<vector<int>>& matrix, int i, int j, int len, vector<int>&v) 
    {
        if (i >= rows || i < 0 || j >= cols || j < 0 || dp[i][j] > len) return;
        if (v.size() && v.back() >= matrix[i][j]) return;
        
        len++;
        dp[i][j] = max(dp[i][j], len);
        
        res = max(res, len);
        v.push_back(matrix[i][j]);
        dfs(matrix, i+1, j, len, v);
        dfs(matrix, i-1, j, len, v);
        dfs(matrix, i, j+1, len, v);
        dfs(matrix, i, j-1, len, v);
        v.pop_back();
    }
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) 
    {
        if (matrix.empty()) return 0;
        
        rows = matrix.size();
        cols = matrix[0].size();

        dp.resize(rows, std::vector<int>(cols, 0));
        
        for (int i = 0; i < rows; i++) 
        {
            for (int j = 0; j < cols; j++) 
            {
                vector<int>v;
                dfs(matrix, i, j, 0, v);
            }
        }
        
        return res;
    }
};
