
/*

Explanation
1.	Sliding Window:
•	The left and right pointers define the current window.
•	The window is expanded by moving the right pointer and shrunk by moving the left pointer.
2.	Character Frequency Map:
•	A hash map (unordered_map) is used to track the frequency of characters in the current window.

Complexity
•	Time Complexity: O(26 * n), where:
•	26 is the maximum number of distinct characters (for lowercase English letters).
•	n is the length of the string.
•	Space Complexity: O(26) for the frequency map.

*/

class Solution {
public:
    int numberOfSubstrings(string s, int k) {
        int n = s.length(), res = (n + 1) * n / 2;

        unordered_map<char, int> count;
        for (int left = 0, right = 0; right < n; right++) {
            count[s[right]]++;
            
            while (count[s[right]] >= k)
                --count[s[left++]];
            
            res -= right - left + 1;
        }
        return res;
    }
};
