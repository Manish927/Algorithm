
/*
Given a string, sort it in decreasing order based on the frequency of characters.

Example 1:

Input:
"tree"

Output:
"eert"

Explanation:
'e' appears twice while 'r' and 't' both appear once.
So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.
Example 2:

Input:
"cccaaa"

Output:
"cccaaa"

Explanation:
Both 'c' and 'a' appear three times, so "aaaccc" is also a valid answer.
Note that "cacaca" is incorrect, as the same characters must be together.
Example 3:

Input:
"Aabb"

Output:
"bbAa"

Explanation:
"bbaA" is also a valid answer, but "Aabb" is incorrect.
Note that 'A' and 'a' are treated as two different characters.

*/

//Approach 1 of 2 : using Java Stream, Collectors
class Solution {
    public String frequencySort(String s) {
        HashMap<Character, Integer> hashMap = new HashMap<>();

        s.chars().forEach(c -> hashMap.put((char) c, hashMap.getOrDefault((char) c, 0) + 1));
        StringBuilder sb = new StringBuilder();

        hashMap.entrySet().stream().sorted(Map.Entry.comparingByValue(Comparator.reverseOrder())).forEach(e->repeat(e, sb));

        return sb.toString();
    }
    
    public static void repeat(Map.Entry e, StringBuilder sb)
    {
        char[] chars = new char[(int) e.getValue()];

        Arrays.fill(chars, (char)e.getKey());
        sb.append(chars);
    }
}


//Approach 2 of 2
class Solution {
    public String frequencySort(String s) {
        HashMap<Character, Integer> hash_map = new HashMap<Character, Integer>();
        
        for (char c : s.toCharArray())
        {
            hash_map.put(c, hash_map.getOrDefault(c, 0) + 1);
        }
        
        PriorityQueue<Character> maxHeap = new PriorityQueue<>((a, b) -> hash_map.get(b) - hash_map.get(a));
        // lambda where characters placed is sorted based on the frequency 
        
        maxHeap.addAll(hash_map.keySet());
        
        StringBuilder str = new StringBuilder();
        
        while(!maxHeap.isEmpty())
        {
            char curr = maxHeap.remove();
            
            for (int i = 0; i < hash_map.get(curr); i++)
            {
                str.append(curr);
            }
        }
        
        return str.toString();
    }
}
