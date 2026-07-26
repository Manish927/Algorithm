/*
508. Most Frequent Subtree Sum
premium lock icon
Companies
Given the root of a binary tree, return the most frequent subtree sum. If there is a tie, return all the values with the highest frequency in any order.

The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself).
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
    private:
    std::unordered_map<int, int> freq;
    int maxFreq = 0;

    int dfs(TreeNode* root) {
        if (!root)
            return 0;

        int left = dfs(root->left);
        int right = dfs(root->right);

        int sum = left + right + root->val;

        maxFreq = max(maxFreq, ++freq[sum]);

        return sum;
    }

public:
    vector<int> findFrequentTreeSum(TreeNode* root) {
        if (!root)
        return {};

        dfs(root);

        std::vector<int> ans;

        for (auto &p : freq) {
            if (p.second == maxFreq)
                ans.push_back(p.first);
        }

        return ans;
    }
};

