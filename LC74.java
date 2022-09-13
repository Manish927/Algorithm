/*

Write an efficient algorithm that searches for a value target in an m x n integer matrix matrix. This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.

Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
Output: true

Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
Output: false
*/




class Solution {
    public boolean searchMatrix(int[][] matrix, int target) {
        int searchRow = 0, searchCol = matrix[0].length - 1;
        
        while ((searchRow >= 0 && searchRow < matrix.length) &&
                (searchCol >= 0 && searchCol< matrix[0].length)) {
            if (matrix[searchRow][searchCol] == target)
                return true;
            else if (target > matrix[searchRow][searchCol]) {
                 searchRow++;
            } else {
                searchCol--;
            }
        }
        return false;
    }
}
