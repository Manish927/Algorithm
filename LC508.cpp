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

void printVector(vector<int> ans) {
    cout << "[ ";

    for (int x : ans)
        cout << x << " ";

    cout << "]\n";
}

int main() {

    Solution sol;

    //==============================
    // Test Case 1
    //      5
    //     / \
    //    2  -3
    //==============================

    TreeNode* root1 = new TreeNode(5);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(-3);

    cout << "Test Case 1\n";
    printVector(sol.findFrequentTreeSum(root1));


    //==============================
    // Test Case 2
    //      5
    //     / \
    //    2  -5
    //==============================

    sol = Solution();

    TreeNode* root2 = new TreeNode(5);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(-5);

    cout << "Test Case 2\n";
    printVector(sol.findFrequentTreeSum(root2));


    //==============================
    // Test Case 3
    //      1
    //     / \
    //    1   1
    //==============================

    sol = Solution();

    TreeNode* root3 = new TreeNode(1);
    root3->left = new TreeNode(1);
    root3->right = new TreeNode(1);

    cout << "Test Case 3\n";
    printVector(sol.findFrequentTreeSum(root3));


    //==============================
    // Test Case 4
    //
    //          4
    //         / \
    //        2   6
    //       / \
    //      1   3
    //==============================

    sol = Solution();

    TreeNode* root4 = new TreeNode(4);
    root4->left = new TreeNode(2);
    root4->right = new TreeNode(6);
    root4->left->left = new TreeNode(1);
    root4->left->right = new TreeNode(3);

    cout << "Test Case 4\n";
    printVector(sol.findFrequentTreeSum(root4));


    //==============================
    // Test Case 5
    //
    //        0
    //       / \
    //      0   0
    //==============================

    sol = Solution();

    TreeNode* root5 = new TreeNode(0);
    root5->left = new TreeNode(0);
    root5->right = new TreeNode(0);

    cout << "Test Case 5\n";
    printVector(sol.findFrequentTreeSum(root5));


    return 0;
}
