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

class Solution {
public:
    std::string frequencySort(std::string& str)
    {
      std::unordered_map<char, short int> count;
      const auto compare = [&](char a, char b) {return count[a] < count[b]; };
      std::priority_queue<char, std::vector<char>, decltype(compare)> maxHeap{compare};

      std::string result;
      result.reserve(10);

      for (auto& c : str)
      {
        auto iter = count.find(c);

        if (iter != count.end())
          iter->second += 1;
        else
          count.insert({c, 0});
      }

      for (auto [first, second] : count)
      {
        maxHeap.push(first);
      }

      while (!maxHeap.empty())
      {
        char curr = maxHeap.top();

        for (auto i = 0; i <= count[curr]; i++)
          result.append(1, curr);
        maxHeap.pop();
      }

      return result;
   }
};
