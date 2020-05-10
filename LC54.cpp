/*
54. Spiral Matrix
Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

Example 1:

Input:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
Output: [1,2,3,6,9,8,7,4,5]
Example 2:

Input:
[
  [1, 2, 3, 4],
  [5, 6, 7, 8],
  [9,10,11,12]
]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]
*/

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
     
        if (matrix.size() == 0)
            return {};
        
        int mxn = matrix.size() * matrix[0].size();
        std::vector<int> result;// (mxn);
        
        int startRow = 0;
        int endRow = matrix.size() - 1;
        int startCol = 0;
        int endCol = matrix[0].size() - 1;
        
        while (startRow <= endRow && startCol <= endCol)
        {
            for (int col = startCol; col <= endCol; col++)
                result.push_back(matrix[startRow][col]);
            
            for (int row =startRow + 1; row <= endRow; row++)
                result.push_back(matrix[row][endCol]);
            
            
            if (startRow < endRow && startCol < endCol)
            {
                for (int col = endCol - 1; col >= startCol; col--)
                {   
                    result.push_back(matrix[endRow][col]);
                }

                for (int row = endRow-1; row > startRow; row--)
                {
                    result.push_back(matrix[row][startCol]);
                }
            }
            startRow++;
            endRow--;
            startCol++;
            endCol--;
        }
        
        return result;
        
    }
};
