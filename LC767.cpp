/*
767. Reorganize String

Given a string s, rearrange the characters of s so that any two adjacent characters are not the same.

Return any possible rearrangement of s or return "" if not possible.

 

Example 1:

Input: s = "aab"
Output: "aba"
Example 2:

Input: s = "aaab"
Output: ""
 

Constraints:

1 <= s.length <= 500
s consists of lowercase English letters.
*/

class Solution {
public:
    string reorganizeString(string s) {
        
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        
        typedef std::pair<char, int> PairT;
        auto cmp = [&](PairT a, PairT b) { return a.second < b.second; };
        typedef std::unordered_map<char, int> FreqMapT;
        FreqMapT freq_map;
        FreqMapT::iterator freq_iter;
        
        for (auto elem : s) {
            freq_iter = freq_map.find(elem);
            
            if (freq_iter != freq_map.end()) {
                freq_iter->second++;
            }
            else
                freq_map.insert({elem, 0});
        }
        
        std::string result;
        std::priority_queue<PairT, std::vector<PairT>, decltype(cmp)> maxHeap{cmp};
        for (auto [first, second] : freq_map) {
            maxHeap.push({first, second});
        }
        
        
        auto start = maxHeap.top(); maxHeap.pop();
        result.push_back(start.first);
        start.second--;
        
        while (!maxHeap.empty()) {
            auto temp = maxHeap.top(); maxHeap.pop();
            result.push_back(temp.first);
            temp.second--;
            
            if (start.second >= 0) {
                maxHeap.push(start);
            }
            
            start = temp;
        }
        
        if (start.second >= 0) 
            return "";
        
        return result;
    }
    

};
