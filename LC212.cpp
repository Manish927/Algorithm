/*
212. Word Search II

Given an m x n board of characters and a list of strings words, return all words on the board.

Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

 

Example 1:

*/

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

class Solution {
    
    struct Node { 
        // Use unique_ptr to automatically prevent memory leaks
        std::unordered_map<char, std::unique_ptr<Node>> children;
        std::string word = "";
    };
    
    std::unique_ptr<Node> trie;
        
    // Using a std::pair array with structured bindings makes direction code readable
    const std::vector<std::pair<int, int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };
    
    
    void dfs(std::vector<string>& result, std::vector<std::vector<char>>& board, int row, int col, Node* trieNode) {
        
        char ch = board[row][col];
        Node* next = trieNode->children[ch].get();
        
        if (!next->word.empty()) {
            result.push_back(std::move(next->word));
            next->word.clear();
        }
        
        if (next->children.empty()) {
            trieNode->children.erase(ch);
            return;
        }
        
        board[row][col] = '#'; //ensuring we have visited
        
        for (const auto& [dr, dc] : directions) {
            int r = row + dr;
            int c = col + dc;
            
            if (r < 0 || r >= board.size() || c < 0 || c >= board[0].size()) {
                continue;
            }
            
            if (next->children.contains(board[r][c])) {
                dfs(result, board, r, c, next);
            }
        }
        
        board[row][col] = ch;   // put back from '#' to original char.
    }
    
    public:
    
    Solution() : trie(std::make_unique<Node>()) {}
    
    std::vector<std::string> findWords(vector<vector<char>>& board, vector<string>& words) {
        // constructing a trie using list of input words
        
        for (const auto& word : words) {
            Node* curr = trie.get();
            
            for (const char c : word) {
                if (!curr->children.contains(c)) {
                    curr->children[c] = std::make_unique<Node>();
                }
                curr= curr->children[c].get();
            }
            curr->word = word;
        }
        
       //tracking trie untill we meet a completed word
        std::vector<std::string> result;
        int m = board.size();
        int n = board[0].size();
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (trie->children.contains(board[i][j])) {
                    dfs(result, board, i, j , trie.get());
                }
            }
        }
        
        return result;
    }
};
