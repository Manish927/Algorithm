/*
Write an efficient algorithm that searches for a value target in an m x n integer matrix matrix. This matrix has the following properties:
Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.

Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
Output: true

Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
Output: false
*/



static const auto speedup = []()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}();

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        
        int low = matrix.size(), high = matrix[0].size() - 1;
            int mid = 0;
            
            while(mid < low && high >= 0) {
                if(matrix[mid][high] == target)
                    return true;
                if(target < matrix[mid][high])
                    high--;
                else 
                    mid++;
            }
            return false;
    }
};
