/* 
240. Search a 2D Matrix II

Write an efficient algorithm that searches for a value target in an m x n integer matrix matrix. This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.

Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
Output: true


Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
Output: false
*/


//Solution 1 of 2
class Solution {
public:
    
    Solution() {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
    }
    
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int row = matrix.size();
        int col = matrix[0].size();
    
        int rowIndex = 0;
        int colIndex = col-1;
    
        while(rowIndex < row && colIndex>=0)
        {
            int element = matrix[rowIndex][colIndex];
            if(element == target)
            {
                return 1;
            }
            if(element < target)
            {
                rowIndex++;
            }
            else
            {
                colIndex--;
            }
        }
        return 0;
    }
};
