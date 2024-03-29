/*
56. Merge Intervals

Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.

 

Example 1:

Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].
Example 2:

Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.
*/

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        
        sort(intervals.begin(), intervals.end());
        
        std::vector<std::vector<int>> merged;
        
        for (auto interval : intervals) {
            
            //if the list of merged intervals is empty or if the current interval
            // does not overlap with the previous, simple append it.
            
            if (merged.empty() || merged.back()[1] < interval[0]) {
                merged.push_back(interval);
            }
            else
            {
                // there is an overlap, so we merge the current and previous intervals.
                merged.back()[1] = std::max(merged.back()[1], interval[1]);
            }
        }
        
        return merged;
    }
};
