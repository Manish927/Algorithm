/*
110. Balanced Binary Tree
Given a binary tree, determine if it is height-balanced

Input: root = [3,9,20,null,null,15,7]
Output: true

*/

class Solution {
public:
    bool isBalanced(TreeNode* root) {
        return checkHeight(root) != -1;
    }

private:
    int checkHeight(TreeNode* node) {
        if (!node) return 0;

        int leftHeight = checkHeight(node->left);
        if (leftHeight == -1) return -1;

        int rightHeight = checkHeight(node->right);
        if (rightHeight == -1) return -1;

        if (abs(leftHeight - rightHeight) > 1) return -1;

        return max(leftHeight, rightHeight) + 1;
    }
};


// Iterative solution

#include <iostream>
#include <stack>
#include <unordered_map>
#include <cmath>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if (!root) return true;

        unordered_map<TreeNode*, int> heightMap;
        unordered_map<TreeNode*, bool> visited;
        stack<TreeNode*> stk;
        stk.push(root);

        while (!stk.empty()) {
            TreeNode* node = stk.top();

            if (!node) {
                stk.pop();
                continue;
            }

            if ((!node->left || visited[node->left]) &&
                (!node->right || visited[node->right])) {

                stk.pop();
                int leftHeight = node->left ? heightMap[node->left] : 0;
                int rightHeight = node->right ? heightMap[node->right] : 0;

                if (abs(leftHeight - rightHeight) > 1)
                    return false;

                heightMap[node] = 1 + max(leftHeight, rightHeight);
                visited[node] = true;
            } else {
                if (node->right && !visited[node->right])
                    stk.push(node->right);
                if (node->left && !visited[node->left])
                    stk.push(node->left);
            }
        }

        return true;
    }
};