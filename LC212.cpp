/*
212. Word Search II

Given an m x n board of characters and a list of strings words, return all words on the board.

Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

 

Example 1:

*/

class Solution {
    
    class Node {
        public: 
            unordered_map<char, Node*> children;
            std::string word;
    };
    
    Node* trie;
        
    std::vector<std::vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    
    void dfs(std::vector<string>& result, std::vector<std::vector<char>>& board, int row, int col, Node* trieNode) {
        
        char ch = board[row][col];
        Node* next = trieNode->children[ch];
        
        if (next->word != "") {
            result.push_back(next->word);
            next->word = "";
        }
        
        if (next->children.empty()) {
            trieNode->children.erase(ch);
            return;
        }
        
        board[row][col] = '#'; //ensuring we have visited
        
        for (const auto& dir : directions) {
            int r = row + dir[0];
            int c = col + dir[1];
            
            if (r < 0 || r >= board.size() || c < 0 || c >= board[0].size()) {
                continue;
            }
            
            if (next->children.count(board[r][c])) {
                dfs(result, board, r, c, next);
            }
        }
        
        board[row][col] = ch;   // put back from '#' to original char.
    }
    
    public:
    
    Solution() : trie(new Node()) {}
    
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        // constructing a trie using list of input words
        
        for (const auto& word : words) {
            Node* curr = trie;
            
            for (auto const& c : word) {
                if (!curr->children.count(c)) {
                    curr->children.emplace(c, new Node());
                }
                
                curr= curr->children[c];
            }
            curr->word = word;
        }
        
        
        //tracking trie untill we meet a completed word
        int m = board.size();
        int n = board[0].size();
        
        std::vector<std::string> result;
        
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                
                // only tracking the character from trie
                if (trie->children.count(board[i][j])) {
                    dfs(result, board, i, j , trie);
                }
            }
        }
        
        return result;
    }
};
