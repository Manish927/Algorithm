/*
515. Find Largest Value in Each Tree Row

You need to find the largest value in each row of a binary tree.

Example:
Input: 

          1
         / \
        3   2
       / \   \  
      5   3   9 

Output: [1, 3, 9]
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
    vector<int> largestValues(TreeNode* root) 
    {
        if (!root)
            return {};
        
        std::vector<int> result;
        std::queue<TreeNode*> Q;
        
        Q.push(root);
        
        while (!Q.empty())
        {
            int QSize = Q.size();
            int max = INT_MIN;
            
            while (QSize--)
            {
                TreeNode* temp = Q.front();
                Q.pop();
                
                if (temp->val > max)
                    max = temp->val;
                
                if (temp->left)
                    Q.push(temp->left);
                
                if (temp->right)
                    Q.push(temp->right);
            }
            
            result.push_back(max);
        }
        
        return result;
    }
};
