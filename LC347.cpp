/*
347. Top K Frequent Elements

Given a non-empty array of integers, return the k most frequent elements.

Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]
Example 2:

Input: nums = [1], k = 1
Output: [1]
Note:

You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
It's guaranteed that the answer is unique, in other words the set of the top k frequent elements is unique.
You can return the answer in any order.
*/

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
        
        unordered_map<int, int> freq;
        
        for(int i = 0; i<nums.size(); i++)
        {
            freq[nums[i]]++;
        }
        
        priority_queue<int, vector<int>, greater<int>> heap;

        for(auto it = freq.begin(); it != freq.end(); it++)
        {
            heap.push(it->second);
            
            if(heap.size() > k)
            {
                heap.pop();
            }
        }
        
        vector<int> result;
        for(auto it = freq.begin(); it != freq.end(); it++)
        {
            if(it->second >= heap.top())
            {
                result.push_back(it->first);
            }
        }
        
        return result;        
    }
};
