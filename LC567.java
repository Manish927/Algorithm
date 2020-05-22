/*

567. Permutation in String
Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1. 
In other words, one of the first string's permutations is the substring of the second string. 

Example 1:

Input: s1 = "ab" s2 = "eidbaooo"
Output: True
Explanation: s2 contains one permutation of s1 ("ba").
Example 2:

Input:s1= "ab" s2 = "eidboaoo"
Output: False
 
Constraints:

The input strings only contain lower case letters.
The length of both given strings is in range [1, 10,000].

*/
class Solution {
    public boolean checkInclusion(String s1, String s2) 
    {
       if (s1.length() > s2.length())
            return false;
        
        int[] s1map = new int[26];
        int[] s2map = new int[26];
        
        for (int i = 0; i < s1.length(); i++) 
        {
            s1map[s1.charAt(i) - 'a']++;
            s2map[s2.charAt(i) - 'a']++;
        }
        
        int count = 0;
        for (int i = 0; i < 26; i++)
        {
            if (s1map[i] == s2map[i])
                count++;
        }       
        for (int i = 0; i < s2.length() - s1.length(); i++) 
        {
            int r = s2.charAt(i + s1.length()) - 'a', l = s2.charAt(i) - 'a';
            if (count == 26)
                return true;
            
            s2map[r]++;
            if (s2map[r] == s1map[r])
                count++;
            else if (s2map[r] == s1map[r] + 1)
                count--;
            s2map[l]--;
            if (s2map[l] == s1map[l])
                count++;
            else if (s2map[l] == s1map[l] - 1)
                count--;
        }
        return count == 26; 
    }
}
