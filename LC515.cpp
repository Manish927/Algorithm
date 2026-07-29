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

/*
Approach: Breadth-First Search

Process the tree level by level using a queue. For each level:

Record the number of nodes currently in the queue.
Visit exactly those nodes.
Track the maximum value among them.
Add their children to the queue for the next level.

*/
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value)
        : val(value), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        vector<int> result;

        if (root == nullptr) {
            return result;
        }

        queue<TreeNode*> nodes;
        nodes.push(root);

        while (!nodes.empty()) {
            int levelSize = nodes.size();
            int levelMaximum = INT_MIN;

            for (int i = 0; i < levelSize; ++i) {
                TreeNode* current = nodes.front();
                nodes.pop();

                levelMaximum = max(levelMaximum, current->val);

                if (current->left != nullptr) {
                    nodes.push(current->left);
                }

                if (current->right != nullptr) {
                    nodes.push(current->right);
                }
            }

            result.push_back(levelMaximum);
        }

        return result;
    }
};
