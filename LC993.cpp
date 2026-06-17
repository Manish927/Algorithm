class Solution {
public:
    bool isCousins(TreeNode* root, int x, int y) {
        if (!root)
            return false;

        TreeNode* xParent = nullptr;
        TreeNode* yParent = nullptr;
        int xDepth = -1;
        int yDepth = -1;

        struct NodeInfo {
            TreeNode* node;
            TreeNode* parent;
            int depth;
        };

        stack<NodeInfo> st;
        st.push({root, nullptr, 0});

        while (!st.empty()) {
            auto [node, parent, depth] = st.top();
            st.pop();

            if (node->val == x) {
                xParent = parent;
                xDepth = depth;
            }
            else if (node->val == y) {
                yParent = parent;
                yDepth = depth;
            }

            // Optional early exit
            if (xDepth != -1 && yDepth != -1)
                break;

            if (node->right)
                st.push({node->right, node, depth + 1});

            if (node->left)
                st.push({node->left, node, depth + 1});
        }

        return xDepth == yDepth && xParent != yParent;
    }
};
