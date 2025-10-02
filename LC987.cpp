/*
987. Vertical Order Traversal of a Binary Tree

Given the root of a binary tree, calculate the vertical order traversal of the binary tree.

For each node at position (row, col), its left and right children will be at positions (row + 1, col - 1) and (row + 1, col + 1) respectively. The root of the tree is at (0, 0).

The vertical order traversal of a binary tree is a list of top-to-bottom orderings for each column index starting from the leftmost column and ending on the rightmost column. There may be multiple nodes in the same row and same column. In such a case, sort these nodes by their values.

Return the vertical order traversal of the binary tree.

Input: root = [3,9,20,null,null,15,7]
Output: [[9],[3,15],[20],[7]]
Explanation:
Column -1: Only node 9 is in this column.
Column 0: Nodes 3 and 15 are in this column in that order from top to bottom.
Column 1: Only node 20 is in this column.
Column 2: Only node 7 is in this column.

*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */


 class Solution {
public:
    
    Solution() {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
    }

    vector<vector<int>> verticalTraversal(TreeNode* root) {
    
        queue<pair<TreeNode*, pair<int, int>>> q;
        map<int, map<int, multiset<int>>> mpp;

        if(root == NULL) return{};

        q.push({root, {0, 0}});

        while( !q.empty() ){

            auto p = q.front();
            q.pop();

            TreeNode* node = p.first;
            int v = p.second.first;
            int l = p.second.second;

            mpp[v][l].insert(node -> val);

            if(node -> left) q.push({node->left, {v - 1, l + 1}});
            if(node -> right) q.push({node->right, {v + 1, l + 1}});
            
        }

        vector<vector<int>> ans;

        for(auto it : mpp){
            vector<int> col;

            for(auto x : it.second){
                col.insert(col.end(), x.second.begin(), x.second.end());
                // col.insert(where you want to insert, range)
            }
            ans.push_back(col);
        }

        return ans;
    }
}


void printVerticalOrder(vector<vector<int>>& res) {
    for (auto& col : res) {
        for (int val : col) cout << val << " ";
        cout << endl;
    }
}

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    Solution sol;

    vector<vector<int>> result = sol.verticalTraversal(root);
    printVerticalOrder(result);

    return 0;
}