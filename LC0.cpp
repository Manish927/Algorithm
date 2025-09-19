/*
   Write a function that takes in a list of unique strings and returns a list of semordnilap pairs. A semordnilap pair is defined as a set of different
   strings where the reverse of one word is the same as the forward version of the other. For example, the words "diaper" and "repaid" are a semordnilap pair,
   as the words "palindromes" and "semordnilap".

   The order of the returned pairs and the order of the string within each pair do not matter.

   Sample input:
   words = ["diaper", "abc", "test", "cba", "repaid"]
   sample output
   [["diaper, "repaid"], ["abc", "cba"]]   
*/
#include <unordered_set>
#include <vector>

std::vector<std::pair<string, string>> semordnilap(std::vector<string> words) {
  unordered_set<string> wordList;
  vector<vector<string>> result;

  for (string word : words) {
    string revWord = word;
    reverse(revWord.begin(), revWord.end());

    if (wordList.find(revWord) != wordList.end()) {
      result.push_back({word, revWord});
    }
    wordList.insert(word);
      
  }
  
  return result;
}
